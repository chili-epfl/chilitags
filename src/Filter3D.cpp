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
#include<cmath>
#include<cfloat>

//TODO: Replace all assignment sequences with memcpys (if possible) when double/float is unified

namespace chilitags{

template<typename RealT>
Filter3D<RealT>::Filter3D() :
    CV_TYPE(std::is_same<RealT,double>::value ? CV_64F : CV_32F),
    EPSILON(std::is_same<RealT,double>::value ? DBL_EPSILON : FLT_EPSILON),
    mQ(),
    mR(),
    mTempState(7,1, CV_TYPE)
{

    //Process noise covariance is 6x6: cov((x,y,z,rx,ry,rz))
    mQ = (cv::Mat_<RealT>(7,7) <<
            1e-3f,  0,      0,      0,      0,      0,      0,
            0,      1e-3f,  0,      0,      0,      0,      0,
            0,      0,      1e-3f,  0,      0,      0,      0,
            0,      0,      0,      1e-4f,  0,      0,      0,
            0,      0,      0,      0,      1e-4f,  0,      0,
            0,      0,      0,      0,      0,      1e-4f,  0,
            0,      0,      0,      0,      0,      0,      1e-4f);

    //Measurement noise covariance is 6x6: cov((x,y,z,rx,ry,rz))
    mR = (cv::Mat_<RealT>(7,7) <<
            1e-3f,  0,      0,      0,      0,      0,      0,
            0,      1e-3f,  0,      0,      0,      0,      0,
            0,      0,      1e-1f,  0,      0,      0,      0,
            0,      0,      0,      1e-3f,  0,      0,      0,
            0,      0,      0,      0,      1e-2f,  0,      0,
            0,      0,      0,      0,      0,      1e-2f,  0,
            0,      0,      0,      0,      0,      0,      1e-5f);
}

template<typename RealT>
void Filter3D<RealT>::operator()(std::string const& id, cv::Mat& measuredTrans, cv::Mat& measuredRot)
{
    //Create&insert or return the related filter
    //Second set of 4 params are for Kalman filter: # of state dimensions, # of measurement dimensions,
    //# of control input dimensions and float precision of internal matrices
    auto pair = mFilters.emplace(std::piecewise_construct,
            std::make_tuple(id),
            std::make_tuple(7, 7, 0, CV_TYPE));
    cv::KalmanFilter& filter = pair.first->second.filter;
    cv::Vec<RealT,4>& prevQuat = pair.first->second.prevQuat;

    RealT theta = norm(measuredRot);
    RealT sTheta2 = sin(theta/2);

    //Newly inserted
    if(pair.second){
        mQ.copyTo(filter.processNoiseCov);
        mR.copyTo(filter.measurementNoiseCov);

        //TODO: Control input will be the IMU data that "drives" the tag
        //cv::setIdentity(filter.controlMatrix);

        //We have no expectation from a tag other than staying still
        cv::setIdentity(filter.transitionMatrix);

        //We make the same measurement as the state: (x,y,z,qr,qi,qj,qk)
        cv::setIdentity(filter.measurementMatrix);

        //Set initial state
        filter.statePost.at<RealT>(0) = (RealT)measuredTrans.at<double>(0); //x
        filter.statePost.at<RealT>(1) = (RealT)measuredTrans.at<double>(1); //y
        filter.statePost.at<RealT>(2) = (RealT)measuredTrans.at<double>(2); //z

        filter.statePost.at<RealT>(3) = cos(theta/2); //qr
        if(theta < EPSILON){ //Use lim( theta -> 0 ){ sin(theta)/theta }
            filter.statePost.at<RealT>(4) = ((RealT)measuredRot.at<double>(0)); //qi
            filter.statePost.at<RealT>(5) = ((RealT)measuredRot.at<double>(1)); //qj
            filter.statePost.at<RealT>(6) = ((RealT)measuredRot.at<double>(2)); //qk
        }
        else{
            filter.statePost.at<RealT>(4) = ((RealT)measuredRot.at<double>(0))/theta*sTheta2; //qi
            filter.statePost.at<RealT>(5) = ((RealT)measuredRot.at<double>(1))/theta*sTheta2; //qj
            filter.statePost.at<RealT>(6) = ((RealT)measuredRot.at<double>(2))/theta*sTheta2; //qk
        }

        prevQuat(0) = filter.statePost.at<RealT>(3);
        prevQuat(1) = filter.statePost.at<RealT>(4);
        prevQuat(2) = filter.statePost.at<RealT>(5);
        prevQuat(3) = filter.statePost.at<RealT>(6);
    }

    //Already existing filter
    else{
        mTempState.at<RealT>(0) = (RealT)measuredTrans.at<double>(0); //x
        mTempState.at<RealT>(1) = (RealT)measuredTrans.at<double>(1); //y
        mTempState.at<RealT>(2) = (RealT)measuredTrans.at<double>(2); //z

        mTempState.at<RealT>(3) = cos(theta/2); //qr
        if(theta < EPSILON){ //Use lim( theta -> 0 ){ sin(theta)/theta }
            mTempState.at<RealT>(4) = ((RealT)measuredRot.at<double>(0)); //qi
            mTempState.at<RealT>(5) = ((RealT)measuredRot.at<double>(1)); //qj
            mTempState.at<RealT>(6) = ((RealT)measuredRot.at<double>(2)); //qk
        }
        else{
            mTempState.at<RealT>(4) = ((RealT)measuredRot.at<double>(0))/theta*sTheta2; //qi
            mTempState.at<RealT>(5) = ((RealT)measuredRot.at<double>(1))/theta*sTheta2; //qj
            mTempState.at<RealT>(6) = ((RealT)measuredRot.at<double>(2))/theta*sTheta2; //qk
        }

        shortestPathQuat(prevQuat);
        filter.predict();
        filter.correct(mTempState).copyTo(mTempState);
        normalizeQuat();

        measuredTrans.at<double>(0) = mTempState.at<RealT>(0); //x
        measuredTrans.at<double>(1) = mTempState.at<RealT>(1); //y
        measuredTrans.at<double>(2) = mTempState.at<RealT>(2); //z

        theta = sqrt(
                mTempState.at<RealT>(4)*mTempState.at<RealT>(4) +
                mTempState.at<RealT>(5)*mTempState.at<RealT>(5) +
                mTempState.at<RealT>(6)*mTempState.at<RealT>(6));
        theta = 2*atan2(theta, mTempState.at<RealT>(3));
        sTheta2 = sin(theta/2);
        if(theta < EPSILON){ //Use lim( theta -> 0 ){ theta/sin(theta) }
            measuredRot.at<double>(0) = mTempState.at<RealT>(4); //rx
            measuredRot.at<double>(1) = mTempState.at<RealT>(5); //ry
            measuredRot.at<double>(2) = mTempState.at<RealT>(6); //rz
        }
        else{
            measuredRot.at<double>(0) = mTempState.at<RealT>(4)*theta/sTheta2; //rx
            measuredRot.at<double>(1) = mTempState.at<RealT>(5)*theta/sTheta2; //ry
            measuredRot.at<double>(2) = mTempState.at<RealT>(6)*theta/sTheta2; //rz
        }
    }
}

template<typename RealT>
inline RealT Filter3D<RealT>::norm(cv::Mat& vec3d)
{
    return sqrt((RealT)(
                vec3d.at<double>(0)*vec3d.at<double>(0) +
                vec3d.at<double>(1)*vec3d.at<double>(1) +
                vec3d.at<double>(2)*vec3d.at<double>(2)));
}

template<typename RealT>
inline void Filter3D<RealT>::normalizeQuat()
{
    RealT norm = sqrt(
            mTempState.at<RealT>(3)*mTempState.at<RealT>(3) +
            mTempState.at<RealT>(4)*mTempState.at<RealT>(4) +
            mTempState.at<RealT>(5)*mTempState.at<RealT>(5) +
            mTempState.at<RealT>(6)*mTempState.at<RealT>(6));

    if(norm > EPSILON){
        mTempState.at<RealT>(3) /= norm;
        mTempState.at<RealT>(4) /= norm;
        mTempState.at<RealT>(5) /= norm;
        mTempState.at<RealT>(6) /= norm;
    }
    else{
        mTempState.at<RealT>(3) = 1.0f;
        mTempState.at<RealT>(4) = 0.0f;
        mTempState.at<RealT>(5) = 0.0f;
        mTempState.at<RealT>(6) = 0.0f;
    }
}

template<typename RealT>
inline void Filter3D<RealT>::shortestPathQuat(cv::Vec<RealT,4>& prevQuat)
{
    //If -q would be closer to q_prev than +q, replace new q with -q
    //The following comes from the derivation of |q - q_prev|^2 - |-q - q_prev|^2
    if(
            mTempState.at<RealT>(3)*prevQuat(0) +
            mTempState.at<RealT>(4)*prevQuat(1) +
            mTempState.at<RealT>(5)*prevQuat(2) +
            mTempState.at<RealT>(6)*prevQuat(3) < 0){
        mTempState.at<RealT>(3) = -mTempState.at<RealT>(3);
        mTempState.at<RealT>(4) = -mTempState.at<RealT>(4);
        mTempState.at<RealT>(5) = -mTempState.at<RealT>(5);
        mTempState.at<RealT>(6) = -mTempState.at<RealT>(6);
    }
    prevQuat(0) = mTempState.at<RealT>(3);
    prevQuat(1) = mTempState.at<RealT>(4);
    prevQuat(2) = mTempState.at<RealT>(5);
    prevQuat(3) = mTempState.at<RealT>(6);
}

//All possible instantiations of Filter3D
template class Filter3D<float>;
template class Filter3D<double>;

} /* namespace chilitags */

