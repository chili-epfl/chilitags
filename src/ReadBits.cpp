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

#include "ReadBits.hpp"
#include <opencv2/imgproc/imgproc.hpp>

//#define DEBUG_ReadBits
#ifdef DEBUG_ReadBits
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#endif

namespace {
static const int scDataSize = 6;
static const int scTagMargin = 2;
static const int scTagSize = 2*scTagMargin+scDataSize;
}

chilitags::ReadBits::ReadBits() :
    mDstBoundaries({{        0,         0},
                    {scTagSize,         0},
                    {scTagSize, scTagSize},
                    {        0, scTagSize}}),
    mSamplePoints(),
    mTransformedSamplePoints(scDataSize*scDataSize),
    mSamples(1, scDataSize*scDataSize, CV_8U),
    mBits(scDataSize*scDataSize)
{
    for (int y = 0; y < scDataSize; ++y)
    {
        for (int x = 0; x < scDataSize; ++x)
        {
            mSamplePoints.push_back(cv::Point2f(
                scTagMargin + x + .5,
                scTagMargin + y + .5));
        }
    }

#ifdef DEBUG_ReadBits
    cv::namedWindow("ReadBits-full");
    cv::namedWindow("ReadBits-tag");
#endif
}


const std::vector<unsigned char> &chilitags::ReadBits::operator()(const cv::Mat &pInputImage, const std::vector<cv::Point2f> &pCorners)
{
    auto tCorners = pCorners;

    auto tRoi = cv::boundingRect(tCorners);

    // Refine can actually provide corners outside the image
    tRoi.x = cv::max(tRoi.x, 0);
    tRoi.y = cv::max(tRoi.y, 0);
    tRoi.width = cv::min(tRoi.width, pInputImage.cols-tRoi.x);
    tRoi.height = cv::min(tRoi.height, pInputImage.rows-tRoi.y);

    cv::Point2f tOrigin = tRoi.tl();
    for (auto& p : tCorners) p -= tOrigin;

    cv::Matx33f tTransformation = cv::getPerspectiveTransform(mDstBoundaries, tCorners);

    cv::perspectiveTransform(mSamplePoints, mTransformedSamplePoints, tTransformation);

    cv::Mat tInputRoi = pInputImage(tRoi);

    uchar* tSampleData = mSamples.ptr(0);
    for (auto& tTransformedSamplePoint : mTransformedSamplePoints) {
        *tSampleData++ = tInputRoi.at<uchar>(tTransformedSamplePoint);
    }

    //cv::Mat tBinarizedImage(cv::Size(scDataSize*scDataSize, 1), CV_8U, mMatrix);
    cv::threshold(mSamples, mBits, -1, 1, cv::THRESH_BINARY | cv::THRESH_OTSU);

#ifdef DEBUG_ReadBits

    for (int i = 0; i < scDataSize; ++i)
    {
        for (int j = 0; j < scDataSize; ++j)
        {
            std::cout << (int) mMatrix[i*scDataSize + j];
        }
        std::cout << "\n";
    }
    std::cout << std::endl;

#define ZOOM_FACTOR 10

    cv::Mat debugImage = pInputImage.clone();

    cv::Mat tag;
    cv::resize(pInputImage(boundingRect(mCorners->toVector())), tag, cv::Size(0,0), ZOOM_FACTOR, ZOOM_FACTOR, cv::INTER_NEAREST);
    cv::cvtColor(tag, tag, cv::COLOR_GRAY2BGR);

    for (int i = 0; i < scDataSize; ++i)
    {
        for (int j = 0; j < scDataSize; ++j)
        {
            cv::Point2f position = tTransformedSamplePoints[i*scDataSize + j];
            cv::circle(tag, position * ZOOM_FACTOR, 1,
                       cv::Scalar(0,255,0),2);
            cv::circle(tag, position * ZOOM_FACTOR, 3,
                       cv::Scalar::all(mMatrix[i*scDataSize + j]*255),2);
        }
    }

    cv::circle(tag, tCorners[0] * ZOOM_FACTOR, 3, cv::Scalar(255,0,0),2);

    cv::line(tag, tCorners[0]*ZOOM_FACTOR, tCorners[1]*ZOOM_FACTOR,cv::Scalar(255,0,0));
    cv::line(tag, tCorners[1]*ZOOM_FACTOR, tCorners[2]*ZOOM_FACTOR,cv::Scalar(255,0,255));
    cv::line(tag, tCorners[2]*ZOOM_FACTOR, tCorners[3]*ZOOM_FACTOR,cv::Scalar(255,0,255));
    cv::line(tag, tCorners[3]*ZOOM_FACTOR, tCorners[0]*ZOOM_FACTOR,cv::Scalar(255,0,255));

    cv::line(tag, tCorners[2]*ZOOM_FACTOR, tCorners[0]*ZOOM_FACTOR,cv::Scalar(255,0,255));
    cv::line(tag, tCorners[3]*ZOOM_FACTOR, tCorners[1]*ZOOM_FACTOR,cv::Scalar(255,0,255));

    cv::line(debugImage, tCorners[0]+tOrigin, tCorners[1]+tOrigin,cv::Scalar(255,0,255));
    cv::line(debugImage, tCorners[1]+tOrigin, tCorners[2]+tOrigin,cv::Scalar(255,0,255));
    cv::line(debugImage, tCorners[2]+tOrigin, tCorners[3]+tOrigin,cv::Scalar(255,0,255));
    cv::line(debugImage, tCorners[3]+tOrigin, tCorners[0]+tOrigin,cv::Scalar(255,0,255));


    cv::imshow("ReadBits-full", debugImage);
    cv::imshow("ReadBits-tag", tag);
    cv::waitKey(0);
#endif

    return mBits;
}
