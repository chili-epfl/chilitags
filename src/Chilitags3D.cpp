/*******************************************************************************
*   Copyright 2013-2014 EPFL                                                   *
*   Copyright 2013-2014 Quentin Bonnard                                        *
*                                                                              *
*   This file is part of chilitags.                                            *
*                                                                              *
*   Chilitags is free software: you can redistribute it and/or modify          *
*   it under the terms of the Lesser GNU General Public License as             *
*   published by the Free Software Foundation, either version 3 of the         *
*   License, or (at your option) any later version.                            *
*                                                                              *
*   Chilitags is distributed in the hope that it will be useful,               *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of             *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
*   GNU Lesser General Public License for more details.                        *
*                                                                              *
*   You should have received a copy of the GNU Lesser General Public License   *
*   along with Chilitags.  If not, see <http://www.gnu.org/licenses/>.         *
*******************************************************************************/

#include <chilitags.hpp>

#include "Filter.hpp"

#include <iostream>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp> //for FileStorage
#ifdef OPENCV3
#include <opencv2/core/utility.hpp>
#endif

namespace chilitags{

template<typename RealT>
class Chilitags3D<RealT>::Impl {

public:
Impl(cv::Size cameraResolution) :
    mChilitags(),
    mOmitOtherTags(false),
    mCameraMatrix(),
    mDistCoeffs(),
    mDefaultTagCorners(),
    mId2Configuration(),

    mFilter(5, 0.5f)
{
    RealT focalLength = 700.0f;
    mCameraMatrix = (cv::Mat_<RealT>(3,3) <<
        focalLength ,            0 , cameraResolution.width /2,
                   0 , focalLength , cameraResolution.height/2,
                   0,             0 , 1
    );
    setDefaultTagSize(20.0f);
    mChilitags.setFilter(0, 0.0f);
}

void setFilter(int persistence, float gain) {
    mFilter.setPersistence(persistence);
    mFilter.setGain(gain);
}

const Chilitags &getChilitags() const {
    return mChilitags;
}
      Chilitags &getChilitags()       {
    return mChilitags;
}

TagPoseMap estimate(const TagCornerMap &tags) {

    TagPoseMap objects;

    std::map<
        const std::string,     //name of the object
        std::pair<
            std::vector<cv::Point3_<RealT>>,      //points in object
            std::vector<cv::Point2f>>>   //points in frame
    objectToPointMapping;


    auto configurationIt = mId2Configuration.begin();
    auto configurationEnd = mId2Configuration.end();
    for (const auto &tag : tags) {
        int tagId = tag.first;
        const cv::Mat_<cv::Point2f> corners(tag.second);

        while (configurationIt != configurationEnd
               && configurationIt->first < tagId)
            ++configurationIt;

        if (configurationIt != configurationEnd) {
            if (configurationIt->first == tagId) {
                const auto &configuration = configurationIt->second;
                if (configuration.second.mKeep) {
                    computeTransformation(cv::format("tag_%d", tagId),
                                          configuration.second.mLocalcorners,
                                          corners,
                                          objects);
                }
                auto & pointMapping = objectToPointMapping[configuration.first];
                pointMapping.first.insert(
                    pointMapping.first.end(),
                    configuration.second.mCorners.begin(),
                    configuration.second.mCorners.end());
                pointMapping.second.insert(
                    pointMapping.second.end(),
                    corners.begin(),
                    corners.end());
            } else if (!mOmitOtherTags) {
                computeTransformation(cv::format("tag_%d", tagId),
                                      mDefaultTagCorners,
                                      corners,
                                      objects);
            }

        } else if (!mOmitOtherTags) {
            computeTransformation(cv::format("tag_%d", tagId),
                                  mDefaultTagCorners,
                                  corners,
                                  objects);
        }
    }

    for (auto& objectToPoints : objectToPointMapping) {
        computeTransformation(objectToPoints.first,
                              objectToPoints.second.first,
                              cv::Mat_<cv::Point2f>(objectToPoints.second.second),
                              objects);
    }

    return mFilter(objects);
}

TagPoseMap estimate(
    const cv::Mat &inputImage,
    Chilitags::DetectionTrigger detectionTrigger) {
    return estimate(mChilitags.find(inputImage, detectionTrigger));
}

void setDefaultTagSize(RealT defaultSize){
    mDefaultTagCorners = {
        cv::Point3_<RealT>(0.f, 0.f, 0.f),
        cv::Point3_<RealT>(defaultSize, 0.f, 0.f),
        cv::Point3_<RealT>(defaultSize, defaultSize, 0.f),
        cv::Point3_<RealT>(0.f, defaultSize, 0.f),
    };
}

bool read3DConfiguration(const std::string &filenameOrString, bool omitOtherTags, bool readFromString) {
    mOmitOtherTags = omitOtherTags;

    int mode;
    if(readFromString)
        mode = cv::FileStorage::READ + cv::FileStorage::MEMORY;
    else
        mode = cv::FileStorage::READ;

    cv::FileStorage configuration(filenameOrString, mode);
    if (!configuration.isOpened()) {
        if(readFromString){
            std::cerr << "Could not read tag configuration: " << std::endl;
            std::cerr << filenameOrString << std::endl;
        }
        else
            std::cerr << "Could not open file: " << filenameOrString << std::endl;
        return false;
    }

    mId2Configuration.clear();
    for(const auto &objectConfig : configuration.root()) {
        for(const auto &tagConfig : objectConfig) {
            int id;
            tagConfig["tag"] >> id;
            float size;
            tagConfig["size"] >> size;
            int keep;
            tagConfig["keep"] >> keep;
            cv::Vec3f translation;
            cv::Vec3f rotation;
            for (int i : {0,1,2}) {
                tagConfig["translation"][i] >> translation[i];
                tagConfig["rotation"]   [i] >> rotation   [i];
            }

            mId2Configuration[id] = std::make_pair(
                objectConfig.name(),
                TagConfig(id, size, keep, cv::Vec3f(translation), cv::Vec3f(rotation)));
        }
    }

    return true;
}


/** Sets new camera calibration values.
 */
void setCalibration(cv::InputArray newCameraMatrix,
                    cv::InputArray newDistCoeffs){
    mCameraMatrix = newCameraMatrix.getMat();
    mDistCoeffs = newDistCoeffs.getMat();
}

cv::Size readCalibration(const std::string &filename) {
    cv::Size size;
    cv::FileStorage fs(filename, cv::FileStorage::READ);
    fs["image_width"]             >> size.width;
    fs["image_height"]            >> size.height;
    fs["distortion_coefficients"] >> mDistCoeffs;
    fs["camera_matrix"]           >> mCameraMatrix;

    if( mDistCoeffs.type() != CV_32F )
        mDistCoeffs = cv::Mat_<float>(mDistCoeffs);
    if( mCameraMatrix.type() != CV_32F )
        mCameraMatrix = cv::Mat_<float>(mCameraMatrix);

    return size;
}

const cv::Mat &getCameraMatrix()     const {return mCameraMatrix;}
const cv::Mat &getDistortionCoeffs() const{return mDistCoeffs;}

private:

struct TagConfig {
    TagConfig() :
        mId(-1),
        mSize(-1.f),
        mKeep(false),
        mCorners(4),
        mLocalcorners(4)
    {
    }

