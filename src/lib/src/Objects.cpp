#include <opencv2/calib3d/calib3d.hpp>

#include "Chilitag.hpp"
#include "Objects.hpp"

// maximum of objects or tags that can be tracked. Must be =<1024
#define MAX_OBJECTS 1024

using namespace std;
using namespace cv;
using namespace chilitags;

Objects::Objects(InputArray cameraMatrix, 
                 InputArray distCoeffs, 
                 float size,
                 int persistence):
                    cameraMatrix(cameraMatrix.getMat()),
                    distCoeffs(distCoeffs.getMat()),
                    _config(""),
                    persistence(persistence),
                    hasObjectConfiguration(false)
{
    init(size);
}

Objects::Objects(InputArray cameraMatrix, 
                 InputArray distCoeffs, 
                 const string& configuration, 
                 float defaultSize,
                 int persistence):
                    cameraMatrix(cameraMatrix.getMat()),
                    distCoeffs(distCoeffs.getMat()),
                    _config(configuration),
                    persistence(persistence),
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

void Objects::update() {

    /******************************************************************
     * Remove estimators of objects that have no been seen for too long
	 * and notify the others of the new frame
     *****************************************************************/
	for (auto t = estimatedTranslations.begin(),
			r = estimatedRotations.begin();
		t != estimatedTranslations.end(); ) {
		if ((*t).second.getMeasurementAge() > persistence) {
			t = estimatedTranslations.erase(t);
			r = estimatedRotations.erase(r);
		}
		else {
			(*t).second.predict();
			++t;
			(*r).second.predict();
			++r;
		}
	}

    /***********************************************
     *    Find tags and associate them to objects
     *    if necessary.
     **********************************************/

    map<const Object*, vector<Chilitag>> tagsPerObject;
    vector<Chilitag> freeTags;

    for (int i = 0; i < MAX_OBJECTS; ++i)
    {
		// We set the tag to not persist at all,
		// as we will handle persistence manually along with the filter.
        Chilitag tag(i, 0);

        if (tag.isPresent()) {
            auto object = _config.usedBy(i);
            if (object) {
                tagsPerObject[object].push_back(tag);
            }
            else {
                freeTags.push_back(tag);
            }
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

            string name(string("marker_") + to_string(tag.GetMarkerId()));

            computeTransformation(name, 
                                  defaultMarkerCorners,
                                  tag.getCorners().toVector());
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

            const MarkerConfig* markerConfig = _config.marker(tag.GetMarkerId());

            // do we need to publish this marker independently of the object?
            if (markerConfig->keep) {
                vector<Point3f> localcorners(markerConfig->localcorners.cbegin(),
                                             markerConfig->localcorners.cend());
                computeTransformation(
                                    string("marker_") + to_string(tag.GetMarkerId()), 
                                    localcorners,
                                    tag.getCorners().toVector());
            }

            // first, add the corners for the tag
            auto& newCorners = markerConfig->corners;
            corners.insert(corners.end(),newCorners.cbegin(),newCorners.cend());

            // then, add the image points where the tag is seen
            auto newPoints(tag.getCorners().toVector());
            imagePoints.insert(imagePoints.end(),newPoints.cbegin(),newPoints.cend());

        }

        computeTransformation(name, corners, imagePoints);

    }

}

map<string, Matx44f> Objects::all() const
{
    map<string, Matx44f> objects;
	vector<string> toErase;
    for (auto& kv : estimatedTranslations) {
		objects[kv.first] = transformationMatrix(
			kv.second.getEstimation(),
			estimatedRotations.at(kv.first).getEstimation());
	}

    return objects;
}

void Objects::computeTransformation(const string& name,
                                    const vector<Point3f>& corners,
                                    const vector<Point2f>& imagePoints) const
{
        // Rotation & translation vectors, computed by cv::solvePnP
        Mat rvec, tvec;

        // Find the 3D pose of our marker
        solvePnP(corners,
                imagePoints,
                cameraMatrix, distCoeffs,
                rvec, tvec, false,
                cv::ITERATIVE);
		rvec = Mat_<float>(rvec);
		tvec = Mat_<float>(tvec);

		estimatedTranslations.emplace(name, tvec);
		estimatedRotations.emplace(name, rvec);

        estimatedTranslations.at(name).correct(tvec);
        estimatedRotations.at(name).correct(rvec);
}

cv::Matx44f Objects::transformationMatrix(const cv::Mat& tvec, const cv::Mat& rvec) const
{
    Matx33f rotation;
    Rodrigues(rvec, rotation);

    Matx44f trans;

    // how to do that in an OpenCV way??
    trans(0,0) = rotation(0,0);
    trans(0,1) = rotation(0,1);
    trans(0,2) = rotation(0,2);
    trans(1,0) = rotation(1,0);
    trans(1,1) = rotation(1,1);
    trans(1,2) = rotation(1,2);
    trans(2,0) = rotation(2,0);
    trans(2,1) = rotation(2,1);
    trans(2,2) = rotation(2,2);
    trans(0,3) = tvec.at<float>(0);
    trans(1,3) = tvec.at<float>(1);
    trans(2,3) = tvec.at<float>(2);
    trans(3,3) = 1;

    return trans;
}

