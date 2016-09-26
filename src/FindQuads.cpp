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

#include "FindQuads.hpp"
#include <opencv2/imgproc/imgproc.hpp>


//#define DEBUG_FindQuads
#ifdef DEBUG_FindQuads
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core_c.h> // CV_AA
#endif

namespace {
const int MATRIX_SIZE = 10;
const int MIN_TAG_SIZE = 1.1f*MATRIX_SIZE;

#ifdef DEBUG_FindQuads
void drawContour(cv::Mat &image, cv::Mat &contour, cv::Scalar color, cv::Point offset) {
    std::vector<std::vector<cv::Point> >contours;
    contours.push_back(contour);
    cv::drawContours(image, contours, 0, color, 1, CV_AA, cv::noArray(), INT_MAX, offset);
    float perimeter = std::abs(cv::arcLength(contour, true));
    cv::putText(image, cv::format("%.1f", perimeter), offset+contours[0][0],
                cv::FONT_HERSHEY_SIMPLEX, 1.0f, color);
}
#endif

}

namespace chilitags {

FindQuads::FindQuads() :
    mGrayPyramid(1),
    mBinaryPyramid(1),
    mMinInputWidth(160)
{
#ifdef DEBUG_FindQuads
    cv::namedWindow("FindQuads");
#endif
}

std::vector<Quad> FindQuads::operator()(const cv::Mat &greyscaleImage)
{
    //TODO function too long, split it

    std::vector<Quad> quads;
#ifdef DEBUG_FindQuads
    cv::RNG rNG( 0xFFFFFFFF );
    cv::Mat debugImage = cv::Mat::zeros(
        cv::Size(2*greyscaleImage.cols, greyscaleImage.rows),
        CV_8UC3);
#endif

    mGrayPyramid[0] = greyscaleImage;

    // Subsample the image by a factor two,
    // as long as the width is at least mMinInputWidth
    unsigned int nPyramidLevel = 1;
    if (mMinInputWidth > 0) {
        while (mGrayPyramid[nPyramidLevel-1].cols/2 >= mMinInputWidth) {
            if (nPyramidLevel >= mGrayPyramid.size()) mGrayPyramid.push_back(cv::Mat());
            cv::resize(mGrayPyramid[nPyramidLevel-1], mGrayPyramid[nPyramidLevel], cv::Size(), 0.5f, 0.5f, cv::INTER_NEAREST);
            ++nPyramidLevel;
        }
    }

    while (mBinaryPyramid.size() < nPyramidLevel) mBinaryPyramid.push_back(cv::Mat());
    for (unsigned int i = 0; i < nPyramidLevel; ++i) {
        cv::Canny(mGrayPyramid[i], mBinaryPyramid[i], 100, 200, 3);
    }

    for (int i = nPyramidLevel-1; i>=0; --i) //starting with the lowest definition, so the highest definition are last, and can simply override the first ones.
    {
        int scale = 1 << i;
#ifdef DEBUG_FindQuads
        cv::Point offset(debugImage.cols-2*mBinaryPyramid[i].cols,0);
        cv::rectangle(debugImage, cv::Rect(offset.x, offset.y, greyscaleImage.cols/scale, greyscaleImage.rows/scale), cv::Scalar::all(255));
#endif
        std::vector<std::vector<cv::Point> > contours;
        cv::findContours(mBinaryPyramid[i], contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

        for (std::vector<std::vector<cv::Point> >::iterator contour = contours.begin();
             contour != contours.end();
             ++contour)
        {
            float perimeter = std::abs(cv::arcLength(*contour, true));
            float area = std::abs(cv::contourArea(*contour));

            if (perimeter > 4*MIN_TAG_SIZE && area > MIN_TAG_SIZE*MIN_TAG_SIZE)
            {
                cv::Mat approxContour;
                cv::approxPolyDP( *contour, approxContour, perimeter*0.05f, true);

                cv::Mat normalisedContour;
                cv::convexHull(approxContour, normalisedContour, false);

                if (normalisedContour.rows == 4)
                {
#ifdef DEBUG_FindQuads
                    drawContour(debugImage, normalisedContour, cv::Scalar(0,255,0), offset);
#endif
                    normalisedContour *= scale;
                    quads.push_back(normalisedContour.reshape(1));
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
                //drawContour(debugImage, *contour, cv::Scalar(128,128,128), offset);
            }
#endif
        }
#ifdef DEBUG_FindQuads
        cv::putText(debugImage, cv::format("%d, %d", quads.size(), contours.size()), offset+cv::Point(32,32),
                    cv::FONT_HERSHEY_SIMPLEX, 0.5f, cv::Scalar::all(255));
#endif
    }
#ifdef DEBUG_FindQuads
    cv::imshow("FindQuads", debugImage);
    cv::waitKey(0);
#endif

    return quads;
}

} /* namespace chilitags */