    TagConfig(int id, RealT size, bool keep, cv::Vec<RealT,3> translation, cv::Vec<RealT,3> rotation) :
        mId(id),
        mSize(size),
        mKeep(keep),
        mCorners(4),
        mLocalcorners(4)
    {
        mLocalcorners[0] = cv::Point3_<RealT>(0.f, 0.f, 0.f);
        mLocalcorners[1] = cv::Point3_<RealT>(size, 0.f, 0.f);
        mLocalcorners[2] = cv::Point3_<RealT>(size, size, 0.f);
        mLocalcorners[3] = cv::Point3_<RealT>(0.f, size, 0.f);


        // Rotation matrix computation: cf The Matrix and Quaternions FAQ
        // http://www.cs.princeton.edu/~gewang/projects/darth/stuff/quat_faq.html#Q36

        static const RealT DEG2RAD = 3.141593f / 180.f;
        auto A = cos(rotation[0] * DEG2RAD);
        auto B = sin(rotation[0] * DEG2RAD);
        auto C = cos(rotation[1] * DEG2RAD);
        auto D = sin(rotation[1] * DEG2RAD);
        auto E = cos(rotation[2] * DEG2RAD);
        auto F = sin(rotation[2] * DEG2RAD);

        TfMat transformation(
                   C*E ,        -C*F ,    D , translation[0] ,
             B*D*E+A*F ,  -B*D*F+A*E , -B*C , translation[1] ,
            -A*D*E+B*F ,   A*D*F+B*E ,  A*C , translation[2] ,
                    0.f,          0.f,   0.f, 1.f             );

        for (auto i : {0, 1, 2, 3}) {
            auto corner = transformation*cv::Matx<RealT, 4, 1>(mLocalcorners[i].x, mLocalcorners[i].y, 0.f, 1.f);
            mCorners[i] = cv::Point3_<RealT>(corner(0), corner(1), corner(2));
        }
    }

    int mId;
    float mSize;
    bool mKeep;

