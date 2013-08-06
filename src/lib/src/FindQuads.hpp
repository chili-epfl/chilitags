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

#ifndef FindQuads_H
#define FindQuads_H

#include "Pipeable.hpp"
#include <opencv2/opencv.hpp>
#include <Quad.hpp>

namespace chilitags {

class FindQuads : public Pipeable
{
public:
FindQuads(const cv::Mat *pBinaryImage);
~FindQuads();

const Quad *const *QuadCorners() const {
	return &mQuadsCorners;
}
const size_t *NumQuads() const {
	return &mNumQuads;
}

protected:
virtual void run();

const cv::Mat *mBinaryImage;
static const int scScaledCopiesCount = 3;
cv::Mat mScaledCopies[scScaledCopiesCount];
CvMemStorage* mStorage;

static const int scMaxNumQuads = 1000;
Quad *const mQuadsCorners;
size_t mNumQuads;

private:
FindQuads(const FindQuads&);
FindQuads& operator=(const FindQuads&);
};

}

#endif
