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
 * @file Filter3D.hpp
 * @brief 6D pose filter for multiple std::string ID'd objects
 * @author Ayberk Özgür
 *
 * At the core of this class is one regular Kalman filter per detected tag.
 * In these filters, the state is described as the following 7x1 vector:
 *
 * X(t) = (x(t), y(t), z(t), q_w(t), q_x(t), q_y(t), q_z(t))^T
 *      = (r(t), q(t))^T
 *
 * where x, y, z describe the tag position and q_w, q_x, q_y, q_z describe the
 * tag orientation in unit quaternion form; this tag pose is in the camera
 * frame, i.e the frame where 3D Chilitags detection is made.
 *
 * The state transition is made according to whether there is input data
 * regarding camera movement, measured by e.g inertial sensors. There are two
 * cases:
 *
 * 1.There is no camera movement information. In this case, the state
 *   transition process is described as:
 *
 *   X(t|t-1) = I*X(t-1|t-1)
 *
 *   where I is a 7x7 identity matrix and there is no control input. In other
 *   words, this transition mechanism resists against tag movement. The amount
 *   of resistance depends on the process noise covariance matrix Q that should
 *   be tuned by the user. Larger values in Q tends to decrease resistance
 *   against motion.
 *
 * 2.There is camera movement information. In this case, the state transition
 *   process becomes:
 *
 *   r(t|t-1) = (deltaR_camera(t in t-1)^-1)*r(t-1|t-1) - (deltaR_camera(t in t-1)^-1)*deltaX_camera(t in t-1)
 *   q(t|t-1) = (deltaR_camera(t in t-1)^-1)*q(t-1|t-1)
 *
 *   Here, deltaR_camera(t in t-1) is a unit quaternion describing the rotation
 *   of the camera at time t with respect to the frame described by the camera
 *   at time t-1. deltaX_camera(t in t-1) is a 3x1 vector describing the
 *   translation of the camera at time t with respect to the frame described by
 *   the camera at time t-1 in millimeters. Therefore, the input to the
 *   process at time t is the camera displacement from time t-1 to time t in
 *   addition to the a posteriori state estimate from time t-1.
 *
 *   In the first equation, the multiplication represents vector rotation. In
 *   other words, the 3x1 vectors are left multiplied by the inverse of the
 *   3x3 rotation matrix described by deltaR_camera. In the second equation,
 *   the multiplication represents Hamilton product, a.k.a quaternion
 *   multiplication.
 *
 *   The two equations can be written in one as follows, giving the usual
 *   Kalman filter process equation:
 *
 *   X(t|t-1) = F(t)*X(t-1|t-1) + B(t)*u(t)
 *
 *   Here, F(t) is a 7x7 matrix that can be written as the following:
 *
 *          /                          |                           \
 *          |  rot(deltaR_camera^-1)   |            0              |
 *          |                     (3x3)|                           |
 *   F(t) = |------------------------------------------------------|
 *          |                          |                           |
 *          |            0             |   mat(deltaR_camera^-1)   |
 *          \                          |                      (4x4)/
 *
 *   where rot() represents the orthogonal rotation matrix and mat() represents
 *   the Hamilton product matrix given the input quaternion.
 *
 *   B(t) is a 7x3 matrix that can be written as the following:
 *
 *          /                          \
 *          |  rot(deltaR_camera^-1)   |
 *          |                     (3x3)|
 *   B(t) = |--------------------------|
 *          |                          |
 *          |            0             |
 *          \                          /
 *
 *   And finally, u(t) is a 3x1 vector that is equal to
 *   -deltaX_camera(t in t-1)
 *
 *   Please note that if the camera displacement is zero, i.e deltaX_camera
 *   is (0,0,0) and deltaR_camera is (1,0,0,0), the equation reduces to the one
 *   in case (1) where the state stays the same.
 *
 * The observation, coming from the actual Chilitags detection, is
 * decribed (similarly to the state) as:
 *
 * z(t) = (x~(t), y~(t), z~(t), q_w~(t), q_x~(t), q_y~(t), q_z~(t))^T
 *      = (r~(t), q~(t))^T
 *
 * The resistance against the movement of the tag described by the observation
 * depends on the observation noise covariance matrix R that is to be tuned by
 * the user. Larger values in R tend to increase the resistance against
 * motion.
 *
 * Given these, the a posteriori state estimate is calculated, as usual, as:
 *
 * X(t|t) = X(t|t-1) + K(t)*(z(t) - I*x(t|t-1))
 *
 * where K(t) is the current Kalman gain, calculated using the a priori state
 * covariance estimate and I is a 7x7 identity matrix. Finally, the a
 * posteriori state estimate is exported at each step as the filtered tag pose
 * output.
 */

#ifndef FILTER3D_HPP
#define FILTER3D_HPP

#include <map>

