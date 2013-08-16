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
#include <opencv2/imgproc/imgproc.hpp>

//#define DEBUG_Refine
#ifdef DEBUG_Refine
#include <stdio.h>
#include <iostream>
#endif

namespace {
const float scClose = 1.0f/10.0f;
const float scFar = 1.0f-scClose;
const cv::Scalar scWhite(255,255,255);
const cv::Scalar scBlack(0, 0, 0);
const float scMaxRefinement = 4.0f; // TODO make relative to resolution

//TODO take more; use length of tag rather than bbox
cv::Rect findROI(const cv::Rect &pMinimalROI) {
	static const float scMarginRatio = scClose;
	int tXMargin = (int)(scMarginRatio*pMinimalROI.width);
	int tYMargin = (int)(scMarginRatio*pMinimalROI.height);
	return cv::Rect(pMinimalROI.x-tXMargin, pMinimalROI.y-tYMargin, pMinimalROI.width+2*tXMargin, pMinimalROI.width+2*tYMargin);         //FIXME: border effect
}
}

chilitags::Refine::Refine(
        const cv::Mat *pInputImage,
        const int *pDecodedTag,
        Registrar &pRegistrar) :
	mInputImage(pInputImage),
	mDecodedTag(pDecodedTag),
	mRefinedCorners(4),
	mOrderedCorners(4),
	mRegistrar(pRegistrar)
{
#ifdef DEBUG_Refine
	cv::namedWindow("Refine");
#endif
}

chilitags::Refine::~Refine()
{
}

void chilitags::Refine::run()
{
	int tDecodedTag = *mDecodedTag;
	if (tDecodedTag > -1)
	{
		const cv::Mat tInputImage = *mInputImage;
		const cv::Point2f *tInputCorners = mRegistrar.getCorners(tDecodedTag);

		std::vector<cv::Point2f> tInputCornersVector;
		tInputCornersVector.assign(tInputCorners, tInputCorners+4);
		cv::Rect tBoundingBox = cv::boundingRect(tInputCornersVector);
		cv::Rect tROI = findROI(tBoundingBox);

		int tPreviousRoiX = tROI.x;
		int tPreviousRoiY = tROI.y;
		tROI.x = std::max(tROI.x, 0);
		tROI.y = std::max(tROI.y, 0);
		tROI.width -= tROI.x - tPreviousRoiX;
		tROI.height -= tROI.y - tPreviousRoiY;
		tROI.width = cv::min(tROI.x+tROI.width, tInputImage.cols)-tROI.x;
		tROI.height = cv::min(tROI.y+tROI.height, tInputImage.rows)-tROI.y;

		cv::Point2f tRoiTL = tROI.tl();
		mRefinedCorners[0] = tInputCorners[0] - tRoiTL;
		mRefinedCorners[1] = tInputCorners[1] - tRoiTL;
		mRefinedCorners[2] = tInputCorners[2] - tRoiTL;
		mRefinedCorners[3] = tInputCorners[3] - tRoiTL;

		cv::Mat tMask(tROI.size(), tInputImage.type(), scWhite);
		mInternalCorners[0] = mRefinedCorners[0]*scClose + mRefinedCorners[2]*scFar;
		mInternalCorners[1] = mRefinedCorners[1]*scClose + mRefinedCorners[3]*scFar;
		mInternalCorners[2] = mRefinedCorners[2]*scClose + mRefinedCorners[0]*scFar;
		mInternalCorners[3] = mRefinedCorners[3]*scClose + mRefinedCorners[1]*scFar;

		const int tNPoints[1] = {Quad::scNPoints};
		const cv::Point *tCornersArray[1] = {mInternalCorners};
		cv::fillPoly(tMask, tCornersArray, tNPoints, 1, scBlack);
		cv::Mat tROICopy(tROI.size(), tInputImage.type());
		tInputImage(tROI).copyTo( tROICopy, tMask);
#ifdef DEBUG_Refine
		cv::imshow("Refine", tROICopy);
		cv::waitKey(0);
#endif

		mRefinedCorners.clear();
		cv::goodFeaturesToTrack(tROICopy, mRefinedCorners, Quad::scNPoints, 0.1, 20);
		cv::cornerSubPix(tROICopy, mRefinedCorners, cv::Size(5, 5), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 100, 0.000001));

		mRefinedCorners[0] += tRoiTL;
		mRefinedCorners[1] += tRoiTL;
		mRefinedCorners[2] += tRoiTL;
		mRefinedCorners[3] += tRoiTL;

		for (size_t i = 0; i < Quad::scNPoints; ++i) {
			int tClosestCornerIndex = 0;
			double tClosestCornerDist = cv::norm(tInputCorners[i] - mRefinedCorners[0]);
			for (size_t j = 1; j < mRefinedCorners.size(); ++j) {
				double tDist = cv::norm(tInputCorners[i] - mRefinedCorners[j]);
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
		cv::Mat tDebugImage = tInputImage.clone();
		for(int i=0; i<Quad::scNPoints; ++i)
		{
			cv::circle(tDebugImage, tInputCorners[i], 3, cv::Scalar::all(128), 2);
			cv::line(tDebugImage, mOrderedCorners[i], mOrderedCorners[i], scWhite, 5);
			printf("%1.1f  %1.1f        ", mOrderedCorners[i].x, mOrderedCorners[i].y);
		}
		printf("\n");
		cv::imshow("Refine", tInputImage);
		cv::waitKey(0);
#endif

		cv::Point2f tOldStyleCorners[4];
		for (size_t i = 0; i < Quad::scNPoints; ++i) {
			tOldStyleCorners[i] = mOrderedCorners[i];
		}
		mRegistrar.set(tDecodedTag, tOldStyleCorners);
	}

}
