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

namespace chilitags {

template<typename RealT>
class Filter3D {

public:

    /**
     * @brief Creates a new 6D pose filter for multiple std::string ID'd objects
     */
    Filter3D();

    /**
     * @brief Filters the given 6D pose depending on the past measurements
     *
     * TODO: measuredTrans and measuredRot must be double for now
     *
     * @param id Unique identifier of the object
     * @param measuredTrans Translation measurement to be filtered, 3x1 vector: (x,y,z)
     * @param measuredRot Rotation measurement to be filtered, 3x1 vector: (rx,ry,rz)
     */
    void operator()(std::string const& id, cv::Mat& measuredTrans, cv::Mat& measuredRot);

private:

    std::map<std::string, cv::KalmanFilter> mFilters;   ///< We keep one filter per object and do not discard them

    cv::Mat mQ;                                         ///< Process noise covariance matrix, to be tuned
    cv::Mat mR;                                         ///< Measurement noise covariance matrix, to be tuned

    cv::Mat mTempState;                                 ///< Temporary matrix to hold the state (x,y,z,rx,ry,rz)

    /**
     * @brief Gets one of CV_32F, CV_64F depending on the template type
     *
     * @return CV_32F or CV_64F
     */
    int getCVType();

};

} /* namespace chilitags */

#endif /* FILTER3D_HPP */
