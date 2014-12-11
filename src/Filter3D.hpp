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
     * @brief Describes a Kalman filter and an associated previous quaternion rotation state
     */
    struct KFQ{
        cv::KalmanFilter filter;
        cv::Vec<RealT,4> prevQuat;

        KFQ(int dynamParams, int measureParams, int controlParams, int type) :
            filter(dynamParams, measureParams, controlParams, type),
            prevQuat()
        {}
    };

    std::map<std::string, KFQ> mFilters;    ///< We keep one filter per object and do not discard them

    cv::Mat mF;                             ///< Process matrix, depends on the camera movement info
    cv::Mat mB;                             ///< Control matrix, depends on the camera movement info
    cv::Mat mControl;                       ///< Control input, depends on the camera movement info

    cv::Mat mQ;                             ///< Process noise covariance matrix, to be tuned
    cv::Mat mR;                             ///< Measurement noise covariance matrix, to be tuned

    cv::Mat mTempState;                     ///< Temporary matrix to hold the state (x,y,z,qr,qi,qj,qk)

    /**
     * @brief Normalizes the quaternion part of the internal state vector
     */
    void normalizeQuat();

    /**
     * @brief Ensures the sign of the internal state vector's quaternion is right so that we prevent quaternion unwinding
     */
    void shortestPathQuat(cv::Vec<RealT,4>& prevQuat);

    /**
     * @brief Calculates the norm of the given 3-vector
     *
     * TODO: vec3d must be double for now
     *
     * @param vec3d 3-vector of doubles
     *
     * @return The calculated norm in single-precision
     */
    RealT norm(cv::Mat& vec3d);

};

} /* namespace chilitags */

#endif /* FILTER3D_HPP */