#include <opencv2/core/core.hpp>
#include <opencv2/video/tracking.hpp>

#include "chilitags.hpp"

namespace chilitags {

template<typename RealT>
class Filter3D {

public:

/**
 * @brief Creates a new 6D pose filter for multiple std::string ID'd objects
 */
Filter3D();

/**
 * @brief Sets the persistence of tags against being discarded when not observed
 *
 * @param persistence Persistence value, roughly correponds to number of frames
 */
void setPersistence(RealT persistence);

/**
 * @brief Sets the process noise covariance matrix Q
 *
 * @param covariance 7x7 covariance matrix
 */
void setProcessNoiseCovariance(cv::Mat const& covariance);

/**
 * @brief Sets the observation noise covariance matrix R
 *
 * @param covariance 7x7 covariance matrix
 */
void setObservationNoiseCovariance(cv::Mat const& covariance);

/**
 * @brief Informs the rotation and translation of the current camera frame in the previous camera frame
 *
 * @param camDeltaR Rotation of current camera frame in previous camera frame in unit quaternion format (w,vx,vy,vz)
 * @param camDeltaX Translation of current camera frame in previous camera frame
 */
void setCamDelta(cv::Vec<RealT, 4> const& camDeltaR, cv::Vec<RealT, 3> const& camDeltaX);

/**
 * @brief Performs KF prediction step for all known tags
 *
 * @param tags The list of tags
 */
void operator()(typename Chilitags3D_<RealT>::TagPoseMap& tags);

/**
 * @brief Performs KF correction step for the given tag
 *
 * TODO: measuredTrans and measuredRot must be double for now
 *
 * @param id Unique identifier of the object
 * @param measuredTrans Translation measurement, also the output, 3x1 vector: (x,y,z)
 * @param measuredRot Rotation measurement, also the output, 3x1 axis-angle representation: (rx,ry,rz)
 */
void operator()(std::string const& id, cv::Mat& measuredTrans, cv::Mat& measuredRot);

private:

const int CV_TYPE;          ///< One of CV_32F, CV_64F depending on the template type
const RealT EPSILON;        ///< One of FLT_EPSILON, DBL_EPSILON depending on the template type

/**
 * @brief Describes a Kalman filter, an associated previous rotation state and a lazy deletion flag
 */
struct KFQ {
    cv::KalmanFilter filter;
    cv::Vec<RealT,4> prevQuat;
    bool deleted;

    KFQ(int dynamParams, int measureParams, int controlParams, int type) :
        filter(dynamParams, measureParams, controlParams, type),
        prevQuat(),
        deleted(false)
    {
    }
};

std::map<std::string, KFQ> mFilters;        ///< We keep one filter per object and do not discard them

cv::Mat mF;                                 ///< Process matrix, depends on the camera movement info
cv::Mat mB;                                 ///< Control matrix, depends on the camera movement info
cv::Mat mControl;                           ///< Control input, depends on the camera movement info

cv::Mat mQ;                                 ///< Process noise covariance matrix, to be tuned
bool mQChanged;                             ///< Whether Q was updated externally
cv::Mat mR;                                 ///< Measurement noise covariance matrix, to be tuned
bool mRChanged;                             ///< Whether R was updated externally

cv::Mat mCovScales;                         ///< Coefficients to scale the covariance matrix diagonal entries
RealT mPersistence;                         ///< Persistence of tags against being discarded when not seen for a while

cv::Mat mTempState;                         ///< Temporary matrix to hold the state (x,y,z,qr,qi,qj,qk)

/**
 * @brief Recalculates the covariance matrix scale coefficients based on Q and R
 */
void recalculateCovScales();

/**
 * @brief Initializes the filter for newly discovered tag
 *
 * @param filter Filter to initialize
 * @param prevQuat Set to the current rotation for the future
 * @param measuredTrans First measurement of position
 * @param measuredRot First measurement of rotation
 */
void initFilter(cv::KalmanFilter& filter, cv::Vec<RealT,4>& prevQuat, cv::Mat& measuredTrans, cv::Mat& measuredRot);

/**
 * @brief Converts the quaternion rotation in the state to angle-axis representation
 *
 * @param input 4x1 quaternion
 * @param output Double precision 3x1 angle-axis
 */
void getAngleAxis(RealT* input, double* output);

/**
 * @brief Converts the angle-axis to quaternion
 *
 * @param input Double precision 3x1 angle-axis
 * @param output 4x1 quaternion
 */
void getQuaternion(double* input, RealT* output);

/**
 * @brief Normalizes the quaternion part of the internal state vector
 */
void normalizeQuat();

/**
 * @brief Ensures the sign of the internal state vector's quaternion is right so that we prevent quaternion unwinding
 */
void shortestPathQuat(cv::Vec<RealT,4>& prevQuat);

};

} /* namespace chilitags */

#endif /* FILTER3D_HPP */
