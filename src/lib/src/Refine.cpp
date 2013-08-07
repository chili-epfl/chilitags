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

#include "Refine.hpp"
#include <Quad.hpp>

//#define DEBUG_Refine
#ifdef DEBUG_Refine
#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#endif

namespace {
const float scClose = 1.0f/10.0f;
const float scFar = 1.0f-scClose;
const cv::Scalar scWhite = CV_RGB(255,255,255);
const cv::Scalar scBlack = CV_RGB(0, 0, 0);
const float scMaxRefinement = 4.0f;

//TODO cv::boundingRect
cv::Rect findBoundingBox(const cv::Point2f *pCorners) {
	float tMinX = pCorners[0].x;
	float tMaxX = pCorners[0].x;
	float tMinY = pCorners[0].y;
	float tMaxY = pCorners[0].y;
	for (size_t i = 1; i < chilitags::Quad::scNPoints; ++i) {
		tMinX = MIN(tMinX, pCorners[i].x);
		tMaxX = MAX(tMaxX, pCorners[i].x);
		tMinY = MIN(tMinY, pCorners[i].y);
		tMaxY = MAX(tMaxY, pCorners[i].y);
	}
	return cvRect((int)tMinX, (int)tMinY, (int)(tMaxX-tMinX), (int)(tMaxY-tMinY));
}

cv::Rect findROI(const cv::Rect &pMinimalROI) {
	static const float scMarginRatio = scClose;
	int tXMargin = (int)(scMarginRatio*pMinimalROI.width);
	int tYMargin = (int)(scMarginRatio*pMinimalROI.height);
	return cvRect(pMinimalROI.x-tXMargin, pMinimalROI.y-tYMargin, pMinimalROI.width+2*tXMargin, pMinimalROI.width+2*tYMargin);         //FIXME: border effect
}
}

chilitags::Refine::Refine(
        const cv::Mat *pInputImage,
        const int *pDecodedTag,
        Registrar &pRegistrar) :
	mInputImage(pInputImage),
	mDecodedTag(pDecodedTag),
	mBoundingBox(cvRect(0,0,1,1)),
	mROI(findROI(mBoundingBox)),
	mInternalCorners(new cv::Point[Quad::scNPoints]),
	mROICopy(),
	mMask(),
	mNCorners(Quad::scNPoints),
	mRefinedCorners(),
	mOrderedCorners(),
	mRegistrar(pRegistrar)
{
#ifdef DEBUG_Refine
	cvNamedWindow("Refine");
#endif
}

chilitags::Refine::~Refine()
{
	delete []mInternalCorners;
}

