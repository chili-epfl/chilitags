/*******************************************************************************
*   Copyright 2013 EPFL                                                        *
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

#ifndef ReadBits_HPP
#define ReadBits_HPP

#include <Quad.hpp>

namespace chilitags {

class ReadBits
{
public:
ReadBits();

void operator()(cv::Mat pInputImage, const Quad &pCorners);

const std::vector<unsigned char> &Bits() const { return mBits; }

protected:

std::vector<cv::Point2f> mDstBoundaries;
std::vector<cv::Point2f> mSamplePoints;

std::vector<uchar> mBits;

};


}

#endif
