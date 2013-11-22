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

using namespace std;

namespace {
static const int scDataSize = 6;
static const int scTagMargin = 2;
static const int scTagSize = scDataSize+2*scTagMargin;
static const float scFar = scTagMargin/(float) scTagSize;
static const float scClose = 1.0f - scFar;
}

chilitags::ReadBits::ReadBits(const cv::Mat *pInputImage,
                              const Quad *pCorners) :
	mCorners(pCorners),
	mInputImage(*pInputImage),
	mMatrix(new unsigned char[scDataSize*scDataSize])
{
    mDstBoundaries = {{0,0},
                      {scDataSize, 0},
                      {scDataSize, scDataSize},
                      {0, scDataSize}};

    for (int i = 0; i < scDataSize; ++i)
    {
        for (int j = 0; j < scDataSize; ++j)
        {
            cv::Point2f tPosition(i + .5, j + .5);
            mSamplePoints.push_back(tPosition);
        }
    }


#ifdef DEBUG_ReadBits
	cv::namedWindow("ReadBits-full");
	cv::namedWindow("ReadBits-marker");
#endif
}

chilitags::ReadBits::~ReadBits()
{
	delete[] mMatrix;
}


void chilitags::ReadBits::run()
{

    Quad tCorners = *mCorners;

    mSrcBoundaries.clear();
    mSrcBoundaries.push_back(tCorners[0]*scClose + tCorners[2]*scFar);
    mSrcBoundaries.push_back(tCorners[1]*scClose + tCorners[3]*scFar);
    mSrcBoundaries.push_back(tCorners[2]*scClose + tCorners[0]*scFar);
    mSrcBoundaries.push_back(tCorners[3]*scClose + tCorners[1]*scFar);

    cv::Mat tBinarizedImage;
    cv::threshold(mInputImage(boundingRect(mSrcBoundaries)), tBinarizedImage, -1, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);


    cv::Point2f tOrigin = boundingRect(mSrcBoundaries).tl();
    for (auto& p : mSrcBoundaries) p -= tOrigin;

	cv::Matx33f tTransformation = cv::getPerspectiveTransform(mDstBoundaries, mSrcBoundaries);


    vector<cv::Point2f> tTransformedSamplePoints;

    cv::perspectiveTransform(mSamplePoints, tTransformedSamplePoints, tTransformation);

    for (int i = 0; i < scDataSize; ++i)
    {
        for (int j = 0; j < scDataSize; ++j)
        {
            auto tPoint = tTransformedSamplePoints[i + j * scDataSize];
            if (   tPoint.x < 0 || tPoint.x > tBinarizedImage.cols
                || tPoint.y < 0 || tPoint.y > tBinarizedImage.rows)
            {
#ifdef DEBUG_ReadBits
                cout << "Transformed point out of the image!" << endl;
#endif
                continue;
            }
            mMatrix[i*scDataSize + j] = (tBinarizedImage.at<uchar>(tPoint) > 128);
        }
    }

#ifdef DEBUG_ReadBits

#define ZOOM_FACTOR 10

    //cv::Mat debugImage = mBinarize.mInputImage.clone();
    cv::Mat debugImage = mInputImage.clone();

    cv::Mat marker;
    cv::resize(tBinarizedImage, marker, cv::Size(0,0), ZOOM_FACTOR, ZOOM_FACTOR, cv::INTER_NEAREST);
    cv::cvtColor(marker, marker, cv::COLOR_GRAY2BGR);

    for (int i = 0; i < scDataSize; ++i)
    {
        for (int j = 0; j < scDataSize; ++j)
        {
            cv::Point2f position = tTransformedSamplePoints[i + j * scDataSize];
            if (mMatrix[i*scDataSize + j]) {
                cv::circle(marker, position * ZOOM_FACTOR, 3, cv::Scalar(0,128,0));
                //cv::circle(debugImage, position + tOrigin, 1, cv::Scalar(0,0,0));
            }
            else {
                cv::circle(marker, position * ZOOM_FACTOR, 3, cv::Scalar(255,128,0),2);
                //cv::circle(debugImage, position + tOrigin, 1, cv::Scalar(255,0,0));
            }
        }
    }
    cv::line(marker, mSrcBoundaries[0]*ZOOM_FACTOR, mSrcBoundaries[1]*ZOOM_FACTOR,cv::Scalar(255,0,255));
    cv::line(marker, mSrcBoundaries[1]*ZOOM_FACTOR, mSrcBoundaries[2]*ZOOM_FACTOR,cv::Scalar(255,0,255));
    cv::line(marker, mSrcBoundaries[2]*ZOOM_FACTOR, mSrcBoundaries[3]*ZOOM_FACTOR,cv::Scalar(255,0,255));
    cv::line(marker, mSrcBoundaries[3]*ZOOM_FACTOR, mSrcBoundaries[0]*ZOOM_FACTOR,cv::Scalar(255,0,255));

    cv::line(debugImage, mSrcBoundaries[0]+tOrigin, mSrcBoundaries[1]+tOrigin,cv::Scalar(255,0,255));
    cv::line(debugImage, mSrcBoundaries[1]+tOrigin, mSrcBoundaries[2]+tOrigin,cv::Scalar(255,0,255));
    cv::line(debugImage, mSrcBoundaries[2]+tOrigin, mSrcBoundaries[3]+tOrigin,cv::Scalar(255,0,255));
    cv::line(debugImage, mSrcBoundaries[3]+tOrigin, mSrcBoundaries[0]+tOrigin,cv::Scalar(255,0,255));


	cv::imshow("ReadBits-full", debugImage);
	cv::imshow("ReadBits-marker", marker);
    cv::waitKey(0);
#endif
}