    // this array stores the 3D location of the
    // 4 corners of the tag *in the parent
    // object frame*. It is automatically computed.
    std::vector<cv::Point3_<RealT>> mCorners;

    // this array stores the 3D location of the
    // 4 corners of the tag *in the tag
    // own frame*. It is automatically computed.
    std::vector<cv::Point3_<RealT>> mLocalcorners;
};

void computeTransformation(const std::string& name,
                           const std::vector<cv::Point3_<RealT>>& objectPoints,
                           const cv::Mat_<cv::Point_<RealT>>& imagePoints,
                           TagPoseMap& objects) const
{
    // Rotation & translation vectors, computed by cv::solvePnP
    cv::Mat rotation, translation;

    // Find the 3D pose of our tag
    cv::solvePnP(objectPoints,
                 imagePoints,
                 mCameraMatrix, mDistCoeffs,
                 rotation, translation, false,
#ifdef OPENCV3
                 cv::SOLVEPNP_ITERATIVE);
#else
                 cv::ITERATIVE);
#endif

    //std::cout << rotation.size().width << " " << rotation.size().height << " " << translation.size().width << " " << translation.size().height << std::endl;

    cv::Matx33d rotMat;
    cv::Rodrigues(rotation, rotMat);

    objects[name] = {
        (RealT)rotMat(0,0) , (RealT)rotMat(0,1) , (RealT)rotMat(0,2) , (RealT)translation.at<double>(0) ,
        (RealT)rotMat(1,0) , (RealT)rotMat(1,1) , (RealT)rotMat(1,2) , (RealT)translation.at<double>(1) ,
        (RealT)rotMat(2,0) , (RealT)rotMat(2,1) , (RealT)rotMat(2,2) , (RealT)translation.at<double>(2) ,
                  0 ,           0 ,           0 ,                         1 ,
    };
}

Chilitags mChilitags;

bool mOmitOtherTags;

cv::Mat mCameraMatrix;
cv::Mat mDistCoeffs;
std::vector<cv::Point3_<RealT>> mDefaultTagCorners;

// associates a tag id with an object name and the configuration of the tag
// in this object
std::map<int, std::pair<std::string, TagConfig> > mId2Configuration;

Filter<std::string, TfMat> mFilter;
};

template<typename RealT>
void Chilitags3D<RealT>::setFilter(int persistence, float gain) {
    mImpl->setFilter(persistence, gain);
}

template<typename RealT>
Chilitags3D<RealT>::Chilitags3D(cv::Size cameraResolution) :
    mImpl(new Chilitags3D<RealT>::Impl(cameraResolution)){
}

template<typename RealT>
const Chilitags &Chilitags3D<RealT>::getChilitags() const {
    return mImpl->getChilitags();
}

template<typename RealT>
Chilitags &Chilitags3D<RealT>::getChilitags(){
    return mImpl->getChilitags();
}

template<typename RealT>
typename Chilitags3D<RealT>::TagPoseMap Chilitags3D<RealT>::estimate(
    const TagCornerMap &tags) {
    return mImpl->estimate(tags);
}

template<typename RealT>
typename Chilitags3D<RealT>::TagPoseMap Chilitags3D<RealT>::estimate(
    const cv::Mat &inputImage,
    Chilitags::DetectionTrigger detectionTrigger) {
    return mImpl->estimate(inputImage, detectionTrigger);
}

template<typename RealT>
void Chilitags3D<RealT>::setDefaultTagSize(RealT defaultSize){
    mImpl->setDefaultTagSize(defaultSize);
}

template<typename RealT>
bool Chilitags3D<RealT>::readTagConfiguration(const std::string &filenameOrString, bool omitOtherTags, bool readFromString){
    return mImpl->read3DConfiguration(filenameOrString, omitOtherTags, readFromString);
}

template<typename RealT>
void Chilitags3D<RealT>::setCalibration(
    cv::InputArray newCameraMatrix,
    cv::InputArray newDistCoeffs) {
    mImpl->setCalibration(newCameraMatrix, newDistCoeffs);
}

template<typename RealT>
cv::Size Chilitags3D<RealT>::readCalibration(const std::string &filename){
    return mImpl->readCalibration(filename);
}

template<typename RealT>
Chilitags3D<RealT>::~Chilitags3D() = default;

template<typename RealT>
const cv::Mat &Chilitags3D<RealT>::getCameraMatrix()     const {
    return mImpl->getCameraMatrix();}

template<typename RealT>
const cv::Mat &Chilitags3D<RealT>::getDistortionCoeffs() const {
    return mImpl->getDistortionCoeffs();}

//All possible instantiations of Chilitags3D
template class Chilitags3D<float>;
template class Chilitags3D<double>;

} /* namespace chilitags */

