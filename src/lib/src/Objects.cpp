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
#include <unordered_map>

namespace {

struct MarkerConfig {
	MarkerConfig(int id):id(id),corners(),localcorners(){}
    int id;
    float size = 0.;
    std::array<float, 3> translation = {{0., 0., 0.}};
    // the rotation is specified as a XYZ Euler rotation,
    // ie, first a rotation around X, then around Y, then around Z
    std::array<float, 3> rotation = {{0., 0., 0.}};
    bool keep = false;

    // this array stores the 3D location of the 
    // 4 corners of the marker *in the parent 
    // object frame*. It is automatically computed.
    std::array<cv::Point3f, 4> corners;

    // this array stores the 3D location of the 
    // 4 corners of the marker *in the marker 
    // own frame*. It is automatically computed.
    std::array<cv::Point3f, 4> localcorners;
};

struct Object {
	Object():name(),markers(){}
    std::string name;
    std::vector<MarkerConfig> markers;
};

/**
 * ObjectConfig reads and stores markers configurations.
 *
 * A marker configuration allows to associate a marker to
 * an object name (ie, alias) with possibly a 6D transformation.
 * It also allows to associate several markers to the same object,
 * for robust detection.
 */
class ObjectConfig {

public:
    ObjectConfig(const std::string& filename):
	_objects(),
	_markers()
	{

		if(filename.empty()) return; // nothing to load...

		cv::FileStorage configuration(filename, cv::FileStorage::READ);

		for(auto it=configuration.root().begin();
				 it!=configuration.root().end();
				 ++it) {

			Object object;

			object.name = (*it).name();

			for(auto marker=(*it).begin();marker!=(*it).end();++marker) {
				MarkerConfig config((*marker)["marker"]);

				config.size = (*marker)["size"];
				(*marker)["translation"][0] >> config.translation[0];
				(*marker)["translation"][1] >> config.translation[1];
				(*marker)["translation"][2] >> config.translation[2];
				(*marker)["rotation"][0] >> config.rotation[0];
				(*marker)["rotation"][1] >> config.rotation[1];
				(*marker)["rotation"][2] >> config.rotation[2];
				(*marker)["keep"] >> config.keep;

				computeCorners(config);

				object.markers.push_back(config);
			}

			_objects.push_back(object);

			// store the markers pointer only *after* the object is
			// stored in _objects, else we won't point to the correct
			// address.
			for (auto& m : _objects.back().markers) {
				_markers[m.id] = &m;
			}
		}


	}

    const Object* usedBy(int markerId) const{
		for (auto& o : _objects) {
			for (auto& m : o.markers) {
				// here, we return a pointer to an element of
				// a vector<Object> which is dangerous: if 
				// elements are added to the vector, it may
				// resize and the pointer would become invalid.
				// In our case it's however ok since _objects
				// is only modified at construction.
				if (m.id == markerId) return &o;
			}
		}
		return nullptr;
	}

    const MarkerConfig* marker(int markerId) const{
		return _markers.at(markerId);
	}

private:
    void computeCorners(MarkerConfig& marker) const {

		static const float DEG2RAD = 3.141593f / 180.f;

		marker.localcorners[0] = cv::Point3f(0.f        , 0.f        , 0.f);
		marker.localcorners[1] = cv::Point3f(marker.size, 0.f        , 0.f);
		marker.localcorners[2] = cv::Point3f(marker.size, marker.size, 0.f);
		marker.localcorners[3] = cv::Point3f(0.f        , marker.size, 0.f);


		// Rotation matrix computation: cf The Matrix and Quaternions FAQ
		// http://www.cs.princeton.edu/~gewang/projects/darth/stuff/quat_faq.html#Q36
		
		auto A = cos(marker.rotation[0] * DEG2RAD);
		auto B = sin(marker.rotation[0] * DEG2RAD);
		auto C = cos(marker.rotation[1] * DEG2RAD);
		auto D = sin(marker.rotation[1] * DEG2RAD);
		auto E = cos(marker.rotation[2] * DEG2RAD);
		auto F = sin(marker.rotation[2] * DEG2RAD);

		cv::Matx44f transformation(
				C*E,        -C*F,       D,    marker.translation[0],
				B*D*E+A*F,  -B*D*F+A*E, -B*C, marker.translation[1],
				-A*D*E+B*F, A*D*F+B*E,  A*C,  marker.translation[2],
				0.,         0.,         0.,   1.);

		for (auto i : {0, 1, 2, 3}) {
			cv::Matx41f corner(marker.localcorners[i].x,
						   marker.localcorners[i].y,
						   marker.localcorners[i].z,
						   1.0);
			auto tCorner = transformation * corner;
			marker.corners[i] = cv::Point3f(tCorner(0), tCorner(1), tCorner(2));
		}
	}

    std::vector<Object> _objects;
    std::unordered_map<int, const MarkerConfig*> _markers;

};



}

