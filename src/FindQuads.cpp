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

struct IsSimilarTo {
    IsSimilarTo(std::vector<cv::Point2f> quad) : mQuad(quad){
    }
    bool operator()(const std::vector<cv::Point2f> &quad) {
        // TODO make it function of the perimeter
        static const int EPSILON = 4*1;
        // TODO no seriously, do something
        float distSum = mQuad[0].x+mQuad[0].y+mQuad[1].x+mQuad[1].y+mQuad[2].x+mQuad[2].y+mQuad[3].x+mQuad[3].y-quad[0].x-quad[0].y-quad[1].x-quad[1].y-quad[2].x-quad[2].y-quad[3].x-quad[3].y;
        return -EPSILON < distSum && distSum < EPSILON;
    }

private:
    std::vector<cv::Point2f> mQuad;
};

#ifdef DEBUG_FindQuads
void drawContour(cv::Mat &image, std::vector<cv::Point> &contour, cv::Scalar color, cv::Point offset) {
    std::vector<std::vector<cv::Point> >contours;
    contours.push_back(contour);
    cv::drawContours(image, contours, 0, color, 1, CV_AA, cv::noArray(), INT_MAX, offset);
    double perimeter = std::abs(cv::arcLength(contour, true));
    cv::putText(image, cv::format("%.1f", perimeter), offset+contour[0],
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

std::vector<std::vector<cv::Point2f> > chilitags::FindQuads::operator()(const cv::Mat &greyscaleImage)
{
    cv::Canny(greyscaleImage, mBinaryImage, 100, 200, 3);

    //TODO function too long, split it

    std::vector<std::vector<cv::Point2f> > quads;
#ifdef DEBUG_FindQuads
    cv::RNG rNG( 0xFFFFFFFF );
    cv::Mat debugImage = cv::Mat::zeros(cv::Size(2*binaryImage.cols, binaryImage.rows), CV_8UC3);
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
        cv::Size scaledSize = mScaledCopies[i].size();
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
                std::vector<cv::Point> approxContour;
                cv::approxPolyDP( *contour, approxContour, perimeter*0.02, true);

                std::vector<cv::Point> normalisedContour;
                cv::convexHull(approxContour, normalisedContour, false);

                if (normalisedContour.size() == 4)
                {
                    std::vector<cv::Point2f> candidate = {
                        scale*normalisedContour[0],
                        scale*normalisedContour[1],
                        scale*normalisedContour[2],
                        scale*normalisedContour[3],
                    };

                    IsSimilarTo isSimilarToCandidate(candidate);

                    auto sameQuad = std::find_if(
                        quads.begin(),
                        quads.end(),
                        isSimilarToCandidate);
                    if (false && sameQuad != quads.end()) // TODO move to Decode
                    {
                        *sameQuad = candidate;
#ifdef DEBUG_FindQuads
                        drawContour(debugImage, normalisedContour, cv::Scalar(0,255,255), offset);
#endif
                    }
                    else
                    {
                        quads.push_back(candidate);
#ifdef DEBUG_FindQuads
                        drawContour(debugImage, normalisedContour, cv::Scalar(0,255,0), offset);
#endif
                    }
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
