/*******************************************************************************
*   Copyright 2013-2014 EPFL                                                   *
*   Copyright 2013-2014 Quentin Bonnard                                        *
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

#include "GrowRoi.hpp"
#include <opencv2/imgproc/imgproc.hpp>

//#define DEBUG_Refine
#ifdef DEBUG_Refine
#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#endif

namespace chilitags {

Refine::Refine()
{
#ifdef DEBUG_Refine
    cv::namedWindow("Refine");
#endif
}

Quad Refine::operator()(
    const cv::Mat &inputImage,
    const Quad &quad,
    const float proximityRatio)
{
    cv::Mat_<cv::Point2f> refinedQuad(quad);

    // Taking a ROI around the raw corners with some margin
    static const float GROWTH_RATIO = 1.2f/10.0f;
    cv::Rect roi = chilitags::growRoi(inputImage, refinedQuad, GROWTH_RATIO);

    static const int MIN_ROI_SIZE = 10;
    if (roi.width < MIN_ROI_SIZE || roi.height < MIN_ROI_SIZE) return quad;

    cv::Point2f roiOffset = roi.tl();
    for (int i : {0,1,2,3}) refinedQuad(i) -= roiOffset;

    float averageSideLength = cv::arcLength(refinedQuad, true) / 4.0f;
    float cornerNeighbourhood = proximityRatio*averageSideLength;

    // ensure the cornerSubPixel search window is smaller that the ROI
    cornerNeighbourhood = cv::min(cornerNeighbourhood, (roi.width - 5.0f)/2.0f);
    cornerNeighbourhood = cv::min(cornerNeighbourhood, (roi.height - 5.0f)/2.0f);
    cornerNeighbourhood = cv::max(cornerNeighbourhood, 1.0f);

    cv::cornerSubPix(inputImage(roi), refinedQuad,
                     cv::Size(cornerNeighbourhood, cornerNeighbourhood),
                     cv::Size(-1, -1), cv::TermCriteria(
                         cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS,
                         5, 0.01f));

#ifdef DEBUG_Refine
    cv::Mat debugImage = inputImage(roi).clone();
    for(int i=0; i<4; ++i)
    {
        cv::circle(debugImage, refinedQuad(i), 3, cv::Scalar::all(128), 2);
        cv::line(debugImage,
                 refinedQuad(i), refinedQuad(i),
                 cv::Scalar::all(255), 5);
        cv::rectangle(debugImage,
                      refinedQuad(i)-cv::Point2f(cornerNeighbourhood, cornerNeighbourhood), refinedQuad(i)+cv::Point2f(cornerNeighbourhood, cornerNeighbourhood),
                      cv::Scalar::all(255));
        printf("%1.1f  %1.1f        ", refinedQuad(i).x, refinedQuad(i).y);
    }
    printf("\n");
    cv::imshow("Refine", debugImage);
    cv::waitKey(0);
#endif

    for (int i : {0,1,2,3}) refinedQuad(i) += roiOffset;

    return refinedQuad.reshape(1);
}

} /* namespace chilitags */
