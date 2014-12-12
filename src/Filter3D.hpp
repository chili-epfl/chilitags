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

    const int CV_TYPE;      ///< One of CV_32F, CV_64F depending on the template type
    const RealT EPSILON;    ///< One of FLT_EPSILON, DBL_EPSILON depending on the template type

    /**
     * @brief Describes a Kalman filter, an associated previous rotation state and a lazy deletion flag
     */
    struct KFQ{
        cv::KalmanFilter filter;
        cv::Vec<RealT,4> prevQuat;
        bool deleted;

        KFQ(int dynamParams, int measureParams, int controlParams, int type) :
            filter(dynamParams, measureParams, controlParams, type),
            prevQuat(),
            deleted(false)
        {}
    };

    std::map<std::string, KFQ> mFilters;    ///< We keep one filter per object and do not discard them

    cv::Mat mF;                             ///< Process matrix, depends on the camera movement info
    cv::Mat mB;                             ///< Control matrix, depends on the camera movement info
    cv::Mat mControl;                       ///< Control input, depends on the camera movement info

    cv::Mat mQ;                             ///< Process noise covariance matrix, to be tuned
    bool mQChanged;                         ///< Whether Q was updated externally
    cv::Mat mR;                             ///< Measurement noise covariance matrix, to be tuned
    bool mRChanged;                         ///< Whether R was updated externally

    cv::Mat mCovScales;                     ///< Coefficients to scale the covariance matrix diagonal entries
    RealT mPersistence;                     ///< Persistence of tags against being discarded when not seen for a while

    cv::Mat mTempState;                     ///< Temporary matrix to hold the state (x,y,z,qr,qi,qj,qk)

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
