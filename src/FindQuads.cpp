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

#include "FindQuads.hpp"
#include <opencv2/imgproc/imgproc.hpp>

//#define DEBUG_FindQuads
#ifdef DEBUG_FindQuads
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core_c.h> // CV_AA
#endif

namespace {
const int MATRIX_SIZE = 10;
const int MIN_TAG_SIZE = 1.2*MATRIX_SIZE;

#ifdef DEBUG_FindQuads
void drawContour(cv::Mat &image, cv::Mat &contour, cv::Scalar color, cv::Point offset) {
    std::vector<std::vector<cv::Point> >contours;
    contours.push_back(contour);
    cv::drawContours(image, contours, 0, color, 1, CV_AA, cv::noArray(), INT_MAX, offset);
    double perimeter = std::abs(cv::arcLength(contour, true));
    cv::putText(image, cv::format("%.1f", perimeter), offset+contours[0][0],
                cv::FONT_HERSHEY_SIMPLEX, 1.0, color);
}
#endif

}

chilitags::FindQuads::FindQuads() :
    mBinaryImage()
{
#ifdef DEBUG_FindQuads
    cv::namedWindow("FindQuads");
#endif
}

std::vector<chilitags::Quad> chilitags::FindQuads::operator()(const cv::Mat &greyscaleImage)
{
    cv::Canny(greyscaleImage, mBinaryImage, 100, 200, 3);

    //TODO function too long, split it

    std::vector<Quad> quads;
#ifdef DEBUG_FindQuads
    cv::RNG rNG( 0xFFFFFFFF );
    cv::Mat debugImage = cv::Mat::zeros(cv::Size(2*mBinaryImage.cols, mBinaryImage.rows), CV_8UC3);
#endif

    mScaledCopies[0] = mBinaryImage;
    for (int i = 1; i < SCALED_COPIES_COUNT; ++i) {
        cv::pyrDown(mScaledCopies[i-1], mScaledCopies[i]);
    }

    for (int i = SCALED_COPIES_COUNT-1; i>=0; --i) //starting with the lowest definition, so the highest definition are last, and can simply override the first ones.
    {
        int scale = 1 << i;
#ifdef DEBUG_FindQuads
        cv::Point offset(debugImage.cols-2*mScaledCopies[i].cols,0);
#endif
        std::vector<std::vector<cv::Point> > contours;
        cv::findContours(mScaledCopies[i], contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

        for (std::vector<std::vector<cv::Point> >::iterator contour = contours.begin();
             contour != contours.end();
             ++contour)
        {
            double perimeter = std::abs(cv::arcLength(*contour, true));
            double area = std::abs(cv::contourArea(*contour));

            if (perimeter > 4*MIN_TAG_SIZE && area > MIN_TAG_SIZE*MIN_TAG_SIZE)
            {
                cv::Mat approxContour;
                cv::approxPolyDP( *contour, approxContour, perimeter*0.02, true);

                cv::Mat normalisedContour;
                cv::convexHull(approxContour, normalisedContour, false);

                if (normalisedContour.rows == 4)
                {
                    normalisedContour *= scale;
                    quads.push_back(normalisedContour.reshape(1));
#ifdef DEBUG_FindQuads
                    drawContour(debugImage, normalisedContour, cv::Scalar(0,255,0), offset);
#endif
                }
#ifdef DEBUG_FindQuads
                else // not quadrilaterals
                {
                    drawContour(debugImage, normalisedContour, cv::Scalar(0,0,255), offset);
                }
#endif
            }
#ifdef DEBUG_FindQuads
            else // too small
            {
                drawContour(debugImage, *contour, cv::Scalar(128,128,128), offset);
            }
#endif
        }
#ifdef DEBUG_FindQuads
        cv::putText(debugImage, cv::format("%d", contours.size()), offset+cv::Point(32,32),
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar::all(255));
#endif
    }
#ifdef DEBUG_FindQuads
    cv::imshow("FindQuads", debugImage);
    cv::waitKey(0);
#endif

    return quads;
}
