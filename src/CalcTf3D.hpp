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

#ifndef CALCTF3D_HPP
#define CALCTF3D_HPP

#include <vector>
#include <map>
#include <opencv2/core/core.hpp>

#include <chilitags.hpp>

namespace chilitags {

template<typename RealT>
class CalcTf3D
{
public:

    CalcTf3D(cv::Size cameraResolution);

    void setCameraCalibration(cv::Mat newCameraMatrix, cv::Mat newDistCoeffs);

    cv::Mat const& getCameraMatrix() const;

    cv::Mat const& getDistortionCoeffs() const;

    void operator()(std::string const& name,
            std::vector<cv::Point3_<RealT>> const& objectPoints,
            cv::Mat_<cv::Point2f> const& imagePoints,
            typename Chilitags3D_<RealT>::TagPoseMap& objects);

protected:

    cv::Mat mCameraMatrix;
    cv::Mat mDistCoeffs;

    // Rotation & translation vectors, computed by cv::solvePnP
    cv::Mat mTempRotation;
    cv::Mat mTempTranslation;

    //TODO: This is double because of rodrigues, it doesn't accept float at the time of writing
    cv::Matx33d mTempRotMat;

};

} /* namespace chilitags */

#endif /* CALCTF3D_HPP */
