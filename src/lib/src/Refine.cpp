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
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
//#define DEBUG_Refine
#ifdef DEBUG_Refine
#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#endif

chilitags::Refine::Refine(
        const cv::Mat *pInputImage,
        const std::vector<Quad>* quads):
	mInputImage(pInputImage),
	mQuads(*quads),
	mRefinedCorners(4)
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
    mRefinedQuads.clear();

	for (const auto& quad : mQuads)
	{
		const cv::Mat tInputImage = *mInputImage;
		mRefinedCorners = quad.toVector();

		// Taking a ROI around the raw corners with some margin
		static const float scGrowthRatio = 2.0f/10.0f;
		cv::Rect tRoi = cv::boundingRect(mRefinedCorners);
		int tXGrowth = (int)(scGrowthRatio*tRoi.width);
		int tYGrowth = (int)(scGrowthRatio*tRoi.height);
		tRoi.x -= tXGrowth;
		tRoi.y -= tYGrowth;
		tRoi.width += 2*tXGrowth;
		tRoi.height += 2*tYGrowth;

		// Making sure the ROI is still in the image
		int tPreviousRoiX = tRoi.x;
		int tPreviousRoiY = tRoi.y;
		tRoi.x = std::max(tRoi.x, 0);
		tRoi.y = std::max(tRoi.y, 0);
		tRoi.width -= tRoi.x - tPreviousRoiX;
		tRoi.height -= tRoi.y - tPreviousRoiY;
		tRoi.width = cv::min(tRoi.x+tRoi.width, tInputImage.cols)-tRoi.x;
		tRoi.height = cv::min(tRoi.y+tRoi.height, tInputImage.rows)-tRoi.y;

		cv::Point2f tRoiOffset = tRoi.tl();
		mRefinedCorners[0] -= tRoiOffset;
		mRefinedCorners[1] -= tRoiOffset;
		mRefinedCorners[2] -= tRoiOffset;
		mRefinedCorners[3] -= tRoiOffset;

		static const double scProximityRatio = 1.5/10.0;
		double tAverageSideLength =
			cv::arcLength(mRefinedCorners, true)
			/ (double) Quad::scNPoints;
		double tCornerNeighbourhood = scProximityRatio*tAverageSideLength;
		
 		// ensure the cornerSubPixel search window is smaller that the ROI
 		tCornerNeighbourhood = cv::min(tCornerNeighbourhood, ((double) tRoi.width-5)/2);
 		tCornerNeighbourhood = cv::min(tCornerNeighbourhood, ((double) tRoi.height-5)/2);
		
		cv::cornerSubPix(tInputImage(tRoi), mRefinedCorners,
			cv::Size(tCornerNeighbourhood, tCornerNeighbourhood),
			cv::Size(-1, -1), cv::TermCriteria(
				cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS,
				5, 0.01));

		mRefinedCorners[0] += tRoiOffset;
		mRefinedCorners[1] += tRoiOffset;
		mRefinedCorners[2] += tRoiOffset;
		mRefinedCorners[3] += tRoiOffset;

#ifdef DEBUG_Refine
		cv::Mat tDebugImage = tInputImage(tRoi).clone();
		for(int i=0; i<Quad::scNPoints; ++i)
		{
			cv::circle(tDebugImage, quad[i]-tRoiOffset,
				3, cv::Scalar::all(128), 2);
			cv::line(tDebugImage,
				mRefinedCorners[i]-tRoiOffset, mRefinedCorners[i]-tRoiOffset,
				cv::Scalar::all(255), 5);
			printf("%1.1f  %1.1f        ", mRefinedCorners[i].x, mRefinedCorners[i].y);
		}
		printf("\n");
		cv::imshow("Refine", tDebugImage);
		cv::waitKey(0);
#endif

	    mRefinedQuads.push_back(Quad(mRefinedCorners));
	}

}
