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
 * @file ScreenOut.cpp
 * @brief Contains fast and simple methods to screen out things that are obviously not tags
 * @author Ayberk Özgür
 */

#include<type_traits>
#include<cmath>

#include "ScreenOut.hpp"

namespace chilitags{

template<typename RealT>
ScreenOut<RealT>::ScreenOut() :
    EPSILON(std::is_same<RealT,double>::value ? DBL_EPSILON : FLT_EPSILON),
    PI_2(std::acos(std::is_same<RealT,double>::value ? 0.0 : 0.0f)),
    mFloorVector(0.0f, 0.0f, 0.0f),
    mScreenUpsideDown(false)
{
}

template<typename RealT>
inline void ScreenOut<RealT>::setFloorVector(cv::Vec<RealT, 3> floorVector)
{
    if(floorVector(0) == 0.0f && floorVector(1) == 0.0f && floorVector(2) == 0.0f)
        mScreenUpsideDown = false;
    else{
        mScreenUpsideDown = true;
        mFloorVector = floorVector;
    }
}

template<typename RealT>
inline bool ScreenOut<RealT>::operator()(Quad const& quad)
{
    return !isConvex(quad);
}

template<typename RealT>
inline bool ScreenOut<RealT>::operator()(cv::Mat const& rotation)
{
    return mScreenUpsideDown ? isUpsideDown(rotation) : false;
}

template<typename RealT>
inline bool ScreenOut<RealT>::isConvex(Quad const& quad)
{
    int vPrevX, vPrevY, vNextX, vNextY;

    for(int c = 0, p = 3, n = 1; c < 4; c++, p = (p + 1)%4, n = (n + 1)%4){
        vPrevX = quad(p,0) - quad(c,0); vPrevY = quad(p,1) - quad(c,1);
        vNextX = quad(n,0) - quad(c,0); vNextY = quad(n,1) - quad(c,1);
        if(vPrevX*vNextY > vPrevY*vNextX)
            return false;
    }

    return true;
}

template<typename RealT>
bool ScreenOut<RealT>::isUpsideDown(cv::Mat const& rotation)
{
    double rot[3];
    memcpy(rot, (double*)rotation.ptr(), 3*sizeof(double));
    RealT theta = (RealT)sqrt(rot[0]*rot[0] + rot[1]*rot[1] + rot[2]*rot[2]);

    cv::Vec<RealT, 3> zAxis;
    if(theta < EPSILON){
        zAxis(0) = 0.0f;
        zAxis(1) = 0.0f;
        zAxis(2) = 1.0f;
    }
    else{
        rot[0] /= theta;
        rot[1] /= theta;
        rot[2] /= theta;

        //Below is the rightmost column of Rodrigues' formula
        RealT sTheta = std::sin(theta);
        RealT cTheta = std::cos(theta);
        RealT cTheta_ = 1.0f - cTheta;
        zAxis(0) = (RealT)(rot[0]*rot[2]*cTheta_ + rot[1]*sTheta);
        zAxis(1) = (RealT)(rot[1]*rot[2]*cTheta_ - rot[0]*sTheta);
        zAxis(2) = (RealT)(rot[2]*rot[2]*cTheta_ + cTheta);
    }

    return std::acos(zAxis.dot(mFloorVector)) < PI_2;
}

//All possible instantiations of ScreenOut
template class ScreenOut<float>;
template class ScreenOut<double>;

} /* namespace chilitags */
