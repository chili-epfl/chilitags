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

#include <type_traits>
#include <cmath>
#include <cfloat>

#include <opencv2/calib3d/calib3d.hpp>

namespace chilitags {

template<typename RealT>
Filter3D<RealT>::Filter3D() :
    CV_TYPE(std::is_same<RealT,double>::value ? CV_64F : CV_32F),
    EPSILON(std::is_same<RealT,double>::value ? DBL_EPSILON : FLT_EPSILON),
    mF(7, 7, CV_TYPE),
    mB(7, 3, CV_TYPE),
    mControl(3, 1, CV_TYPE),
    mQ(),
    mQChanged(true),
    mR(),
    mRChanged(true),
    mCovScales(7, 1, CV_TYPE),
    mPersistence(10.0f),
    mTempState(7, 1, CV_TYPE)
{

    //Process noise covariance is 7x7: cov((x,y,z,qw,qx,qy,qz))
    mQ = (cv::Mat_<RealT>(7,7) <<
          1e-3f,  0,      0,      0,      0,      0,      0,
          0,      1e-3f,  0,      0,      0,      0,      0,
          0,      0,      1e-3f,  0,      0,      0,      0,
          0,      0,      0,      1e-4f,  0,      0,      0,
          0,      0,      0,      0,      1e-4f,  0,      0,
          0,      0,      0,      0,      0,      1e-4f,  0,
          0,      0,      0,      0,      0,      0,      1e-4f);

    //Measurement noise covariance is 7x7: cov((x,y,z,qw,qx,qy,qz))
    mR = (cv::Mat_<RealT>(7,7) <<
          1e-3f,  0,      0,      0,      0,      0,      0,
          0,      1e-3f,  0,      0,      0,      0,      0,
          0,      0,      1e-1f,  0,      0,      0,      0,
          0,      0,      0,      1e-3f,  0,      0,      0,
          0,      0,      0,      0,      1e-2f,  0,      0,
          0,      0,      0,      0,      0,      1e-2f,  0,
          0,      0,      0,      0,      0,      0,      1e-5f);

    //Scale coefficients when calculating the trace of the covariance estimate
    recalculateCovScales();

    //Process matrix is 7x7 and is identity as long as there is no camera movement info
    cv::setIdentity(mF);

    //Control matrix is 7x3 and is zero as long as there is no camera movement info
    mB = cv::Mat::zeros(7, 3, CV_TYPE);

    //Control input is 3x1 and is zero as long as there is no linear camera movement info
    mControl = cv::Mat::zeros(3, 1, CV_TYPE);
}

template<typename RealT>
inline void Filter3D<RealT>::recalculateCovScales()
{
    for(int i=0; i<7; i++)
        mCovScales.at<RealT>(i) = sqrt(mQ.at<RealT>(i,i)*mR.at<RealT>(i,i));
}

template<typename RealT>
void Filter3D<RealT>::setPersistence(RealT persistence)
{
    mPersistence = persistence;
}

template<typename RealT>
void Filter3D<RealT>::setProcessNoiseCovariance(cv::Mat const& covariance)
{
    covariance.copyTo(mQ);
    recalculateCovScales();
    mQChanged = true;
}

template<typename RealT>
void Filter3D<RealT>::setObservationNoiseCovariance(cv::Mat const& covariance)
{
    covariance.copyTo(mR);
    recalculateCovScales();
    mRChanged = true;
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
    memcpy(B0, F0, 3*sizeof(RealT));
    memcpy(B1, F1, 3*sizeof(RealT));
    memcpy(B2, F2, 3*sizeof(RealT));

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

    for(auto& kfq : mFilters) {
        if(kfq.second.deleted)
            continue;

        cv::KalmanFilter& filter = kfq.second.filter;

        //Calculate weighted covariance estimate trace, decide to discard or not
        RealT trace = 0.0f;
        for(int i=0; i<7; i++)
            trace += filter.errorCovPost.at<RealT>(i,i)/mCovScales.at<RealT>(i);
        trace /= 7.0f;
        if(trace > mPersistence) {
            kfq.second.deleted = true;
            continue;
        }

        //Do prediction step
        if(mQChanged)
            mQ.copyTo(filter.processNoiseCov);
        if(mRChanged)
            mR.copyTo(filter.measurementNoiseCov);
        mF.copyTo(filter.transitionMatrix);
        mB.copyTo(filter.controlMatrix);
        filter.predict(mControl).copyTo(mTempState);

        //Convert quaternion rotation to angle-axis rotation
        getAngleAxis((RealT*)mTempState.ptr() + 3, (double*)predictedRot.ptr());

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

    mQChanged = false;
    mRChanged = false;
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
    bool& deleted = pair.first->second.deleted;

    //Newly inserted or lazy-deleted
    if(pair.second || deleted) {
        deleted = false;
        initFilter(filter, prevQuat, measuredTrans, measuredRot);
    }

    //Already existing filter
    else{
        RealT* state = (RealT*)mTempState.ptr();
        double* trans = (double*)measuredTrans.ptr();

        //Fill state
        state[0] = (RealT)trans[0]; //x
        state[1] = (RealT)trans[1]; //y
        state[2] = (RealT)trans[2]; //z
        getQuaternion((double*)measuredRot.ptr(), state + 3);

        //Do the correction step
        shortestPathQuat(prevQuat);
        filter.correct(mTempState).copyTo(mTempState);
        normalizeQuat();

        //Write state back
        trans[0] = state[0]; //x
        trans[1] = state[1]; //y
        trans[2] = state[2]; //z
        getAngleAxis(state + 3, (double*)measuredRot.ptr());
    }
}

template<typename RealT>
void Filter3D<RealT>::initFilter(cv::KalmanFilter& filter, cv::Vec<RealT,4>& prevQuat, cv::Mat& measuredTrans, cv::Mat& measuredRot)
{
    mQ.copyTo(filter.processNoiseCov);
    mR.copyTo(filter.measurementNoiseCov);
    filter.errorCovPost = cv::Mat::zeros(7, 7, CV_TYPE);

    //We have no expectation from a tag other than staying still as long as there is no camera movement information
    cv::setIdentity(filter.transitionMatrix);

    //We make the same measurement as the state: (x,y,z,qw,qx,qy,qz)
    cv::setIdentity(filter.measurementMatrix);

    //Set initial state
    RealT* statePost = (RealT*)filter.statePost.ptr();
    double* trans = (double*)measuredTrans.ptr();

    statePost[0] = (RealT)trans[0]; //x
    statePost[1] = (RealT)trans[1]; //y
    statePost[2] = (RealT)trans[2]; //z
    getQuaternion((double*)measuredRot.ptr(), statePost + 3);

    prevQuat(0) = statePost[3];
    prevQuat(1) = statePost[4];
    prevQuat(2) = statePost[5];
    prevQuat(3) = statePost[6];
}

template<typename RealT>
void Filter3D<RealT>::getAngleAxis(RealT* input, double* output)
{
    RealT theta = sqrt(input[1]*input[1] + input[2]*input[2] + input[3]*input[3]);
    theta = 2*atan2(theta, input[0]);
    RealT sTheta2 = sin(theta/2);
    if(theta < EPSILON) { //Use lim( theta -> 0 ){ theta/sin(theta) }
        output[0] = input[1]; //rx
        output[1] = input[2]; //ry
        output[2] = input[3]; //rz
    }
    else{
        output[0] = input[1]*theta/sTheta2; //rx
        output[1] = input[2]*theta/sTheta2; //ry
        output[2] = input[3]*theta/sTheta2; //rz
    }
}

template<typename RealT>
void Filter3D<RealT>::getQuaternion(double* input, RealT* output)
{
    RealT theta = (RealT)sqrt(input[0]*input[0] + input[1]*input[1] + input[2]*input[2]);
    output[0] = cos(theta/2); //qw
    if(theta < EPSILON) { //Use lim( theta -> 0 ){ sin(theta)/theta }
        output[1] = (RealT)input[0]; //qx
        output[2] = (RealT)input[1]; //qy
        output[3] = (RealT)input[2]; //qz
    }
    else{
        RealT sTheta2 = sin(theta/2);
        output[1] = (RealT)input[0]/theta*sTheta2; //qx
        output[2] = (RealT)input[1]/theta*sTheta2; //qy
        output[3] = (RealT)input[2]/theta*sTheta2; //qz
    }
}

template<typename RealT>
inline void Filter3D<RealT>::normalizeQuat()
{
    RealT* quat = (RealT*)mTempState.ptr() + 3;
    RealT norm = sqrt(quat[0]*quat[0] + quat[1]*quat[1] + quat[2]*quat[2] + quat[3]*quat[3]);
    if(norm > EPSILON) {
        quat[0] /= norm;
        quat[1] /= norm;
        quat[2] /= norm;
        quat[3] /= norm;
    }
    else{
        quat[0] = 1.0f;
        quat[1] = 0.0f;
        quat[2] = 0.0f;
        quat[3] = 0.0f;
    }
}

template<typename RealT>
inline void Filter3D<RealT>::shortestPathQuat(cv::Vec<RealT,4>& prevQuat)
{
    RealT* quat = (RealT*)mTempState.ptr() + 3;

    //If -q would be closer to q_prev than +q, replace new q with -q
    //The following comes from the derivation of |q - q_prev|^2 - |-q - q_prev|^2
    if(
        quat[0]*prevQuat(0) +
        quat[1]*prevQuat(1) +
        quat[2]*prevQuat(2) +
        quat[3]*prevQuat(3) < 0) {
        quat[0] = -quat[0];
        quat[1] = -quat[1];
        quat[2] = -quat[2];
        quat[3] = -quat[3];
    }
    prevQuat(0) = quat[0];
    prevQuat(1) = quat[1];
    prevQuat(2) = quat[2];
    prevQuat(3) = quat[3];
}

//All possible instantiations of Filter3D
template class Filter3D<float>;
template class Filter3D<double>;

} /* namespace chilitags */

