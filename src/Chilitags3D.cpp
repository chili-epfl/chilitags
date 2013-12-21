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

struct MarkerConfig {
	MarkerConfig():
	mId(-1),
	mSize(-1.f),
	mKeep(false),
	mCorners(4),
	mLocalcorners(4)
	{}

	MarkerConfig(int pId, float pSize, bool pKeep,
		cv::Vec3f pTranslation, cv::Vec3f pRotation
	):
	mId(pId),
	mSize(pSize),
	mKeep(pKeep),
	mCorners(4),
	mLocalcorners(4)
	{
		mLocalcorners[0] = cv::Point3f(0.f , 0.f , 0.f);
		mLocalcorners[1] = cv::Point3f(pSize, 0.f , 0.f);
		mLocalcorners[2] = cv::Point3f(pSize, pSize, 0.f);
		mLocalcorners[3] = cv::Point3f(0.f , pSize, 0.f);


		// Rotation matrix computation: cf The Matrix and Quaternions FAQ
		// http://www.cs.princeton.edu/~gewang/projects/darth/stuff/quat_faq.html#Q36
		
		static const float DEG2RAD = 3.141593f / 180.f;
		auto A = cos(pRotation[0] * DEG2RAD);
		auto B = sin(pRotation[0] * DEG2RAD);
		auto C = cos(pRotation[1] * DEG2RAD);
		auto D = sin(pRotation[1] * DEG2RAD);
		auto E = cos(pRotation[2] * DEG2RAD);
		auto F = sin(pRotation[2] * DEG2RAD);

		cv::Matx44d tTransformation(
				C*E,        -C*F,       D,    pTranslation[0],
				B*D*E+A*F,  -B*D*F+A*E, -B*C, pTranslation[1],
				-A*D*E+B*F, A*D*F+B*E,  A*C,  pTranslation[2],
				0.,         0.,         0.,   1.);

		for (auto i : {0, 1, 2, 3}) {
			auto tCorner = tTransformation *
				cv::Matx41d(mLocalcorners[i].x, mLocalcorners[i].y, 0.f, 1.f);
			mCorners[i] = cv::Point3f(tCorner(0), tCorner(1), tCorner(2));
		}
	}

    int mId;
    float mSize;
    bool mKeep;

    // this array stores the 3D location of the 
    // 4 corners of the marker *in the parent 
    // object frame*. It is automatically computed.
    std::vector<cv::Point3f> mCorners;

    // this array stores the 3D location of the 
    // 4 corners of the marker *in the marker 
    // own frame*. It is automatically computed.
    std::vector<cv::Point3f> mLocalcorners;
};

}

class chilitags::Chilitags3D::Impl {

public:
    Impl(cv::Size pCameraSize) :
	mChilitags(),
	mOmitOtherMarkers(false),
	mCameraMatrix(),
	mDistCoeffs(),
	mDefaultMarkerCorners(),
	mId2Configuration()
	{
		double tFocalLength = 700.;
		mCameraMatrix = (cv::Mat_<double>(3,3) << 
			tFocalLength,            0,pCameraSize.width /2,
			           0, tFocalLength,pCameraSize.height/2,
			           0,            0,1
		);
		setDefaultTagSize(1.f);
		mChilitags.setPersistence(0);
	}

	const Chilitags &getChilitags() const {return mChilitags;}
	      Chilitags &getChilitags()       {return mChilitags;}

    std::map<std::string, cv::Matx44d> findPose(
		std::map<int, std::vector<cv::Point2f>> pTags) const {

		std::map<std::string, cv::Matx44d> tObjects;

		std::map<
			const std::string, //name of the object
			std::pair<
				std::vector<cv::Point3f>,  //points in object
				std::vector<cv::Point2f>>> //points in frame
			tObjectToPointMapping;


		auto tConfigurationIt = mId2Configuration.begin();
		auto tConfigurationEnd = mId2Configuration.end();
		for (const auto &tTag: pTags) {
			int tTagId = tTag.first;
			while (tConfigurationIt != tConfigurationEnd
				&& tConfigurationIt->first < tTagId)
				++tConfigurationIt;

			if (tConfigurationIt != tConfigurationEnd) {
				if (tConfigurationIt->first == tTagId) {
					const auto &tConfiguration = tConfigurationIt->second;
					if (tConfiguration.second.mKeep) {
						computeTransformation(cv::format("marker_%d", tTagId),
											  tConfiguration.second.mLocalcorners,
											  tTag.second,
											  tObjects);
					}
					auto & tPointMapping = tObjectToPointMapping[tConfiguration.first];
					tPointMapping.first.insert(
						tPointMapping.first.end(),
						tConfiguration.second.mCorners.begin(),
						tConfiguration.second.mCorners.end());
					tPointMapping.second.insert(
						tPointMapping.second.end(),
						tTag.second.begin(),
						tTag.second.end());
				} else if (!mOmitOtherMarkers) {
					computeTransformation(cv::format("marker_%d", tTagId), 
										  mDefaultMarkerCorners,
										  tTag.second,
										  tObjects);
				}

			} else if (!mOmitOtherMarkers) {
				computeTransformation(cv::format("marker_%d", tTagId), 
									  mDefaultMarkerCorners,
									  tTag.second,
									  tObjects);
			}
		}

		for (auto& tObjectToPoints : tObjectToPointMapping) {
			computeTransformation(
				tObjectToPoints.first,
				tObjectToPoints.second.first,
				tObjectToPoints.second.second,
				tObjects);
		}

		return tObjects;
	}

    std::map<std::string, cv::Matx44d> findPose(
		const cv::Mat &pInputImage) const {
		return findPose(mChilitags.find(pInputImage));
	}

