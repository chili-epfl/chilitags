
#ifndef Objects_HPP
#define Objects_HPP

#include <string>
#include <map>
#include <unordered_map>

#include <opencv2/core/core.hpp>

#include "ObjectConfig.hpp"
#include "Estimator.hpp"


namespace chilitags {


class Objects {

public:

	/**
	* Default number of frames during which an object is tracked after it
	* has disappeared. This corresponds to how much tracking will "fill
	* the holes" of the detection
	*/
	static const int DEFAULT_PERSISTENCE = 30;

    Objects(cv::InputArray cameraMatrix, 
            cv::InputArray distCoeffs, 
            float size,
            int persistence = DEFAULT_PERSISTENCE);

    /**
     *
     * \param defaultSize: default size of markers, to be used for markers 
     * not associated to an object (ie, markers that are not used in the 
     * configuration file). The special value '0.0' (default value) means that
     * ONLY the markers used in the configuration file are tracked.
     */
    Objects(cv::InputArray cameraMatrix,
            cv::InputArray distCoeffs,
            const std::string& configuration, 
            float defaultSize = 0,
            int persistence = DEFAULT_PERSISTENCE);
	
	/** Use this method to notify a new frame containing objects to track.
	 * It will take care of updating the tracking data for each object,
	 * and filtering/predicting them.
     */
	void update();

    /** Returns the list of all detected objects with
     * their transformation matrices, in the camera
     * frame.
     */
    std::map<std::string, cv::Matx44f> all() const;

    /** Sets new camera calibration values.
     */
    void resetCalibration(cv::InputArray newCameraMatrix,
                          cv::InputArray newDistCoeffs);

    int nbTrackedObjects() const {return _config.objects().size();}
    int nbTrackedMarkers() const {return _config.nbMarkers();}

private:
    void init(float size);

    cv::Mat cameraMatrix;
    cv::Mat distCoeffs;

    ObjectConfig _config;
    
    int persistence;
    bool hasObjectConfiguration;
    std::vector<cv::Point3f> defaultMarkerCorners;

    void updateTransformation(const std::string& name,
                               const std::vector<cv::Point3f>& corners,
                               const std::vector<cv::Point2f>& imagePoints);

    // store, for each tag, a pair of estimators ;
	// the first one for translations, the second one for rotations
    std::unordered_map<std::string, Estimator> estimations;

};

}

#endif
