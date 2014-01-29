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

chilitags::Refine::Refine()
{
#ifdef DEBUG_Refine
    cv::namedWindow("Refine");
#endif
}

chilitags::Quad chilitags::Refine::operator()(const cv::Mat &inputImage, const Quad &quad)
{
    cv::Mat_<cv::Point2f> refinedQuad(quad);

    // Taking a ROI around the raw corners with some margin
    static const float GROWTH_RATIO = 2.0f/10.0f;
    cv::Rect roi = cv::boundingRect(refinedQuad);
    int xGrowth = (int)(GROWTH_RATIO*roi.width);
    int yGrowth = (int)(GROWTH_RATIO*roi.height);
    roi.x -= xGrowth;
    roi.y -= yGrowth;
    roi.width += 2*xGrowth;
    roi.height += 2*yGrowth;

    // Making sure the ROI is still in the image
    int previousRoiX = roi.x;
    int previousRoiY = roi.y;
    roi.x = std::max(roi.x, 0);
    roi.y = std::max(roi.y, 0);
    roi.width -= roi.x - previousRoiX;
    roi.height -= roi.y - previousRoiY;
    roi.width = cv::min(roi.x+roi.width, inputImage.cols)-roi.x;
    roi.height = cv::min(roi.y+roi.height, inputImage.rows)-roi.y;

    static const int MIN_ROI_SIZE = 10;
    if (roi.width < MIN_ROI_SIZE || roi.height < MIN_ROI_SIZE) return quad;

    cv::Point2f roiOffset = roi.tl();
    for (int i : {0,1,2,3}) refinedQuad(i) -= roiOffset;

    static const double PROXIMITYRATIO = 1.5/10.0;
    double averageSideLength = cv::arcLength(refinedQuad, true) / 4.0;
    double cornerNeighbourhood = PROXIMITYRATIO*averageSideLength;

    // ensure the cornerSubPixel search window is smaller that the ROI
    cornerNeighbourhood = cv::min(cornerNeighbourhood, ((double) roi.width-5)/2);
    cornerNeighbourhood = cv::min(cornerNeighbourhood, ((double) roi.height-5)/2);

    cv::cornerSubPix(inputImage(roi), refinedQuad,
                     cv::Size(cornerNeighbourhood, cornerNeighbourhood),
                     cv::Size(-1, -1), cv::TermCriteria(
                         cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS,
                         5, 0.01));

    for (int i : {0,1,2,3}) refinedQuad(i) += roiOffset;

#ifdef DEBUG_Refine
    cv::Mat debugImage = inputImage(roi).clone();
    for(int i=0; i<4; ++i)
    {
        cv::circle(debugImage, refinedQuad[i]-roiOffset,
                   3, cv::Scalar::all(128), 2);
        cv::line(debugImage,
                 refinedQuad[i]-roiOffset, refinedQuad[i]-roiOffset,
                 cv::Scalar::all(255), 5);
        printf("%1.1f  %1.1f        ", refinedQuad[i].x, refinedQuad[i].y);
    }
    printf("\n");
    cv::imshow("Refine", debugImage);
    cv::waitKey(0);
#endif

    // Sometimes, the corners are refined into a concave quadrilateral
    // which makes ReadBits crash
    cv::Mat convexHull;
    cv::convexHull(refinedQuad, convexHull, false);
    if (convexHull.rows == 4) return convexHull.reshape(1);

    return quad;
}
