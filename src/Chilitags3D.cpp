/*******************************************************************************
*   Copyright 2013 EPFL                                                        *
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

#include <opencv2/calib3d/calib3d.hpp>

#include "chilitags.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp> //for FileStorage
#ifdef OPENCV3
#include <opencv2/core/utility.hpp>
#endif

namespace {

struct TagConfig {
    TagConfig() :
        mId(-1),
        mSize(-1.f),
        mKeep(false),
        mCorners(4),
        mLocalcorners(4)
    {
    }

    TagConfig(int id, float size, bool keep,
              cv::Vec3f translation, cv::Vec3f rotation
              ) :
        mId(id),
        mSize(size),
        mKeep(keep),
        mCorners(4),
        mLocalcorners(4)
    {
        mLocalcorners[0] = cv::Point3f(0.f, 0.f, 0.f);
        mLocalcorners[1] = cv::Point3f(size, 0.f, 0.f);
        mLocalcorners[2] = cv::Point3f(size, size, 0.f);
        mLocalcorners[3] = cv::Point3f(0.f, size, 0.f);


        // Rotation matrix computation: cf The Matrix and Quaternions FAQ
        // http://www.cs.princeton.edu/~gewang/projects/darth/stuff/quat_faq.html#Q36

        static const float DEG2RAD = 3.141593f / 180.f;
        auto A = cos(rotation[0] * DEG2RAD);
        auto B = sin(rotation[0] * DEG2RAD);
        auto C = cos(rotation[1] * DEG2RAD);
        auto D = sin(rotation[1] * DEG2RAD);
        auto E = cos(rotation[2] * DEG2RAD);
        auto F = sin(rotation[2] * DEG2RAD);

        cv::Matx44d transformation(
                   C*E ,        -C*F ,    D , translation[0] ,
             B*D*E+A*F ,  -B*D*F+A*E , -B*C , translation[1] ,
            -A*D*E+B*F ,   A*D*F+B*E ,  A*C , translation[2] ,
                    0. ,          0. ,   0. , 1.              );

        for (auto i : {0, 1, 2, 3}) {
            auto corner = transformation *
                           cv::Matx41d(mLocalcorners[i].x, mLocalcorners[i].y, 0.f, 1.f);
            mCorners[i] = cv::Point3f(corner(0), corner(1), corner(2));
        }
    }

    int mId;
    float mSize;
    bool mKeep;

    // this array stores the 3D location of the
    // 4 corners of the tag *in the parent
    // object frame*. It is automatically computed.
    std::vector<cv::Point3f> mCorners;

    // this array stores the 3D location of the
    // 4 corners of the tag *in the tag
    // own frame*. It is automatically computed.
    std::vector<cv::Point3f> mLocalcorners;
};

}

class chilitags::Chilitags3D::Impl {

public:
Impl(cv::Size cameraSize) :
    mChilitags(),
    mOmitOtherTags(false),
    mCameraMatrix(),
    mDistCoeffs(),
    mDefaultTagCorners(),
    mId2Configuration()
{
    double focalLength = 700.;
    mCameraMatrix = (cv::Mat_<double>(3,3) <<
        focalLength ,            0 , cameraSize.width /2,
                   0 , focalLength , cameraSize.height/2,
                   0,             0 , 1
    );
    setDefaultTagSize(1.f);
    mChilitags.setPersistence(0);
}

const Chilitags &getChilitags() const {
    return mChilitags;
}
      Chilitags &getChilitags()       {
    return mChilitags;
}

std::map<std::string, cv::Matx44d> estimate(
    std::map<int, std::vector<cv::Point2f> > tags) {

    std::map<std::string, cv::Matx44d> objects;

    std::map<
        const std::string,     //name of the object
        std::pair<
            std::vector<cv::Point3f>,      //points in object
            std::vector<cv::Point2f> > >   //points in frame
    objectToPointMapping;


    auto configurationIt = mId2Configuration.begin();
    auto configurationEnd = mId2Configuration.end();
    for (const auto &tag : tags) {
        int tagId = tag.first;
        while (configurationIt != configurationEnd
               && configurationIt->first < tagId)
            ++configurationIt;

        if (configurationIt != configurationEnd) {
            if (configurationIt->first == tagId) {
                const auto &configuration = configurationIt->second;
                if (configuration.second.mKeep) {
                    computeTransformation(cv::format("tag_%d", tagId),
                                          configuration.second.mLocalcorners,
                                          tag.second,
                                          objects);
                }
                auto & pointMapping = objectToPointMapping[configuration.first];
                pointMapping.first.insert(
                    pointMapping.first.end(),
                    configuration.second.mCorners.begin(),
                    configuration.second.mCorners.end());
                pointMapping.second.insert(
                    pointMapping.second.end(),
                    tag.second.begin(),
                    tag.second.end());
            } else if (!mOmitOtherTags) {
                computeTransformation(cv::format("tag_%d", tagId),
                                      mDefaultTagCorners,
                                      tag.second,
                                      objects);
            }

        } else if (!mOmitOtherTags) {
            computeTransformation(cv::format("tag_%d", tagId),
                                  mDefaultTagCorners,
                                  tag.second,
                                  objects);
        }
    }

    for (auto& objectToPoints : objectToPointMapping) {
        computeTransformation(
            objectToPoints.first,
            objectToPoints.second.first,
            objectToPoints.second.second,
            objects);
    }

    return objects;
}

std::map<std::string, cv::Matx44d> estimate(
    const cv::Mat &inputImage) {
    return estimate(mChilitags.find(inputImage));
}

void setDefaultTagSize(float defaultSize){
    mDefaultTagCorners = {
        cv::Point3f(0., 0., 0.),
        cv::Point3f(defaultSize, 0., 0.),
        cv::Point3f(defaultSize, defaultSize, 0.),
        cv::Point3f(0., defaultSize, 0.),
    };
}

void read3DConfiguration(const std::string &filename, bool omitOtherTags) {
    mOmitOtherTags = omitOtherTags;

    cv::FileStorage configuration(filename, cv::FileStorage::READ);
    if (!configuration.isOpened()) {
        std::cerr << "Could not open " << filename << std::endl;
        return;
    }

    mId2Configuration.clear();
    for(const auto &objectConfig : configuration.root()) {
        for(const auto &tagConfig : objectConfig) {
            int id;
            tagConfig["tag"] >> id;
            float size;
            tagConfig["size"] >> size;
            bool keep;
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

    if( mDistCoeffs.type() != CV_64F )
        mDistCoeffs = cv::Mat_<double>(mDistCoeffs);
    if( mCameraMatrix.type() != CV_64F )
        mCameraMatrix = cv::Mat_<double>(mCameraMatrix);

    return size;
}

private:
void computeTransformation(const std::string& name,
                           const std::vector<cv::Point3f>& corners,
                           const std::vector<cv::Point2f>& imagePoints,
                           std::map<std::string, cv::Matx44d>& objects) const
{
    // Rotation & translation vectors, computed by cv::solvePnP
    cv::Mat rotation, translation;

    // Find the 3D pose of our tag
    cv::solvePnP(corners,
                 imagePoints,
                 mCameraMatrix, mDistCoeffs,
                 rotation, translation, false,
                 cv::ITERATIVE);

    cv::Matx33d rotMat;
    cv::Rodrigues(rotation, rotMat);

    objects[name] = {
        rotMat(0,0) , rotMat(0,1) , rotMat(0,2) , translation.at<double>(0) ,
        rotMat(1,0) , rotMat(1,1) , rotMat(1,2) , translation.at<double>(1) ,
        rotMat(2,0) , rotMat(2,1) , rotMat(2,2) , translation.at<double>(2) ,
                   0 ,            0 ,            0 ,                          1 ,
    };
}

Chilitags mChilitags;

bool mOmitOtherTags;

cv::Mat mCameraMatrix;
cv::Mat mDistCoeffs;
std::vector<cv::Point3f> mDefaultTagCorners;

// associates a tag id with an object name and the configuration of the tag
// in this object
std::map<int, std::pair<std::string, TagConfig> > mId2Configuration;
};

chilitags::Chilitags3D::Chilitags3D(cv::Size cameraSize) :
    mImpl(new chilitags::Chilitags3D::Impl(cameraSize)){
}

const chilitags::Chilitags &chilitags::Chilitags3D::getChilitags() const {
    return mImpl->getChilitags();
}
chilitags::Chilitags &chilitags::Chilitags3D::getChilitags(){
    return mImpl->getChilitags();
}

std::map<std::string, cv::Matx44d> chilitags::Chilitags3D::estimate(
    std::map<int, std::vector<cv::Point2f> > tags) {
    return mImpl->estimate(tags);
}

std::map<std::string, cv::Matx44d> chilitags::Chilitags3D::estimate(
    const cv::Mat &inputImage) {
    return mImpl->estimate(inputImage);
}

void chilitags::Chilitags3D::setDefaultTagSize(float defaultSize){
    mImpl->setDefaultTagSize(defaultSize);
}

void chilitags::Chilitags3D::readTagConfiguration(const std::string &filename, bool omitOtherTags){
    mImpl->read3DConfiguration(filename, omitOtherTags);
}

void chilitags::Chilitags3D::setCalibration(
    cv::InputArray newCameraMatrix,
    cv::InputArray newDistCoeffs) {
    mImpl->setCalibration(newCameraMatrix, newDistCoeffs);
}
cv::Size chilitags::Chilitags3D::readCalibration(const std::string &filename){
    return mImpl->readCalibration(filename);
}

chilitags::Chilitags3D::~Chilitags3D() = default;
