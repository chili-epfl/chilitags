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
 * @file Filter3D.cpp
 * @brief 6D pose filter for multiple std::string ID'd objects
 * @author Ayberk Özgür
 */

#include "Filter3D.hpp"

#include<type_traits>

namespace chilitags{

template<typename RealT>
inline int Filter3D<RealT>::getCVType()
{
    return std::is_same<RealT,double>::value ? CV_64F : CV_32F;
}

template<typename RealT>
Filter3D<RealT>::Filter3D() :
    mQ(),
    mR(),
    mTempState(6,1, getCVType())
{
    //Process noise covariance is 6x6: cov((x,y,z,rx,ry,rz))
    mQ = (cv::Mat_<RealT>(6,6) <<
            1e-3f,  0,      0,      0,      0,      0,
            0,      1e-3f,  0,      0,      0,      0,
            0,      0,      1e-3f,  0,      0,      0,
            0,      0,      0,      1e-5f,  0,      0,
            0,      0,      0,      0,      1e-5f,  0,
            0,      0,      0,      0,      0,      1e-5f
         );

    //Measurement noise covariance is 6x6: cov((x,y,z,rx,ry,rz))
    mR = (cv::Mat_<RealT>(6,6) <<
            1e-2f,  0,      0,      0,      0,      0,
            0,      1e-2f,  0,      0,      0,      0,
            0,      0,      1e-1f,  0,      0,      0,
            0,      0,      0,      1e-2f,  0,      0,
            0,      0,      0,      0,      1e-2f,  0,
            0,      0,      0,      0,      0,      1e-3f
         );
}

template<typename RealT>
void Filter3D<RealT>::operator()(std::string const& id, cv::Mat& measuredTrans, cv::Mat& measuredRot)
{
    //Create&insert or return the related filter
    //Second set of 4 params are for Kalman filter: state dimensions, measurement dimensions,
    //control input dimensions and float precision of internal matrices
    auto pair = mFilters.emplace(std::piecewise_construct,
            std::make_tuple(id),
            std::make_tuple(6, 6, 0, getCVType()));
    cv::KalmanFilter& filter = pair.first->second;

    //Newly inserted
    if(pair.second){
        mQ.copyTo(filter.processNoiseCov);
        mR.copyTo(filter.measurementNoiseCov);

        //TODO: Control input will be the IMU data that "drives" the tag
        //cv::setIdentity(filter.controlMatrix);

        //We have no expectation from a tag other than staying still
        cv::setIdentity(filter.transitionMatrix);

        //We make the same measurement as the state: (x,y,z,rx,ry,rz)
        cv::setIdentity(filter.measurementMatrix);

        //Set initial state
        //TODO: Replace these with memcpys
        filter.statePost.at<RealT>(0) = (RealT)measuredTrans.at<double>(0);
        filter.statePost.at<RealT>(1) = (RealT)measuredTrans.at<double>(1);
        filter.statePost.at<RealT>(2) = (RealT)measuredTrans.at<double>(2);
        filter.statePost.at<RealT>(3) = (RealT)measuredRot.at<double>(0);
        filter.statePost.at<RealT>(4) = (RealT)measuredRot.at<double>(1);
        filter.statePost.at<RealT>(5) = (RealT)measuredRot.at<double>(2);
    }

    //Already existing filter
    else{

        //TODO: Replace these with memcpys
        mTempState.at<RealT>(0) = (RealT)measuredTrans.at<double>(0);
        mTempState.at<RealT>(1) = (RealT)measuredTrans.at<double>(1);
        mTempState.at<RealT>(2) = (RealT)measuredTrans.at<double>(2);
        mTempState.at<RealT>(3) = (RealT)measuredRot.at<double>(0);
        mTempState.at<RealT>(4) = (RealT)measuredRot.at<double>(1);
        mTempState.at<RealT>(5) = (RealT)measuredRot.at<double>(2);

        filter.predict();
        filter.correct(mTempState).copyTo(mTempState);

        //TODO: Replace these with memcpys
        measuredTrans.at<double>(0) = mTempState.at<RealT>(0,0);
        measuredTrans.at<double>(1) = mTempState.at<RealT>(1,0);
        measuredTrans.at<double>(2) = mTempState.at<RealT>(2,0);
        measuredRot.at<double>(0) = mTempState.at<RealT>(3,0);
        measuredRot.at<double>(1) = mTempState.at<RealT>(4,0);
        measuredRot.at<double>(2) = mTempState.at<RealT>(5,0);
    }
}

//All possible instantiations of Filter3D
template class Filter3D<float>;
template class Filter3D<double>;

} /* namespace chilitags */
