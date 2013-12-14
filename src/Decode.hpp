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

#ifndef Decode_HPP
#define Decode_HPP

#include <Codec.hpp>
#include <opencv2/core/core.hpp>
#include <vector>

namespace chilitags {

class Decode
{
public:
static const int INVALID_TAG;

Decode();

const std::pair<int, std::vector<cv::Point2f>> &operator()(
	const std::vector<unsigned char> &pBits,
	const std::vector<cv::Point2f> &pCorners);

virtual ~Decode();

protected:

unsigned char *mMatrix;
unsigned char *mMatrix90;
unsigned char *mMatrix180;
unsigned char *mMatrix270;

Codec mCodec;
std::pair<int, std::vector<cv::Point2f>> mDecodedTag;

private:
Decode(const Decode&);
Decode& operator=(const Decode&);

};

}

#endif
