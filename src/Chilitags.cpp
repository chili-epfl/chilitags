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

#include <chilitags.hpp>

#include "EnsureGreyscale.hpp"
#include "Filter.hpp"
#include "Detect.hpp"
#include "Track.hpp"

#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

// The class that takes care of all the detection of Chilitags.
namespace chilitags {

namespace {
    chilitags::TagCornerMap scaleBy(chilitags::TagCornerMap tags, float factor) {
        if (factor == 1.0f) return tags;
        for(auto &tag: tags) {
            //Maybe this translation should be moved to Refine ?
            cv::add(tag.second, cv::Scalar::all(-0.5f), tag.second);
            tag.second = factor*tag.second;
            cv::add(tag.second, cv::Scalar::all(0.5f), tag.second);
        }
        return tags;
    }
}

class Chilitags::Impl
{

public:

Impl() :
    mMaxInputWidth(0),
    mResizedInput(),

    mEnsureGreyscale(),
    mDecode(),

    mFilter(5, 0.f),
    mDetect(),
    mTrack(),

    mCallsBeforeDetection(15),
    mCallsBeforeNextDetection(0)
{
    setPerformance(FAST);
}

void setFilter(int persistence, float gain) {
    mFilter.setPersistence(persistence);
    mFilter.setGain(gain);
}

void setPerformance(PerformancePreset preset) {
    switch (preset) {
        case FASTER:
            mDetect.setCornerRefinement(false);
            mDetect.setMinInputWidth(0);
            break;
        case FAST:
            mDetect.setCornerRefinement(true);
            mDetect.setMinInputWidth(0);
            break;
        case ROBUST:
            mDetect.setCornerRefinement(true);
            mDetect.setMinInputWidth(160);
            break;
        default:
            break;
    }
}

void setCornerRefinement(bool refineCorners) {
    mDetect.setCornerRefinement(refineCorners);
}

void setMaxInputWidth(int maxWidth) {
    mMaxInputWidth = maxWidth;
}

void setMinInputWidth(int minWidth) {
    mDetect.setMinInputWidth(minWidth);
}

void setDetectionPeriod(int period) {
    mCallsBeforeDetection = period;
}

TagCornerMap find(
    const cv::Mat &inputImage,
    DetectionTrigger detectionTrigger){

    // Resize the input image to make it at most mMaxInputWidth wide
    float scaleFactor = 1.0f;
    if (mMaxInputWidth > 0 && inputImage.cols > mMaxInputWidth) {
        scaleFactor =(float) inputImage.cols/(float)mMaxInputWidth;
        cv::resize(inputImage, mResizedInput, cv::Size(), 1.0f/scaleFactor , 1.0f/scaleFactor , cv::INTER_NEAREST);
    }
    else {
        mResizedInput = inputImage;
    }

    mCallsBeforeNextDetection = std::max(mCallsBeforeNextDetection-1, 0);
    if (detectionTrigger == DETECT_PERIODICALLY) {
        detectionTrigger = (mCallsBeforeNextDetection > 0)?TRACK_ONLY:TRACK_AND_DETECT;
    }

    if (detectionTrigger == TRACK_ONLY)
        return scaleBy(mTrack(mResizedInput), scaleFactor);

    // now we're going to do a full detection
    mCallsBeforeNextDetection = mCallsBeforeDetection;

    cv::Mat greyscaleImage = mEnsureGreyscale(mResizedInput);
    TagCornerMap tags;

    if (detectionTrigger == TRACK_AND_DETECT) {
        // track first to override tracked tags with actually detected tags
        tags = mTrack(mResizedInput);
    }

    mDetect(greyscaleImage, tags);

    if (detectionTrigger == TRACK_AND_DETECT) {
        // the current input image has already been updated in mTrack()
        mTrack.update(tags);
    }
    else {
        mTrack.update(greyscaleImage, tags);
    }

    return scaleBy(mFilter(tags), scaleFactor);
};

cv::Matx<unsigned char, 6, 6> encode(int id) const {
    cv::Matx<unsigned char, 6, 6> encodedId;
    mDecode.getCodec().getTagEncodedId(id, encodedId.val);
    return encodedId;
}

int decode(const cv::Matx<unsigned char, 6, 6> &bits) const {
    int id = -1;
    mDecode.getCodec().decode(bits.val, id);
    return id;
}

cv::Mat draw(int id, int cellSize, bool withMargin, cv::Scalar color) const {
    // Creating the image of the bit matrix
    static const int DATA_SIZE = 6;
    cv::Size dataDim(DATA_SIZE,DATA_SIZE);
    unsigned char dataMatrix[DATA_SIZE*DATA_SIZE];
    mDecode.getCodec().getTagEncodedId(id, dataMatrix);
    cv::Mat dataImage(dataDim, CV_8U, dataMatrix);

    // Adding the black border arounf the bit matrix
    cv::Size borderSize(2,2);
    cv::Mat tagImage(dataImage.size()+borderSize*2, CV_8U, cv::Scalar(0));
    dataImage.copyTo(tagImage(cv::Rect(borderSize, dataImage.size())));

    // Adding the optionnal white margin
    cv::Size marginSize(0,0);
    if (withMargin) marginSize += borderSize;
    cv::Mat outlinedImage(tagImage.size()+marginSize*2, CV_8U, cv::Scalar(1));
    tagImage.copyTo(outlinedImage(cv::Rect(marginSize, tagImage.size())));

    // Resizing to specified cellSize
    cv::Mat sizedImage(outlinedImage.size()*cellSize, CV_8U);
    cv::resize(outlinedImage, sizedImage, sizedImage.size(), 0, 0, cv::INTER_NEAREST);

    // Coloring
    cv::Mat   redImage = (1-sizedImage)*color[0]+sizedImage*255;
    cv::Mat greenImage = (1-sizedImage)*color[1]+sizedImage*255;
    cv::Mat  blueImage = (1-sizedImage)*color[2]+sizedImage*255;
    cv::Mat colorImage(sizedImage.size(), CV_8UC3);
    cv::merge(std::vector<cv::Mat>{blueImage, greenImage, redImage}, colorImage);

    return colorImage;
}

protected:

int mMaxInputWidth;
cv::Mat mResizedInput;

EnsureGreyscale mEnsureGreyscale;

Decode mDecode;

Filter<int, Quad> mFilter;

Detect mDetect;

Track mTrack;

int mCallsBeforeNextDetection;
int mCallsBeforeDetection;

};

Chilitags::Chilitags() :
    mImpl(new Impl())
{
}

void Chilitags::setFilter(int persistence, float gain) {
    mImpl->setFilter(persistence, gain);
}

void Chilitags::setPerformance(PerformancePreset preset) {
    mImpl->setPerformance(preset);
}

void Chilitags::setCornerRefinement(bool refineCorners) {
    mImpl->setCornerRefinement(refineCorners);
}

void Chilitags::setMaxInputWidth(int maxWidth) {
    mImpl->setMaxInputWidth(maxWidth);
}

void Chilitags::setMinInputWidth(int minWidth) {
    mImpl->setMinInputWidth(minWidth);
}

TagCornerMap Chilitags::find(
    const cv::Mat &inputImage,
    DetectionTrigger trigger
    ) {
    return mImpl->find(inputImage, trigger);
}

void Chilitags::setDetectionPeriod(int period) {
    mImpl->setDetectionPeriod(period);
}

cv::Matx<unsigned char, 6, 6> Chilitags::encode(int id) const {
    return mImpl->encode(id);
}

int Chilitags::decode(const cv::Matx<unsigned char, 6, 6> & bits) const {
    return mImpl->decode(bits);
}

cv::Mat Chilitags::draw(int id, int cellSize, bool withMargin, cv::Scalar color) const {
    return mImpl->draw(id, cellSize, withMargin, color);
}

Chilitags::~Chilitags() = default;

}
