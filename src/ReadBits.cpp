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

#include "ReadBits.hpp"
#include <opencv2/imgproc/imgproc.hpp>

//#define DEBUG_ReadBits
#ifdef DEBUG_ReadBits
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#endif

//std::round is missing in the Android NDK, we implement it here (taken from AOSP):
#ifdef ANDROID
namespace std {
template <typename T>
inline T round(const T &x){
    return static_cast<T>(std::floor(static_cast<float>(x) + 0.5f));
}
}
#endif

namespace chilitags {

static const int DATA_SIZE = 6;
static const int TAG_MARGIN = 2;

ReadBits::ReadBits() :
    mSamplePoints(),
    mTransformedSamplePoints(DATA_SIZE*DATA_SIZE),
    mSamples(1, DATA_SIZE*DATA_SIZE, CV_8U),
    mBits(DATA_SIZE*DATA_SIZE)
{
    for (int y = 0; y < DATA_SIZE; ++y)
    {
        for (int x = 0; x < DATA_SIZE; ++x)
        {
            mSamplePoints.push_back(cv::Point2f(
                                        TAG_MARGIN + x + 0.5f,
                                        TAG_MARGIN + y + 0.5f));
        }
    }

#ifdef DEBUG_ReadBits
    cv::namedWindow("ReadBits-full");
    cv::namedWindow("ReadBits-tag");
#endif
}

const std::vector<unsigned char>& ReadBits::operator()(const cv::Mat &inputImage, const Quad &corners)
{
    static const float TAG_SIZE = 2*TAG_MARGIN+DATA_SIZE;
    static const Quad NORMALIZED_CORNERS = {
        0.f,      0.f,
        TAG_SIZE,      0.f,
        TAG_SIZE, TAG_SIZE,
        0.f, TAG_SIZE
    };

    cv::Mat_<cv::Point2f> cornersCopy(corners);

    // Sometimes, the corners are refined into a concave quadrilateral
    // which makes ReadBits crash
    cv::Mat convexHull;
    cv::convexHull(cornersCopy, convexHull, true);
    if (convexHull.rows != 4) {
        cornersCopy = convexHull;
        cornersCopy.push_back(0.5f*(cornersCopy(0)+cornersCopy(1)));
    }

    auto roi = cv::boundingRect(cornersCopy);

    // Refine can actually provide corners outside the image
    roi.x = cv::max(roi.x, 0);
    roi.y = cv::max(roi.y, 0);
    roi.width = cv::min(roi.width, inputImage.cols-roi.x);
    roi.height = cv::min(roi.height, inputImage.rows-roi.y);

    cv::Point2f origin = roi.tl();
    for (int i : {0,1,2,3}) cornersCopy(i) -= origin;

    cv::Matx33f transformation = cv::getPerspectiveTransform(NORMALIZED_CORNERS, cornersCopy);

    cv::perspectiveTransform(mSamplePoints, mTransformedSamplePoints, transformation);

    cv::Mat inputRoi = inputImage(roi);

    uchar* sampleData = mSamples.ptr(0);
    for (auto& transformedSamplePoint : mTransformedSamplePoints) {
        transformedSamplePoint.x = cv::max(cv::min(roi.width - 1, (int)std::round(transformedSamplePoint.x)), 0);
        transformedSamplePoint.y = cv::max(cv::min(roi.height - 1, (int)std::round(transformedSamplePoint.y)), 0);

        *sampleData++ = inputRoi.at<uchar>(transformedSamplePoint);
    }

    cv::threshold(mSamples, mBits, -1, 1, cv::THRESH_BINARY | cv::THRESH_OTSU);

#ifdef DEBUG_ReadBits
    for (int i = 0; i < DATA_SIZE; ++i)
    {
        for (int j = 0; j < DATA_SIZE; ++j)
        {
            std::cout << (int) mBits[i*DATA_SIZE + j];
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
#define ZOOM_FACTOR 10

    cv::Mat debugImage = inputImage.clone();

    cv::Mat tag;
    cv::resize(inputRoi, tag, cv::Size(0,0), ZOOM_FACTOR, ZOOM_FACTOR, cv::INTER_NEAREST);
    cv::cvtColor(tag, tag, cv::COLOR_GRAY2BGR);

    for (int i = 0; i < DATA_SIZE; ++i)
    {
        for (int j = 0; j < DATA_SIZE; ++j)
        {
            cv::Point2f position = mTransformedSamplePoints[i*DATA_SIZE + j];
            cv::circle(tag, position * ZOOM_FACTOR, 1,
                       cv::Scalar(0,255,0),2);
            cv::circle(tag, position * ZOOM_FACTOR, 3,
                       cv::Scalar::all(mBits[i*DATA_SIZE + j]*255),2);
        }
    }

    cv::circle(tag, *cornersCopy[0] * ZOOM_FACTOR, 3, cv::Scalar(255,0,0),2);

    cv::line(tag, *cornersCopy[0]*ZOOM_FACTOR, *cornersCopy[1]*ZOOM_FACTOR,cv::Scalar(255,0,0));
    cv::line(tag, *cornersCopy[1]*ZOOM_FACTOR, *cornersCopy[2]*ZOOM_FACTOR,cv::Scalar(255,0,255));
    cv::line(tag, *cornersCopy[2]*ZOOM_FACTOR, *cornersCopy[3]*ZOOM_FACTOR,cv::Scalar(255,0,255));
    cv::line(tag, *cornersCopy[3]*ZOOM_FACTOR, *cornersCopy[0]*ZOOM_FACTOR,cv::Scalar(255,0,255));

    cv::line(tag, *cornersCopy[2]*ZOOM_FACTOR, *cornersCopy[0]*ZOOM_FACTOR,cv::Scalar(255,0,255));
    cv::line(tag, *cornersCopy[3]*ZOOM_FACTOR, *cornersCopy[1]*ZOOM_FACTOR,cv::Scalar(255,0,255));

    cv::line(debugImage, *cornersCopy[0]+origin, *cornersCopy[1]+origin,cv::Scalar(255,0,255));
    cv::line(debugImage, *cornersCopy[1]+origin, *cornersCopy[2]+origin,cv::Scalar(255,0,255));
    cv::line(debugImage, *cornersCopy[2]+origin, *cornersCopy[3]+origin,cv::Scalar(255,0,255));
    cv::line(debugImage, *cornersCopy[3]+origin, *cornersCopy[0]+origin,cv::Scalar(255,0,255));


    cv::imshow("ReadBits-full", debugImage);
    cv::imshow("ReadBits-tag", tag);
    cv::waitKey(0);
#endif

    return mBits;
}

} /* namespace chilitags */
