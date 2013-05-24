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
        const IplImage *const *pInputImage,
        const Quad *pCorners);
const IplImage *const *GetOutputImage() const {
	return &mUndistortedTag;
}

virtual ~Undistort();

protected:
void run();

const IplImage *const *mInputImage;
const Quad *mCorners;

CvPoint2D32f mSrcBoundaries[4];
CvPoint2D32f mDstBoundaries[4];
CvMat *mTransformation;

IplImage *mUndistortedTag;

private:
Undistort(const Undistort&);
Undistort& operator=(const Undistort&);
};


}

#endif