class chilitags::Objects::Impl {

public:
    Impl(cv::InputArray cameraMatrix, 
            cv::InputArray distCoeffs, 
            float size) :
	cameraMatrix(cameraMatrix.getMat()),
	distCoeffs(distCoeffs.getMat()),
	_config(""),
	hasObjectConfiguration(false)
	{
		init(size);
	}

    /**
     *
     * \param defaultSize: default size of markers, to be used for markers 
     * not associated to an object (ie, markers that are not used in the 
     * configuration file). The special value '0.0' (default value) means that
     * ONLY the markers used in the configuration file are tracked.
     */
    Impl(cv::InputArray cameraMatrix,
            cv::InputArray distCoeffs,
            const std::string& configuration, 
            float defaultSize = 0) :
	cameraMatrix(cameraMatrix.getMat()),
	distCoeffs(distCoeffs.getMat()),
	_config(configuration),
	hasObjectConfiguration(true)
	{
		init(defaultSize);
	}

    /** Returns the list of all detected objects with
     * their transformation matrices, in the camera
     * frame.
     */
    std::map<std::string, cv::Matx44d> operator()(const std::map<int, std::vector<cv::Point2f>> &tags) const {

		std::map<std::string, cv::Matx44d> objects;

		std::map<const Object*, std::vector<std::pair<int,std::vector<cv::Point2f>>>> tagsPerObject;
		std::vector<std::pair<int,std::vector<cv::Point2f>>> freeTags;

		/***********************************************
		 *    Find tags and associate them to objects
		 *    if necessary.
		 **********************************************/
		for (const auto &tag: tags) {
			auto object = _config.usedBy(tag.first);
			if (object) {
				tagsPerObject[object].push_back(tag);
			}
			else {
				freeTags.push_back(tag);
			}
		}



		/********************************************
		 *     Process free tags (ie, not part of an
		 *     object).
		 ********************************************/

		// defaultMarkerCorners is empty when the user does not
		// want to track free tags
		if (!defaultMarkerCorners.empty()) {
			for (auto& tag : freeTags) {

				std::string name(std::string("marker_") + std::to_string(tag.first));

				computeTransformation(name, 
									  defaultMarkerCorners,
									  tag.second,
									  objects);
			}
		}

		/********************************************
		 *     Process objects
		 ********************************************/
		for (auto& kv : tagsPerObject) {

			std::string name(kv.first->name);
			std::vector<cv::Point3f> corners;
			std::vector<cv::Point2f> imagePoints;

			for (auto& tag : kv.second) {

				const MarkerConfig* markerConfig = _config.marker(tag.first);

				// do we need to publish this marker independently of the object?
				if (markerConfig->keep) {
					std::vector<cv::Point3f> localcorners(markerConfig->localcorners.cbegin(),
												 markerConfig->localcorners.cend());
					computeTransformation(
										std::string("marker_") + std::to_string(tag.first), 
										localcorners,
										tag.second,
										objects);
				}

				// first, add the corners for the tag
				auto& newCorners = markerConfig->corners;
				corners.insert(corners.end(),newCorners.cbegin(),newCorners.cend());

				// then, add the image points where the tag is seen
				imagePoints.insert(imagePoints.end(),tag.second.cbegin(),tag.second.cend());

			}

			computeTransformation(name, corners, imagePoints, objects);

		}

		return objects;
	}

    /** Sets new camera calibration values.
     */
    void resetCalibration(cv::InputArray newCameraMatrix,
                          cv::InputArray newDistCoeffs){
		cameraMatrix = newCameraMatrix.getMat();
		distCoeffs = newDistCoeffs.getMat();
	}

private:
    void init(float size)
	{
		if (size > 0) {
			defaultMarkerCorners.push_back(cv::Point3f(0.,0.,0.));
			defaultMarkerCorners.push_back(cv::Point3f(size,0.,0.));
			defaultMarkerCorners.push_back(cv::Point3f(size,size,0.));
			defaultMarkerCorners.push_back(cv::Point3f(0.,size,0.));
		}
	}

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
    bool hasObjectConfiguration;
    std::vector<cv::Point3f> defaultMarkerCorners;

    ObjectConfig _config;
};

chilitags::Objects::Objects(
	cv::InputArray cameraMatrix, 
	cv::InputArray distCoeffs, 
	float size):
mImpl(new chilitags::Objects::Impl(cameraMatrix, distCoeffs, size)){}

chilitags::Objects::Objects(cv::InputArray cameraMatrix,
	cv::InputArray distCoeffs,
	const std::string& configuration, 
	float defaultSize):
mImpl(new chilitags::Objects::Impl(
		cameraMatrix, distCoeffs, configuration, defaultSize)){}

std::map<std::string, cv::Matx44d> chilitags::Objects::operator()(
	const std::map<int, std::vector<cv::Point2f>> &tags) const {
	return mImpl->operator()(tags);
}

void chilitags::Objects::resetCalibration(cv::InputArray newCameraMatrix,
                               cv::InputArray newDistCoeffs) {
	mImpl->resetCalibration(newCameraMatrix, newDistCoeffs);
}

chilitags::Objects::~Objects() = default;
