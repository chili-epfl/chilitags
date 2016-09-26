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

#include "EstimatePose3D.hpp"

#include <opencv2/calib3d/calib3d.hpp>

namespace chilitags {

template<typename RealT>
EstimatePose3D<RealT>::EstimatePose3D(cv::Size cameraResolution) :
    mFilter3D(),
    mFilter3DEnabled(true),
    mCameraMatrix(),
    mDistCoeffs()
{
    float focalLength = 700.0f;
    mCameraMatrix = (cv::Mat_<float>(3,3) <<
                     focalLength,    0,              cameraResolution.width/2,
                     0,              focalLength,    cameraResolution.height/2,
                     0,              0,              1
                     );
}

template<typename RealT>
void EstimatePose3D<RealT>::setCameraCalibration(cv::Mat newCameraMatrix, cv::Mat newDistCoeffs)
{
    mCameraMatrix = newCameraMatrix;
    mDistCoeffs = newDistCoeffs;
}

template<typename RealT>
cv::Mat const& EstimatePose3D<RealT>::getCameraMatrix() const
{
    return mCameraMatrix;
}

template<typename RealT>
cv::Mat const& EstimatePose3D<RealT>::getDistortionCoeffs() const
{
    return mDistCoeffs;
}

template<typename RealT>
void EstimatePose3D<RealT>::enableFilter(bool enabled)
{
    mFilter3DEnabled = enabled;
}

template<typename RealT>
void EstimatePose3D<RealT>::setFilterPersistence(RealT persistence)
{
    mFilter3D.setPersistence(persistence);
}

template<typename RealT>
void EstimatePose3D<RealT>::setFilterProcessNoiseCovariance(cv::Mat const& covariance)
{
    mFilter3D.setProcessNoiseCovariance(covariance);
}

template<typename RealT>
void EstimatePose3D<RealT>::setFilterObservationNoiseCovariance(cv::Mat const& covariance)
{
    mFilter3D.setObservationNoiseCovariance(covariance);
}

template<typename RealT>
void EstimatePose3D<RealT>::setCamDelta(cv::Vec<RealT, 4> const& camDeltaR, cv::Vec<RealT, 3> const& camDeltaX)
{
    if(mFilter3DEnabled)
        mFilter3D.setCamDelta(camDeltaR, camDeltaX);
}

template<typename RealT>
void EstimatePose3D<RealT>::operator()(typename Chilitags3D_<RealT>::TagPoseMap& objects)
{
    if(mFilter3DEnabled)
        mFilter3D(objects);
}

template<typename RealT>
void EstimatePose3D<RealT>::operator()(std::string const& name,
                                       std::vector<cv::Point3_<RealT> > const& objectPoints,
                                       cv::Mat_<cv::Point2f> const& imagePoints,
                                       typename Chilitags3D_<RealT>::TagPoseMap& objects)
{

    // Find the 3D pose of our tag
    cv::solvePnP(objectPoints, imagePoints,
                 mCameraMatrix, mDistCoeffs,
                 mTempRotation, mTempTranslation, false,
#ifdef OPENCV3
                 cv::SOLVEPNP_ITERATIVE);
#else
                 cv::ITERATIVE);
#endif
    //TODO: Rotation and translation vectors come out of solvePnP as double

    if(mFilter3DEnabled)
        mFilter3D(name, mTempTranslation, mTempRotation);

    cv::Rodrigues(mTempRotation, mTempRotMat);

    objects[name] = {
        (RealT)mTempRotMat(0,0),    (RealT)mTempRotMat(0,1),    (RealT)mTempRotMat(0,2),    (RealT)mTempTranslation.at<double>(0),
        (RealT)mTempRotMat(1,0),    (RealT)mTempRotMat(1,1),    (RealT)mTempRotMat(1,2),    (RealT)mTempTranslation.at<double>(1),
        (RealT)mTempRotMat(2,0),    (RealT)mTempRotMat(2,1),    (RealT)mTempRotMat(2,2),    (RealT)mTempTranslation.at<double>(2),
        0,                          0,                          0,                          1
    };
}

//All possible instantiations of EstimatePose3D
template class EstimatePose3D<float>;
template class EstimatePose3D<double>;

} /* namespace chilitags */
