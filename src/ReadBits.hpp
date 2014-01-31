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

#include <vector>
#include <opencv2/core/core.hpp>

namespace chilitags {

typedef cv::Matx<float, 4, 2> Quad;

class ReadBits
{
public:
ReadBits();

const std::vector<unsigned char> &operator()(const cv::Mat &inputImage, const Quad &corners);

protected:

std::vector<cv::Point2f> mSamplePoints;
std::vector<cv::Point2f> mTransformedSamplePoints;
cv::Mat mSamples;

std::vector<uchar> mBits;

};


}

#endif
