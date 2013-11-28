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

//#define DEBUG_Refine
#ifdef DEBUG_Refine
#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#endif

chilitags::Refine::Refine() :
	mRefinedQuads()
{
#ifdef DEBUG_Refine
	cv::namedWindow("Refine");
#endif
}

void chilitags::Refine::operator()(const cv::Mat pInputImage, const std::vector<std::vector<cv::Point2f>> &pQuads)
{
    mRefinedQuads.clear();

	for (const auto& tQuad : pQuads)
	{
		auto tCorners = tQuad;

		// Taking a ROI around the raw corners with some margin
		static const float scGrowthRatio = 2.0f/10.0f;
		cv::Rect tRoi = cv::boundingRect(tCorners);
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
		tRoi.width = cv::min(tRoi.x+tRoi.width, pInputImage.cols)-tRoi.x;
		tRoi.height = cv::min(tRoi.y+tRoi.height, pInputImage.rows)-tRoi.y;

		cv::Point2f tRoiOffset = tRoi.tl();
		tCorners[0] -= tRoiOffset;
		tCorners[1] -= tRoiOffset;
		tCorners[2] -= tRoiOffset;
		tCorners[3] -= tRoiOffset;

		static const double scProximityRatio = 1.5/10.0;
		double tAverageSideLength = cv::arcLength(tCorners, true) / 4.0;
		double tCornerNeighbourhood = scProximityRatio*tAverageSideLength;
		
 		// ensure the cornerSubPixel search window is smaller that the ROI
 		tCornerNeighbourhood = cv::min(tCornerNeighbourhood, ((double) tRoi.width-5)/2);
 		tCornerNeighbourhood = cv::min(tCornerNeighbourhood, ((double) tRoi.height-5)/2);
		
		cv::cornerSubPix(pInputImage(tRoi), tCorners,
			cv::Size(tCornerNeighbourhood, tCornerNeighbourhood),
			cv::Size(-1, -1), cv::TermCriteria(
				cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS,
				5, 0.01));

		tCorners[0] += tRoiOffset;
		tCorners[1] += tRoiOffset;
		tCorners[2] += tRoiOffset;
		tCorners[3] += tRoiOffset;

#ifdef DEBUG_Refine
		cv::Mat tDebugImage = tInputImage(tRoi).clone();
		for(int i=0; i<4; ++i)
		{
			cv::circle(tDebugImage, tCorners[i]-tRoiOffset,
				3, cv::Scalar::all(128), 2);
			cv::line(tDebugImage,
				tCorners[i]-tRoiOffset, tCorners[i]-tRoiOffset,
				cv::Scalar::all(255), 5);
			printf("%1.1f  %1.1f        ", tCorners[i].x, tCorners[i].y);
		}
		printf("\n");
		cv::imshow("Refine", tDebugImage);
		cv::waitKey(0);
#endif

	    mRefinedQuads.push_back(tCorners);
	}

}
