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

#include <opencv2/calib3d/calib3d.hpp>

//TODO: Replace all assignment sequences with memcpys (if possible) when double/float is unified

namespace chilitags{

template<typename RealT>
Filter3D<RealT>::Filter3D() :
    CV_TYPE(std::is_same<RealT,double>::value ? CV_64F : CV_32F),
    EPSILON(std::is_same<RealT,double>::value ? DBL_EPSILON : FLT_EPSILON),
    mF(7, 7, CV_TYPE),
    mB(7, 3, CV_TYPE),
    mControl(3, 1, CV_TYPE),
    mQ(),
    mR(),
    mTempState(7, 1, CV_TYPE)
{

    //Process noise covariance is 7x7: cov((x,y,z,qw,qi,qj,qk))
    mQ = (cv::Mat_<RealT>(7,7) <<
            1e-3f,  0,      0,      0,      0,      0,      0,
            0,      1e-3f,  0,      0,      0,      0,      0,
            0,      0,      1e-3f,  0,      0,      0,      0,
            0,      0,      0,      1e-4f,  0,      0,      0,
            0,      0,      0,      0,      1e-4f,  0,      0,
            0,      0,      0,      0,      0,      1e-4f,  0,
            0,      0,      0,      0,      0,      0,      1e-4f);

    //Measurement noise covariance is 7x7: cov((x,y,z,qw,qi,qj,qk))
    mR = (cv::Mat_<RealT>(7,7) <<
            1e-3f,  0,      0,      0,      0,      0,      0,
            0,      1e-3f,  0,      0,      0,      0,      0,
            0,      0,      1e-1f,  0,      0,      0,      0,
            0,      0,      0,      1e-3f,  0,      0,      0,
            0,      0,      0,      0,      1e-2f,  0,      0,
            0,      0,      0,      0,      0,      1e-2f,  0,
            0,      0,      0,      0,      0,      0,      1e-5f);

    //Process matrix is 7x7 and is identity as long as there is no camera movement info
    cv::setIdentity(mF);

    //Control matrix is 7x3 and is zero as long as there is no camera movement info
    mB = cv::Mat::zeros(7, 3, CV_TYPE);

    //Control input is 3x1 and is zero as long as there is no linear camera movement info
    mControl = cv::Mat::zeros(3, 1, CV_TYPE);
}

template<typename RealT>
void Filter3D<RealT>::setCamDelta(cv::Vec<RealT, 4> const& q, cv::Vec<RealT, 3> const& camDeltaX)
{
    RealT* F0 = (RealT*)mF.ptr(0);
    RealT* F1 = (RealT*)mF.ptr(1);
    RealT* F2 = (RealT*)mF.ptr(2);
    RealT* F3 = (RealT*)mF.ptr(3);
    RealT* F4 = (RealT*)mF.ptr(4);
    RealT* F5 = (RealT*)mF.ptr(5);
    RealT* F6 = (RealT*)mF.ptr(6);

    RealT* B0 = (RealT*)mB.ptr(0);
    RealT* B1 = (RealT*)mB.ptr(1);
    RealT* B2 = (RealT*)mB.ptr(2);

    RealT* u = (RealT*)mControl.ptr(0);

    //Set the transition matrix (other entries are zero)
    F0[0] = q(0)*q(0) + q(1)*q(1) - q(2)*q(2) - q(3)*q(3);  F0[1] = 2*(q(1)*q(2) + q(0)*q(3));  F0[2] = 2*(q(1)*q(3) - q(0)*q(2));
    F1[0] = 2*(q(1)*q(2) - q(0)*q(3));  F1[1] = q(0)*q(0) - q(1)*q(1) + q(2)*q(2) - q(3)*q(3);  F1[2] = 2*(q(2)*q(3) + q(0)*q(1));
    F2[0] = 2*(q(1)*q(3) + q(0)*q(2));  F2[1] = 2*(q(2)*q(3) - q(0)*q(1));  F2[2] = q(0)*q(0) - q(1)*q(1) - q(2)*q(2) + q(3)*q(3);
    F3[3] = q(0);   F3[4] = q(1);   F3[5] = q(2);   F3[6] = q(3);
    F4[3] = -q(1);  F4[4] = q(0);   F4[5] = q(3);   F4[6] = -q(2);
    F5[3] = -q(2);  F5[4] = -q(3);  F5[5] = q(0);   F5[6] = q(1);
    F6[3] = -q(3);  F6[4] = q(2);   F6[5] = -q(1);  F6[6] = q(0);

    //Set the control matrix (other entries are zero)
    //TODO: memcpy
    B0[0] = F0[0];  B0[1] = F0[1]; B0[2] = F0[2];
    B1[0] = F1[0];  B1[1] = F1[1]; B1[2] = F1[2];
    B2[0] = F2[0];  B2[1] = F2[1]; B2[2] = F2[2];

    //Set the control input
    u[0] = -camDeltaX(0);
    u[1] = -camDeltaX(1);
    u[2] = -camDeltaX(2);
}

template<typename RealT>
void Filter3D<RealT>::operator()(typename Chilitags3D_<RealT>::TagPoseMap& tags)
{
    //TODO: These have to be double precision for rodrigues
    cv::Mat predictedRot(3,1,CV_64F);
    cv::Matx33d tempRotMat;

    for(auto& kfq : mFilters){
        cv::KalmanFilter& filter = kfq.second.filter;

        //Do prediction step
        mF.copyTo(filter.transitionMatrix);
        mB.copyTo(filter.controlMatrix);
        filter.predict(mControl).copyTo(mTempState);

        //Convert quaternion rotation to angle-axis rotation
        getAngleAxis(predictedRot);

        //Convert angle-axis to 3x3 rotation matrix
        cv::Rodrigues(predictedRot, tempRotMat);

        //Write back updated pose
        tags[kfq.first] = {
            (RealT)tempRotMat(0,0),     (RealT)tempRotMat(0,1),     (RealT)tempRotMat(0,2),     mTempState.at<RealT>(0),
            (RealT)tempRotMat(1,0),     (RealT)tempRotMat(1,1),     (RealT)tempRotMat(1,2),     mTempState.at<RealT>(1),
            (RealT)tempRotMat(2,0),     (RealT)tempRotMat(2,1),     (RealT)tempRotMat(2,2),     mTempState.at<RealT>(2),
            0,                          0,                          0,                          1
        };
    }
}

template<typename RealT>
void Filter3D<RealT>::operator()(std::string const& id, cv::Mat& measuredTrans, cv::Mat& measuredRot)
{
    //Create&insert or return the related filter
    //Second set of 4 params are for Kalman filter: # of state dimensions, # of measurement dimensions,
    //# of control input dimensions and float precision of internal matrices
    auto pair = mFilters.emplace(std::piecewise_construct,
            std::make_tuple(id),
            std::make_tuple(7, 7, 3, CV_TYPE));
    cv::KalmanFilter& filter = pair.first->second.filter;
    cv::Vec<RealT,4>& prevQuat = pair.first->second.prevQuat;

    //Newly inserted
    if(pair.second)
        initFilter(filter, prevQuat, measuredTrans, measuredRot);

    //Already existing filter
    else{

        //Fill state
        mTempState.at<RealT>(0) = (RealT)measuredTrans.at<double>(0); //x
        mTempState.at<RealT>(1) = (RealT)measuredTrans.at<double>(1); //y
        mTempState.at<RealT>(2) = (RealT)measuredTrans.at<double>(2); //z
        getQuaternion(measuredRot, mTempState);

        //Do the correction step
        shortestPathQuat(prevQuat);
        filter.correct(mTempState).copyTo(mTempState);
        normalizeQuat();

        //Write state back
        measuredTrans.at<double>(0) = mTempState.at<RealT>(0); //x
        measuredTrans.at<double>(1) = mTempState.at<RealT>(1); //y
        measuredTrans.at<double>(2) = mTempState.at<RealT>(2); //z
        getAngleAxis(measuredRot);
    }
}

template<typename RealT>
void Filter3D<RealT>::initFilter(cv::KalmanFilter& filter, cv::Vec<RealT,4>& prevQuat, cv::Mat& measuredTrans, cv::Mat& measuredRot)
{
    mQ.copyTo(filter.processNoiseCov);
    mR.copyTo(filter.measurementNoiseCov);

    //We have no expectation from a tag other than staying still as long as there is no camera movement information
    cv::setIdentity(filter.transitionMatrix);

    //We make the same measurement as the state: (x,y,z,qr,qi,qj,qk)
    cv::setIdentity(filter.measurementMatrix);

    //Set initial state
    filter.statePost.at<RealT>(0) = (RealT)measuredTrans.at<double>(0); //x
    filter.statePost.at<RealT>(1) = (RealT)measuredTrans.at<double>(1); //y
    filter.statePost.at<RealT>(2) = (RealT)measuredTrans.at<double>(2); //z
    getQuaternion(measuredRot, filter.statePost);

    prevQuat(0) = filter.statePost.at<RealT>(3);
    prevQuat(1) = filter.statePost.at<RealT>(4);
    prevQuat(2) = filter.statePost.at<RealT>(5);
    prevQuat(3) = filter.statePost.at<RealT>(6);
}

template<typename RealT>
void Filter3D<RealT>::getAngleAxis(cv::Mat& output)
{
    RealT theta = sqrt(
            mTempState.at<RealT>(4)*mTempState.at<RealT>(4) +
            mTempState.at<RealT>(5)*mTempState.at<RealT>(5) +
            mTempState.at<RealT>(6)*mTempState.at<RealT>(6));
    theta = 2*atan2(theta, mTempState.at<RealT>(3));
    RealT sTheta2 = sin(theta/2);
    if(theta < EPSILON){ //Use lim( theta -> 0 ){ theta/sin(theta) }
        output.at<double>(0) = mTempState.at<RealT>(4); //rx
        output.at<double>(1) = mTempState.at<RealT>(5); //ry
        output.at<double>(2) = mTempState.at<RealT>(6); //rz
    }
    else{
        output.at<double>(0) = mTempState.at<RealT>(4)*theta/sTheta2; //rx
        output.at<double>(1) = mTempState.at<RealT>(5)*theta/sTheta2; //ry
        output.at<double>(2) = mTempState.at<RealT>(6)*theta/sTheta2; //rz
    }
}

template<typename RealT>
void Filter3D<RealT>::getQuaternion(cv::Mat& input, cv::Mat& output)
{
    RealT theta = norm(input);
    output.at<RealT>(3) = cos(theta/2); //qr
    if(theta < EPSILON){ //Use lim( theta -> 0 ){ sin(theta)/theta }
        output.at<RealT>(4) = ((RealT)input.at<double>(0)); //qi
        output.at<RealT>(5) = ((RealT)input.at<double>(1)); //qj
        output.at<RealT>(6) = ((RealT)input.at<double>(2)); //qk
    }
    else{
        RealT sTheta2 = sin(theta/2);
        output.at<RealT>(4) = ((RealT)input.at<double>(0))/theta*sTheta2; //qi
        output.at<RealT>(5) = ((RealT)input.at<double>(1))/theta*sTheta2; //qj
        output.at<RealT>(6) = ((RealT)input.at<double>(2))/theta*sTheta2; //qk
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

