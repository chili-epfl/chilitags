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

/**
 * @file EstimatePose3D.cpp
 * @brief 6D pose calculator from image coordinates and camera parameters
 * @author Quentin Bonnard
 * @author Ayberk Özgür
 */

#ifndef ESTIMATEPOSE3D_HPP
#define ESTIMATEPOSE3D_HPP

#include <vector>
#include <map>
#include <opencv2/core/core.hpp>

#include <chilitags.hpp>

#include "Filter3D.hpp"

namespace chilitags {

template<typename RealT>
class EstimatePose3D
{
public:

/**
 * @brief Creates a new 6D pose calculator that uses camera image coordinates and camera parameters
 *
 * @param cameraResolution Height and width of the camera image
 */
EstimatePose3D(cv::Size cameraResolution = cv::Size(640,480));

/**
 * @brief Updates the camera calibration parameters
 *
 * See http://docs.opencv.org/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html for parameter details
 *
 * @param newCameraMatrix 3x3 camera matrix
 * @param newDistCoeffs 4x1 or 5x1 or 8x1 distortion coefficients, pass empty matrix if unused
 */
void setCameraCalibration(cv::Mat newCameraMatrix, cv::Mat newDistCoeffs);

/**
 * @brief Returns the camera matrix
 *
 * @return The 3x3 camera matrix
 */
cv::Mat const& getCameraMatrix() const;

/**
 * @brief Returns the distortion coefficients
 *
 * @return The 4x1 or 5x1 or 8x1 or empty distortion coefficients
 */
cv::Mat const& getDistortionCoeffs() const;

/**
 * @brief Enabled/disables Kalman filtering on tag pose
 *
 * @param enabled Whether tag pose filtering is enabled/disabled
 */
void enableFilter(bool enabled);

/**
 * @brief Sets the persistence of tags against being discarded when not observed
 *
 * @param persistence Persistence value, roughly correponds to number of frames
 */
void setFilterPersistence(RealT persistence);

/**
 * @brief Sets the process noise covariance matrix for the Kalman filter
 *
 * @param covariance 7x7 covariance matrix
 */
void setFilterProcessNoiseCovariance(cv::Mat const& covariance);

/**
 * @brief Sets the observation noise covariance matrix for the Kalman filter
 *
 * @param covariance 7x7 covariance matrix
 */
void setFilterObservationNoiseCovariance(cv::Mat const& covariance);

/**
 * @brief Informs the rotation and translation of the current camera frame in the previous camera frame
 *
 * @param camDeltaR Rotation of current camera frame in previous camera frame in unit quaternion format (w,vx,vy,vz)
 * @param camDeltaX Translation of current camera frame in previous camera frame
 */
void setCamDelta(cv::Vec<RealT, 4> const& camDeltaR, cv::Vec<RealT, 3> const& camDeltaX);

/**
 * @brief Updates the poses of all known tags via statistical filtering
 *
 * @param objects Map to update in which ID maps to the transform
 */
void operator()(typename Chilitags3D_<RealT>::TagPoseMap& objects);

/**
 * @brief Updates/inserts the pose of the given object in the given map
 *
 * @param name Unique ID of the object
 * @param objectPoints Reference points on the object
 * @param imagePoints Where reference points are found in the image
 * @param objects Map to update in which ID maps to the transform
 */
void operator()(std::string const& name,
                std::vector<cv::Point3_<RealT> > const& objectPoints,
                cv::Mat_<cv::Point2f> const& imagePoints,
                typename Chilitags3D_<RealT>::TagPoseMap& objects);

protected:

Filter3D<RealT> mFilter3D;      ///< Kalman filter to increase stability of the tag
bool mFilter3DEnabled;          ///< Whether to enable pose filtering

cv::Mat mCameraMatrix;          ///< 3x3 camera matrix
cv::Mat mDistCoeffs;            ///< Empty or 4x1 or 5x1 or 8x1 Distortion coefficients of the camera

cv::Mat mTempRotation;          ///< 3x1 axis-angle: (rx,ry,rz)
cv::Mat mTempTranslation;       ///< 3x1 translation: (x,y,z)

//TODO: This is double because of rodrigues, it doesn't accept float at the time of writing
cv::Matx33d mTempRotMat;        ///< 3x3 rotation matrix representation of mTempRotation

};

} /* namespace chilitags */

#endif /* ESTIMATEPOSE3D_HPP */
