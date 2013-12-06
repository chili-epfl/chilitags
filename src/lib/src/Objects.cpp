#include <opencv2/calib3d/calib3d.hpp>

#include "Objects.hpp"

using namespace std;
using namespace cv;
using chilitags::Objects;

Objects::Objects(InputArray cameraMatrix, 
                 InputArray distCoeffs, 
                 float size):
                    cameraMatrix(cameraMatrix.getMat()),
                    distCoeffs(distCoeffs.getMat()),
                    _config(""),
                    hasObjectConfiguration(false)
{
    init(size);
}

Objects::Objects(InputArray cameraMatrix, 
                 InputArray distCoeffs, 
                 const string& configuration, 
                 float defaultSize):
                    cameraMatrix(cameraMatrix.getMat()),
                    distCoeffs(distCoeffs.getMat()),
                    _config(configuration),
                    hasObjectConfiguration(true)
{
    init(defaultSize);
}

void Objects::init(float size)
{
    if (size > 0) {
        defaultMarkerCorners.push_back(Point3f(0.,0.,0.));
        defaultMarkerCorners.push_back(Point3f(size,0.,0.));
        defaultMarkerCorners.push_back(Point3f(size,size,0.));
        defaultMarkerCorners.push_back(Point3f(0.,size,0.));
    }
}

void Objects::resetCalibration(cv::InputArray newCameraMatrix,
                               cv::InputArray newDistCoeffs)
{
    cameraMatrix = newCameraMatrix.getMat();
    distCoeffs = newDistCoeffs.getMat();
}

map<string, Matx44d> Objects::operator()(const std::map<int, std::vector<cv::Point2f>> &tags) const
{

    map<string, Matx44d> objects;

    map<const Object*, vector<std::pair<int,std::vector<cv::Point2f>>>> tagsPerObject;
    vector<std::pair<int,std::vector<cv::Point2f>>> freeTags;

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

            string name(string("marker_") + to_string(tag.first));

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

        string name(kv.first->name);
        vector<Point3f> corners;
        vector<Point2f> imagePoints;

        for (auto& tag : kv.second) {

            const MarkerConfig* markerConfig = _config.marker(tag.first);

            // do we need to publish this marker independently of the object?
            if (markerConfig->keep) {
                vector<Point3f> localcorners(markerConfig->localcorners.cbegin(),
                                             markerConfig->localcorners.cend());
                computeTransformation(
                                    string("marker_") + to_string(tag.first), 
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

void Objects::computeTransformation(const string& name,
                                    const vector<Point3f>& corners,
                                    const vector<Point2f>& imagePoints,
                                    map<string, Matx44d>& objects) const
{
        // Rotation & translation vectors, computed by cv::solvePnP
        Mat rvec, tvec;
        
        // Find the 3D pose of our marker
        solvePnP(corners,
                imagePoints,
                cameraMatrix, distCoeffs,
                rvec, tvec, false,
                cv::ITERATIVE);

		Matx33d rotation;
		Rodrigues(rvec, rotation);

        objects[name] = {
			rotation(0,0), rotation(0,1), rotation(0,2), tvec.at<double>(0),
			rotation(1,0), rotation(1,1), rotation(1,2), tvec.at<double>(1),
			rotation(2,0), rotation(2,1), rotation(2,2), tvec.at<double>(2),
			0            , 0            , 0            , 1                 ,
		};
}
