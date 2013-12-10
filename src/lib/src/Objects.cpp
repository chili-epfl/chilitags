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

#include "Objects.hpp"
#include <iostream>
#include <opencv2/core/utility.hpp>

namespace {

struct MarkerConfig {
	MarkerConfig(){}

	MarkerConfig(int id, float size, bool keep,
		cv::Vec3f translation, cv::Vec3f rotation
	):
	id(id),
	size(size),
	keep(keep),
	corners(4),
	localcorners(4)
	{
		localcorners[0] = cv::Point3f(0.f , 0.f , 0.f);
		localcorners[1] = cv::Point3f(size, 0.f , 0.f);
		localcorners[2] = cv::Point3f(size, size, 0.f);
		localcorners[3] = cv::Point3f(0.f , size, 0.f);


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
				C*E,        -C*F,       D,    translation[0],
				B*D*E+A*F,  -B*D*F+A*E, -B*C, translation[1],
				-A*D*E+B*F, A*D*F+B*E,  A*C,  translation[2],
				0.,         0.,         0.,   1.);

		for (auto i : {0, 1, 2, 3}) {
			cv::Matx41d corner(localcorners[i].x, localcorners[i].y, 0.f, 1.f);
			auto tCorner = transformation * corner;
			corners[i] = cv::Point3f(tCorner(0), tCorner(1), tCorner(2));
		}
	}

    int id;
    float size;
    bool keep;

    // this array stores the 3D location of the 
    // 4 corners of the marker *in the parent 
    // object frame*. It is automatically computed.
    std::vector<cv::Point3f> corners;

    // this array stores the 3D location of the 
    // 4 corners of the marker *in the marker 
    // own frame*. It is automatically computed.
    std::vector<cv::Point3f> localcorners;
};

}

class chilitags::Objects::Impl {

public:
    Impl(float pMarkerSize, const std::string& filename) :
	cameraMatrix(cv::Mat::eye(3, 3, CV_64F)),
	distCoeffs(cv::Mat::zeros(5, 1, CV_64F))
	{
		if (pMarkerSize > 0) {
			defaultMarkerCorners.push_back(cv::Point3f(0., 0., 0.));
			defaultMarkerCorners.push_back(cv::Point3f(pMarkerSize, 0., 0.));
			defaultMarkerCorners.push_back(cv::Point3f(pMarkerSize, pMarkerSize, 0.));
			defaultMarkerCorners.push_back(cv::Point3f(0., pMarkerSize, 0.));
		}

		if (filename.empty()) return;

		cv::FileStorage configuration(filename, cv::FileStorage::READ);
		if (!configuration.isOpened()) {
			std::cerr << "Could not open " << filename << std::endl;
			return;
		}

		for(const auto &tObjectConfig : configuration.root()) {
			for(const auto &tMarkerConfig : tObjectConfig) {
				int tId;
				tMarkerConfig["marker"] >> tId;
				float tSize;
				tMarkerConfig["size"] >> tSize;
				bool keep;
				tMarkerConfig["keep"] >> keep;
				cv::Vec3f translation;
				tMarkerConfig["translation"] >> translation;
				cv::Vec3f rotation;
				tMarkerConfig["rotation"] >> rotation;

				mId2Configuration[tId] = std::make_pair(
					tObjectConfig.name(), 
					MarkerConfig(tId, tSize, keep, translation, rotation));
			}
		}
	}

    std::map<std::string, cv::Matx44d> operator()(
		const std::map<int, std::vector<cv::Point2f>> &tags) const {

		std::map<std::string, cv::Matx44d> objects;

		std::map<
			const std::string, //name of the object
			std::pair<
				std::vector<cv::Point3f>,  //points in object
				std::vector<cv::Point2f>>> //points in frame
			tObjectToPointMapping;


		auto tConfigurationIt = mId2Configuration.begin();
		auto tConfigurationEnd = mId2Configuration.end();
		for (const auto &tag: tags) {
			int tTagId = tag.first;
			while (tConfigurationIt != tConfigurationEnd
				&& tConfigurationIt->first < tTagId)
				++tConfigurationIt;

			if (tConfigurationIt != tConfigurationEnd) {
				if (tConfigurationIt->first == tTagId) {
					const auto &tConfiguration = tConfigurationIt->second;
					if (tConfiguration.second.keep) {
						computeTransformation(cv::format("marker_%d", tTagId),
											  tConfiguration.second.localcorners,
											  tag.second,
											  objects);
					}
					auto & tPointMapping = tObjectToPointMapping[tConfiguration.first];
					tPointMapping.first.insert(
						tPointMapping.first.end(),
						tConfiguration.second.corners.begin(),
						tConfiguration.second.corners.end());
					tPointMapping.second.insert(
						tPointMapping.second.end(),
						tag.second.begin(),
						tag.second.end());
				} else if (!defaultMarkerCorners.empty()) {
					//i.e. we also want tags not in the config file
					computeTransformation(cv::format("marker_%d", tTagId), 
										  defaultMarkerCorners,
										  tag.second,
										  objects);
				}

			} else if (!defaultMarkerCorners.empty()) {
				computeTransformation(cv::format("marker_%d", tTagId), 
									  defaultMarkerCorners,
									  tag.second,
									  objects);
			}
		}

		for (auto& kv : tObjectToPointMapping) {
			computeTransformation(
				kv.first,
				kv.second.first,
				kv.second.second,
				objects);
		}

		return objects;
	}

    /** Sets new camera calibration values.
     */
    void setCalibration(cv::InputArray newCameraMatrix,
                          cv::InputArray newDistCoeffs){
		cameraMatrix = newCameraMatrix.getMat();
		distCoeffs = newDistCoeffs.getMat();
	}

private:
	void computeTransformation(const std::string& name,
							   const std::vector<cv::Point3f>& corners,
							   const std::vector<cv::Point2f>& imagePoints,
							   std::map<std::string, cv::Matx44d>& objects) const
	{
			// Rotation & translation vectors, computed by cv::solvePnP
			cv::Mat rvec, tvec;
			
			// Find the 3D pose of our marker
			cv::solvePnP(corners,
					imagePoints,
					cameraMatrix, distCoeffs,
					rvec, tvec, false,
					cv::ITERATIVE);

			cv::Matx33d rotation;
			cv::Rodrigues(rvec, rotation);

			objects[name] = {
				rotation(0,0), rotation(0,1), rotation(0,2), tvec.at<double>(0),
				rotation(1,0), rotation(1,1), rotation(1,2), tvec.at<double>(1),
				rotation(2,0), rotation(2,1), rotation(2,2), tvec.at<double>(2),
				0            , 0            , 0            , 1                 ,
			};
	}


    cv::Mat cameraMatrix;
    cv::Mat distCoeffs;
    std::vector<cv::Point3f> defaultMarkerCorners;

	// associates a tag id with an object name and the configuration of the tag
	// in this object
	std::map<int, std::pair<std::string, MarkerConfig>> mId2Configuration;
};

chilitags::Objects::Objects(
	float defaultSize,
	const std::string& configuration):
mImpl(new chilitags::Objects::Impl(defaultSize, configuration)){}

std::map<std::string, cv::Matx44d> chilitags::Objects::operator()(
	const std::map<int, std::vector<cv::Point2f>> &tags) const {
	return mImpl->operator()(tags);
}

void chilitags::Objects::setCalibration(
	cv::InputArray newCameraMatrix,
	cv::InputArray newDistCoeffs) {
	mImpl->setCalibration(newCameraMatrix, newDistCoeffs);
}

chilitags::Objects::~Objects() = default;
