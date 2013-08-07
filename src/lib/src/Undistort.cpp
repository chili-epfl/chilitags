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

#include "Undistort.hpp"

//#define DEBUG_Undistort
#ifdef DEBUG_Undistort
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using std::cout;
using std::endl;
#endif

namespace {
const int scTagMargin = 2;
const int scDataSize = 6;
const int scTagSize = scDataSize+2*scTagMargin;
const float scClose = scTagMargin/(float) scTagSize;
const float scFar = 1.0f - scClose;
const int scTagWarpZoom = 16;
}

chilitags::Undistort::Undistort(
        const cv::Mat *pInputImage,
        const Quad *pCorners) :
	mInputImage(pInputImage),
	mCorners(pCorners),
	mTransformation(),
	mUndistortedTag()
{
#ifdef DEBUG_Undistort
	cvNamedWindow("Undistort");
#endif
}

chilitags::Undistort::~Undistort()
{
}


void chilitags::Undistort::run()
{
	mDstBoundaries[0].x = 0.0f;
	mDstBoundaries[0].y = 0.0f;
	mDstBoundaries[1].x = (float) mInputImage->cols;
	mDstBoundaries[1].y = 0.0f;
	mDstBoundaries[2].x = (float) mInputImage->cols;
	mDstBoundaries[2].y = (float) mInputImage->rows;
	mDstBoundaries[3].x = 0.0f;
	mDstBoundaries[3].y = (float) mInputImage->rows;

	mSrcBoundaries[2].x = (*mCorners)[0].x*scClose + (*mCorners)[2].x*scFar;
	mSrcBoundaries[2].y = (*mCorners)[0].y*scClose + (*mCorners)[2].y*scFar;
	mSrcBoundaries[3].x = (*mCorners)[1].x*scClose + (*mCorners)[3].x*scFar;
	mSrcBoundaries[3].y = (*mCorners)[1].y*scClose + (*mCorners)[3].y*scFar;
	mSrcBoundaries[0].x = (*mCorners)[2].x*scClose + (*mCorners)[0].x*scFar;
	mSrcBoundaries[0].y = (*mCorners)[2].y*scClose + (*mCorners)[0].y*scFar;
	mSrcBoundaries[1].x = (*mCorners)[3].x*scClose + (*mCorners)[1].x*scFar;
	mSrcBoundaries[1].y = (*mCorners)[3].y*scClose + (*mCorners)[1].y*scFar;

	mTransformation = cv::getPerspectiveTransform(mSrcBoundaries, mDstBoundaries);
	cv::warpPerspective(*mInputImage, mUndistortedTag, mTransformation, mUndistortedTag.size());

#ifdef DEBUG_Undistort
	cout << *mCorners << endl;
	cvShowImage("Undistort", mUndistortedTag);
	cvWaitKey(0);
#endif
}
