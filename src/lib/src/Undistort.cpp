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
#include <opencv2/imgproc/imgproc.hpp>

//#define DEBUG_Undistort
#ifdef DEBUG_Undistort
#include <opencv2/highgui/highgui.hpp>
#endif

namespace {
const int scTagMargin = 2;
const int scDataSize = 6;
const int scTagSize = scDataSize+2*scTagMargin;
const float scFar = scTagMargin/(float) scTagSize;
const float scClose = 1.0f - scFar;
const int scTagWarpZoom = 8;
}

chilitags::Undistort::Undistort(
        const cv::Mat *pInputImage,
        const Quad *pCorners) :
	mInputImage(pInputImage),
	mCorners(pCorners),
	mSize(scTagWarpZoom*scDataSize, scTagWarpZoom*scDataSize),
	mUndistortedTag()
{
	mDstBoundaries[0].x = 0.0f;
	mDstBoundaries[0].y = 0.0f;
	mDstBoundaries[1].x = (float) mSize.width;
	mDstBoundaries[1].y = 0.0f;
	mDstBoundaries[2].x = (float) mSize.width;
	mDstBoundaries[2].y = (float) mSize.height;
	mDstBoundaries[3].x = 0.0f;
	mDstBoundaries[3].y = (float) mSize.height;

#ifdef DEBUG_Undistort
	cv::namedWindow("Undistort");
#endif
}

chilitags::Undistort::~Undistort()
{
}


void chilitags::Undistort::run()
{
	Quad tCorners = *mCorners;
	mSrcBoundaries[0] = tCorners[0]*scClose + tCorners[2]*scFar;
	mSrcBoundaries[1] = tCorners[1]*scClose + tCorners[3]*scFar;
	mSrcBoundaries[2] = tCorners[2]*scClose + tCorners[0]*scFar;
	mSrcBoundaries[3] = tCorners[3]*scClose + tCorners[1]*scFar;

	cv::Matx33f tTransformation = cv::getPerspectiveTransform(mSrcBoundaries, mDstBoundaries);
	//cv::warpPerspective(*mInputImage, mUndistortedTag, tTransformation, mSize);

#ifdef DEBUG_Undistort
	cv::imshow("Undistort", mUndistortedTag);
	cv::waitKey(0);
#endif
}
