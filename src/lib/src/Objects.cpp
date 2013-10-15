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
                    hasObjectConfiguration(false),
					defaultMarkerCorners(),
					estimations()
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
                    hasObjectConfiguration(true),
					defaultMarkerCorners(),
					estimations()

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
	for (auto kv = estimations.begin(); kv != estimations.end(); ) {
		if (kv->second.getMeasurementAge() > persistence) {
			kv = estimations.erase(kv);
		}
		else {
			kv->second.predict();
			++kv;
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

            updateTransformation(name, 
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
                updateTransformation(
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

        updateTransformation(name, corners, imagePoints);

    }

}

void Objects::updateTransformation(const string& name,
                                    const vector<Point3f>& corners,
                                    const vector<Point2f>& imagePoints) 
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


		auto entry = estimations.find(name);

		if (entry == estimations.end()) {
			entry = estimations.insert(std::make_pair(name,
				Estimator(tvec, rvec))).first;
		}

		entry->second.correct(tvec, rvec);
}

map<string, Matx44f> Objects::all() const
{
    map<string, Matx44f> objects;
    for (auto& kv : estimations) {
		objects[kv.first] = kv.second.transformationMatrix();
	}

    return objects;
}
