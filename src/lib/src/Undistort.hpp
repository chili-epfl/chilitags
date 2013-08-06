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

#ifndef Undistort_HPP
#define Undistort_HPP

#include "Pipeable.hpp"
#include <opencv2/opencv.hpp>
#include <Quad.hpp>

namespace chilitags {

class Undistort : public Pipeable
{
public:
Undistort(
        const cv::Mat *pInputImage,
        const Quad *pCorners);
const cv::Mat *GetOutputImage() const {
	return &mUndistortedTag;
}

virtual ~Undistort();

protected:
void run();

const cv::Mat *mInputImage;
const Quad *mCorners;

cv::Point2f mSrcBoundaries[4];
cv::Point2f mDstBoundaries[4];
CvMat *mTransformation;

cv::Mat mUndistortedTag;

private:
Undistort(const Undistort&);
Undistort& operator=(const Undistort&);
};


}

#endif
