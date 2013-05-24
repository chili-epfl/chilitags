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

#ifndef Refine_HPP
#define Refine_HPP

#include "Pipeable.hpp"
#include <opencv2/opencv.hpp>
#include <Registrar.hpp>

namespace chilitags {

class Refine : public Pipeable
{
public:

Refine(
        const IplImage *const *pInputImage,
        const int *pDecodedTag,
        Registrar &pRegistrar);
virtual ~Refine();

const CvPoint2D32f*const *GetRefinedCorners() const {
	return &mOrderedCorners;
}

protected:
void run();

const IplImage *const *mInputImage;
const int *mDecodedTag;

CvRect mBoundingBox;
CvRect mROI;
CvPoint *mInternalCorners;
IplImage *mROICopy;
IplImage *mMask;
IplImage *mTempImg;
IplImage *mEigenImg;

int mNCorners;
CvPoint2D32f* mRefinedCorners;
CvPoint2D32f* mOrderedCorners;

Registrar &mRegistrar;

private:
Refine(const Refine& pRefine);
Refine& operator=(const Refine& pRefine);
};


}

#endif
