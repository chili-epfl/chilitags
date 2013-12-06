
#ifndef Objects_HPP
#define Objects_HPP

#include <string>
#include <map>
#include <unordered_map>

#include <opencv2/core/core.hpp>

#include "ObjectConfig.hpp"

namespace chilitags {

class Objects {

public:
    Objects(cv::InputArray cameraMatrix, 
            cv::InputArray distCoeffs, 
            float size);

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
            float defaultSize = 0);

    /** Returns the list of all detected objects with
     * their transformation matrices, in the camera
     * frame.
     */
    std::map<std::string, cv::Matx44d> operator()(const std::map<int, std::vector<cv::Point2f>> &tags) const;

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

    void computeTransformation(const std::string& name,
                               const std::vector<cv::Point3f>& corners,
                               const std::vector<cv::Point2f>& imagePoints,
                               std::map<std::string, cv::Matx44d>& objects) const;

    bool hasObjectConfiguration;
    std::vector<cv::Point3f> defaultMarkerCorners;

    ObjectConfig _config;
};

}

#endif
