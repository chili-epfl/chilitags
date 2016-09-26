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

#include "EstimatePose3D.hpp"

#include <iostream>
#include <opencv2/highgui/highgui.hpp> //for FileStorage
#ifdef OPENCV3
#include <opencv2/core/utility.hpp>
#endif

namespace chilitags {

template<typename RealT>
class Chilitags3D_<RealT>::Impl {

public:
Impl(cv::Size cameraResolution) :
    mChilitags(),
    mEstimatePose3D(cameraResolution),
    mOmitOtherTags(false),
    mDefaultTagCorners(),
    mId2Configuration()
{
    setDefaultTagSize(20.f);
    mChilitags.setFilter(0, 0.0f);
}

const Chilitags &getChilitags() const {
    return mChilitags;
}
Chilitags &getChilitags()       {
    return mChilitags;
}

TagPoseMap estimate(TagCornerMap const& tags, cv::Vec<RealT, 4> const& camDeltaR, cv::Vec<RealT, 3> const& camDeltaX)
{
    TagPoseMap objects;

    //Pass the latest camera movement difference for prediction (if 3D filtering is enabled)
    mEstimatePose3D.setCamDelta(camDeltaR, camDeltaX);

    //Predict pose for all known tags with camera movement (if 3D filtering is enabled)
    mEstimatePose3D(objects);

    //Correct pose prediction with new observations
    std::map<
        const std::string,     //name of the object
        std::pair<
            std::vector<cv::Point3_<RealT> >,      //points in object
            std::vector<cv::Point2f> > >   //points in frame
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
                    mEstimatePose3D(cv::format("tag_%d", tagId),
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
                mEstimatePose3D(cv::format("tag_%d", tagId),
                                mDefaultTagCorners,
                                corners,
                                objects);
            }

        } else if (!mOmitOtherTags) {
            mEstimatePose3D(cv::format("tag_%d", tagId),
                            mDefaultTagCorners,
                            corners,
                            objects);
        }
    }

    for (auto& objectToPoints : objectToPointMapping) {
        mEstimatePose3D(objectToPoints.first,
                        objectToPoints.second.first,
                        cv::Mat_<cv::Point2f>(objectToPoints.second.second),
                        objects);
    }

    return objects;
}

TagPoseMap estimate(
    const cv::Mat &inputImage,
    Chilitags::DetectionTrigger detectionTrigger,
    cv::Vec<RealT, 4> const& camDeltaR,
    cv::Vec<RealT, 3> const& camDeltaX) {
    return estimate(mChilitags.find(inputImage, detectionTrigger), camDeltaR, camDeltaX);
}

void setDefaultTagSize(RealT defaultSize){
    mDefaultTagCorners = {
        cv::Point3_<RealT>(0.f, 0.f, 0.f),
        cv::Point3_<RealT>(defaultSize, 0.f, 0.f),
        cv::Point3_<RealT>(defaultSize, defaultSize, 0.f),
        cv::Point3_<RealT>(0.f, defaultSize, 0.f),
    };
}

void enableFilter(bool enabled){
    mEstimatePose3D.enableFilter(enabled);
}

void setPersistence(RealT persistence){
    mEstimatePose3D.setFilterPersistence(persistence);
}

void setFilterProcessNoiseCovariance(cv::Mat const& covariance){
    mEstimatePose3D.setFilterProcessNoiseCovariance(covariance);
}

void setFilterObservationNoiseCovariance(cv::Mat const& covariance){
    mEstimatePose3D.setFilterObservationNoiseCovariance(covariance);
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
        if(readFromString) {
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
    mEstimatePose3D.setCameraCalibration(newCameraMatrix.getMat(), newDistCoeffs.getMat());
}

cv::Size readCalibration(const std::string &filename) {
    cv::Size size;
    cv::FileStorage fs(filename, cv::FileStorage::READ);
    cv::Mat distCoeffs, cameraMatrix;
    fs["image_width"]             >> size.width;
    fs["image_height"]            >> size.height;
    fs["distortion_coefficients"] >> distCoeffs;
    fs["camera_matrix"]           >> cameraMatrix;

    if( distCoeffs.type() != CV_32F )
        distCoeffs = cv::Mat_<float>(distCoeffs);
    if( cameraMatrix.type() != CV_32F )
        cameraMatrix = cv::Mat_<float>(cameraMatrix);
    mEstimatePose3D.setCameraCalibration(cameraMatrix, distCoeffs);

    return size;
}

const cv::Mat &getCameraMatrix()     const {
    return mEstimatePose3D.getCameraMatrix();
}
const cv::Mat &getDistortionCoeffs() const {
    return mEstimatePose3D.getDistortionCoeffs();
}

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

        TransformMatrix transformation(
            C*E,        -C*F,    D, translation[0],
            B*D*E+A*F,  -B*D*F+A*E, -B*C, translation[1],
            -A*D*E+B*F,   A*D*F+B*E,  A*C, translation[2],
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
    std::vector<cv::Point3_<RealT> > mCorners;

    // this array stores the 3D location of the
    // 4 corners of the tag *in the tag
    // own frame*. It is automatically computed.
    std::vector<cv::Point3_<RealT> > mLocalcorners;
};

Chilitags mChilitags;

EstimatePose3D<RealT> mEstimatePose3D;

bool mOmitOtherTags;

std::vector<cv::Point3_<RealT> > mDefaultTagCorners;

// associates a tag id with an object name and the configuration of the tag
// in this object
std::map<int, std::pair<std::string, TagConfig> > mId2Configuration;
};