	void setDefaultTagSize(float pDefaultSize){
		mDefaultMarkerCorners = {
			cv::Point3f(0., 0., 0.),
			cv::Point3f(pDefaultSize, 0., 0.),
			cv::Point3f(pDefaultSize, pDefaultSize, 0.),
			cv::Point3f(0., pDefaultSize, 0.),
		};
	}

	void read3DConfiguration(const std::string &pFilename, bool pOmitOtherMarkers) {
		mOmitOtherMarkers = pOmitOtherMarkers;

		cv::FileStorage tConfiguration(pFilename, cv::FileStorage::READ);
		if (!tConfiguration.isOpened()) {
			std::cerr << "Could not open " << pFilename << std::endl;
			return;
		}

		mId2Configuration.clear();
		for(const auto &tObjectConfig : tConfiguration.root()) {
			for(const auto &tMarkerConfig : tObjectConfig) {
				int tId;
				tMarkerConfig["marker"] >> tId;
				float tSize;
				tMarkerConfig["size"] >> tSize;
				bool tKeep;
				tMarkerConfig["keep"] >> tKeep;
				cv::Vec3f tTranslation;
				cv::Vec3f tRotation;
				for (int i:{0,1,2}) {
					tMarkerConfig["translation"][i] >> tTranslation[i];
					tMarkerConfig["rotation"]   [i] >> tRotation   [i];
				}

				mId2Configuration[tId] = std::make_pair(
					tObjectConfig.name(), 
					MarkerConfig(tId, tSize, tKeep, cv::Vec3f(tTranslation), cv::Vec3f(tRotation)));
			}
		}
	}


    /** Sets new camera calibration values.
     */
    void setCalibration(cv::InputArray pNewCameraMatrix,
                        cv::InputArray pNewDistCoeffs){
		mCameraMatrix = pNewCameraMatrix.getMat();
		mDistCoeffs = pNewDistCoeffs.getMat();
	}

	cv::Size readCalibration(const std::string &pFilename) {
		cv::Size tSize;
		cv::FileStorage fs(pFilename, cv::FileStorage::READ);
		fs["image_width"]             >> tSize.width;
		fs["image_height"]            >> tSize.height;
		fs["distortion_coefficients"] >> mDistCoeffs;
		fs["camera_matrix"]           >> mCameraMatrix;

		if( mDistCoeffs.type() != CV_64F )
			mDistCoeffs = cv::Mat_<double>(mDistCoeffs);
		if( mCameraMatrix.type() != CV_64F )
			mCameraMatrix = cv::Mat_<double>(mCameraMatrix);

		return tSize;
	}

private:
	void computeTransformation(const std::string& pName,
							   const std::vector<cv::Point3f>& pCorners,
							   const std::vector<cv::Point2f>& pImagePoints,
							   std::map<std::string, cv::Matx44d>& pObjects) const
	{
			// Rotation & translation vectors, computed by cv::solvePnP
			cv::Mat tRotation, tTranslation;
			
			// Find the 3D pose of our marker
			cv::solvePnP(pCorners,
					pImagePoints,
					mCameraMatrix, mDistCoeffs,
					tRotation, tTranslation, false,
					cv::ITERATIVE);

			cv::Matx33d tRotMat;
			cv::Rodrigues(tRotation, tRotMat);

			pObjects[pName] = {
				tRotMat(0,0), tRotMat(0,1), tRotMat(0,2), tTranslation.at<double>(0),
				tRotMat(1,0), tRotMat(1,1), tRotMat(1,2), tTranslation.at<double>(1),
				tRotMat(2,0), tRotMat(2,1), tRotMat(2,2), tTranslation.at<double>(2),
				0           , 0           , 0           , 1                         ,
			};
	}

	Chilitags mChilitags;

	bool mOmitOtherMarkers;

    cv::Mat mCameraMatrix;
    cv::Mat mDistCoeffs;
    std::vector<cv::Point3f> mDefaultMarkerCorners;

	// associates a tag id with an object name and the configuration of the tag
	// in this object
	std::map<int, std::pair<std::string, MarkerConfig>> mId2Configuration;
};

chilitags::Chilitags3D::Chilitags3D(cv::Size pCameraSize):
mImpl(new chilitags::Chilitags3D::Impl(pCameraSize)){}

const chilitags::Chilitags &chilitags::Chilitags3D::getChilitags() const{
	return mImpl->getChilitags();
}
chilitags::Chilitags &chilitags::Chilitags3D::getChilitags(){
	return mImpl->getChilitags();
}

std::map<std::string, cv::Matx44d> chilitags::Chilitags3D::findPose(
	std::map<int, std::vector<cv::Point2f>> pTags) const {
	return mImpl->findPose(pTags);
}

std::map<std::string, cv::Matx44d> chilitags::Chilitags3D::findPose(
	const cv::Mat &pInputImage) const {
	return mImpl->findPose(pInputImage);
}

void chilitags::Chilitags3D::setDefaultTagSize(float pDefaultSize){
	mImpl->setDefaultTagSize(pDefaultSize);
}

void chilitags::Chilitags3D::read3DConfiguration(const std::string &pFilename, bool pOmitOtherMarkers){
	mImpl->read3DConfiguration(pFilename, pOmitOtherMarkers);
}

void chilitags::Chilitags3D::setCalibration(
	cv::InputArray pNewCameraMatrix,
	cv::InputArray pNewDistCoeffs) {
	mImpl->setCalibration(pNewCameraMatrix, pNewDistCoeffs);
}
cv::Size chilitags::Chilitags3D::readCalibration(const std::string &pFilename){
	return mImpl->readCalibration(pFilename);
}

chilitags::Chilitags3D::~Chilitags3D() = default;