void chilitags::Refine::run()
{
	int tDecodedTag = *mDecodedTag;
	if (tDecodedTag > -1)
	{
		cv::Mat tInputImage = *mInputImage;

		const cv::Point2f *tInputCorners = mRegistrar.getCorners(tDecodedTag);
		mBoundingBox = findBoundingBox(tInputCorners);
		mROI = findROI(mBoundingBox);
		int tPreviousRoiX = mROI.x;
		int tPreviousRoiY = mROI.y;
		mROI.x = cv::max(mROI.x, 0);
		mROI.y = cv::max(mROI.y, 0);
		mROI.width -= mROI.x - tPreviousRoiX;
		mROI.height -= mROI.y - tPreviousRoiY;
		mROI.width = cv::min(mROI.x+mROI.width, tInputImage.cols)-mROI.x;
		mROI.height = cv::min(mROI.y+mROI.height, tInputImage.rows)-mROI.y;

		//CvConvenience::matchImageFormats(mROI.width, mROI.height, tInputImage->depth, tInputImage->nChannels, &mROICopy);
		//CvConvenience::matchImageFormats(mROICopy, &mMask);
		//CvConvenience::matchImageFormats(mROICopy->width, mROICopy->height, IPL_DEPTH_32F, 1, &mTempImg);
		//CvConvenience::matchImageFormats(mTempImg, &mEigenImg);

		//std::cout
		//	<< tInputCorners[0].x << " - " <<  tInputCorners[0].y << " - "
		//	<< tInputCorners[1].x << " - " <<  tInputCorners[1].y << " - "
		//	<< tInputCorners[2].x << " - " <<  tInputCorners[2].y << " - "
		//	<< tInputCorners[3].x << " - " <<  tInputCorners[3].y <<
		//std::endl;


		mRefinedCorners[0].x = (float)(tInputCorners[0].x - mROI.x);
		mRefinedCorners[0].y = (float)(tInputCorners[0].y - mROI.y);
		mRefinedCorners[1].x = (float)(tInputCorners[1].x - mROI.x);
		mRefinedCorners[1].y = (float)(tInputCorners[1].y - mROI.y);
		mRefinedCorners[2].x = (float)(tInputCorners[2].x - mROI.x);
		mRefinedCorners[2].y = (float)(tInputCorners[2].y - mROI.y);
		mRefinedCorners[3].x = (float)(tInputCorners[3].x - mROI.x);
		mRefinedCorners[3].y = (float)(tInputCorners[3].y - mROI.y);

		cv::Mat tRoi = tInputImage(mROI);
		cv::rectangle(mMask, cvPoint(0,0), cvPoint(mMask.rows, mMask.cols), scWhite, CV_FILLED);
		mInternalCorners[0].x = (int)(mRefinedCorners[0].x*scClose + mRefinedCorners[2].x*scFar);
		mInternalCorners[0].y = (int)(mRefinedCorners[0].y*scClose + mRefinedCorners[2].y*scFar);
		mInternalCorners[1].x = (int)(mRefinedCorners[1].x*scClose + mRefinedCorners[3].x*scFar);
		mInternalCorners[1].y = (int)(mRefinedCorners[1].y*scClose + mRefinedCorners[3].y*scFar);
		mInternalCorners[2].x = (int)(mRefinedCorners[2].x*scClose + mRefinedCorners[0].x*scFar);
		mInternalCorners[2].y = (int)(mRefinedCorners[2].y*scClose + mRefinedCorners[0].y*scFar);
		mInternalCorners[3].x = (int)(mRefinedCorners[3].x*scClose + mRefinedCorners[1].x*scFar);
		mInternalCorners[3].y = (int)(mRefinedCorners[3].y*scClose + mRefinedCorners[1].y*scFar);
		const int tNPoints[1] = {Quad::scNPoints};
		const cv::Point *tCornersArray[1] = {mInternalCorners};
		cv::fillPoly(mMask, tCornersArray, tNPoints, 1, scBlack);
		mROICopy = cv::Scalar(0);
		tRoi.copyTo( mROICopy, mMask);

		mRefinedCorners.clear();
		cv::goodFeaturesToTrack(mROICopy, mRefinedCorners, Quad::scNPoints, 0.1, 20);
		cv::cornerSubPix(mROICopy, mRefinedCorners, cv::Size(5, 5), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 100, 0.000001));

		mRefinedCorners[0].x += mROI.x;
		mRefinedCorners[0].y += mROI.y;
		mRefinedCorners[1].x += mROI.x;
		mRefinedCorners[1].y += mROI.y;
		mRefinedCorners[2].x += mROI.x;
		mRefinedCorners[2].y += mROI.y;
		mRefinedCorners[3].x += mROI.x;
		mRefinedCorners[3].y += mROI.y;

		for (size_t i = 0; i < Quad::scNPoints; ++i) {
			int tClosestCornerIndex = 0;
			float tClosestCornerDist = CvConvenience::squaredDist(tInputCorners[i], mRefinedCorners[0]);
			for (int j = 1; j < mNCorners; ++j) {
				float tDist = CvConvenience::squaredDist(tInputCorners[i], mRefinedCorners[j]);
				if (tDist < tClosestCornerDist)
				{
					tClosestCornerIndex = j;
					tClosestCornerDist = tDist;
				}
			}
			mOrderedCorners[i] = (tClosestCornerDist<scMaxRefinement) ? mRefinedCorners[tClosestCornerIndex] : tInputCorners[i];
#ifdef DEBUG_Refine
			std::cout << ((tClosestCornerDist<scMaxRefinement) ? "." : "*");
		}
		std::cout << std::endl;
#else
		}
#endif

#ifdef DEBUG_Refine
		for(int i=0; i<mNCorners; ++i)
		{
			cvCircle(tInputImage, cvPointFrom32f(tInputCorners[i]), 3, cvScalarAll(128), 2);
			cvLine(tInputImage, cvPointFrom32f(mOrderedCorners[i]), cvPointFrom32f(mOrderedCorners[i]), scWhite, 5);
			printf("%1.1f  %1.1f        ", mOrderedCorners[i].x, mOrderedCorners[i].y);
		}
		printf("\n");
		//cvShowImage("Refine", tInputImage);
		//cvMoveWindow("Refine", 1600, 0);
		//cvWaitKey(5);
#endif

		cv::Point2f tOldStyleCorners[4];
		for (size_t i = 0; i < Quad::scNPoints; ++i) {
			tOldStyleCorners[i] = mOrderedCorners[i];
		}
		mRegistrar.set(tDecodedTag, tOldStyleCorners);
	}

}