template<typename RealT>
Chilitags3D_<RealT>::Chilitags3D_(cv::Size cameraResolution) :
    mImpl(new Chilitags3D_<RealT>::Impl(cameraResolution)){
}

template<typename RealT>
const Chilitags &Chilitags3D_<RealT>::getChilitags() const {
    return mImpl->getChilitags();
}

template<typename RealT>
Chilitags &Chilitags3D_<RealT>::getChilitags(){
    return mImpl->getChilitags();
}

template<typename RealT>
typename Chilitags3D_<RealT>::TagPoseMap Chilitags3D_<RealT>::estimate(
    const TagCornerMap &tags,
    cv::Vec<RealT, 4> const& camDeltaR,
    cv::Vec<RealT, 3> const& camDeltaX) {
    return mImpl->estimate(tags, camDeltaR, camDeltaX);
}

template<typename RealT>
typename Chilitags3D_<RealT>::TagPoseMap Chilitags3D_<RealT>::estimate(
    const cv::Mat &inputImage,
    Chilitags::DetectionTrigger detectionTrigger,
    cv::Vec<RealT, 4> const& camDeltaR,
    cv::Vec<RealT, 3> const& camDeltaX) {
    return mImpl->estimate(inputImage, detectionTrigger, camDeltaR, camDeltaX);
}

template<typename RealT>
void Chilitags3D_<RealT>::setDefaultTagSize(RealT defaultSize){
    mImpl->setDefaultTagSize(defaultSize);
}

template<typename RealT>
void Chilitags3D_<RealT>::enableFilter(bool enabled){
    mImpl->enableFilter(enabled);
}

template<typename RealT>
void Chilitags3D_<RealT>::setPersistence(RealT persistence){
    mImpl->setPersistence(persistence);
}

template<typename RealT>
void Chilitags3D_<RealT>::setFilterProcessNoiseCovariance(cv::Mat const& covariance){
    mImpl->setFilterProcessNoiseCovariance(covariance);
}

template<typename RealT>
void Chilitags3D_<RealT>::setFilterObservationNoiseCovariance(cv::Mat const& covariance){
    mImpl->setFilterObservationNoiseCovariance(covariance);
}

template<typename RealT>
bool Chilitags3D_<RealT>::readTagConfiguration(const std::string &filenameOrString, bool omitOtherTags, bool readFromString){
    return mImpl->read3DConfiguration(filenameOrString, omitOtherTags, readFromString);
}

template<typename RealT>
void Chilitags3D_<RealT>::setCalibration(
    cv::InputArray newCameraMatrix,
    cv::InputArray newDistCoeffs) {
    mImpl->setCalibration(newCameraMatrix, newDistCoeffs);
}

template<typename RealT>
cv::Size Chilitags3D_<RealT>::readCalibration(const std::string &filename){
    return mImpl->readCalibration(filename);
}

template<typename RealT>
Chilitags3D_<RealT>::~Chilitags3D_() = default;

template<typename RealT>
const cv::Mat &Chilitags3D_<RealT>::getCameraMatrix()     const {
    return mImpl->getCameraMatrix();
}

template<typename RealT>
const cv::Mat &Chilitags3D_<RealT>::getDistortionCoeffs() const {
    return mImpl->getDistortionCoeffs();
}

//All possible instantiations of Chilitags3D
template class Chilitags3D_<float>;
template class Chilitags3D_<double>;

} /* namespace chilitags */

