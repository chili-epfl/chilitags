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
#include "FindQuads.hpp"

#include "ReadBits.hpp"
#include "Decode.hpp"
#include "Refine.hpp"

#include "Filter.hpp"

#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

// The class that takes care of all the detection of Chilitags.
namespace chilitags {

class Chilitags::Impl
{

public:

Impl() :
    mEnsureGreyscale(),
    mFindQuads(),

    mRefine(),
    mReadBits(),
    mDecode(),

    mFilter(5, 0.),

    mRefineCorners(true)
{
    tunePerformance(ACCURATE);
}

void setFilter(int persistence, double gain) {
    mFilter.setPersistence(persistence);
    mFilter.setGain(gain);
}

void tunePerformance(PerformancePreset preset) {
    switch (preset) {
        case FASTER:
            setCornerRefinement(false);
            mFindQuads.setMinInputWidth(0);
            break;
        case FAST:
            setCornerRefinement(true);
            mFindQuads.setMinInputWidth(0);
            break;
        case ACCURATE:
            setCornerRefinement(true);
            mFindQuads.setMinInputWidth(160);
            break;
        defaut:
            break;
    }
}
void setCornerRefinement(bool refineCorners) {
    mRefineCorners = refineCorners;
}

void setMaxInputWidth(int maxWidth) {
    mFindQuads.setMaxInputWidth(maxWidth);
}

void setMinInputWidth(int minWidth) {
    mFindQuads.setMinInputWidth(minWidth);
}


std::map<int, Quad> find(const cv::Mat &inputImage){
    auto greyscaleImage = mEnsureGreyscale(inputImage);

    std::map<int, Quad> tags;

    if (mRefineCorners) {
        for (const auto & quad : mFindQuads(greyscaleImage)) {
            auto refinedQuad = mRefine(greyscaleImage, quad);
            auto tag = mDecode(mReadBits(greyscaleImage, refinedQuad), refinedQuad);
            if (tag.first != Decode::INVALID_TAG) tags[tag.first] = tag.second;
            else {
                tag = mDecode(mReadBits(greyscaleImage, quad), quad);
                if (tag.first != Decode::INVALID_TAG) tags[tag.first] = tag.second;
            }
        }
    }
    else {
        for (const auto & quad : mFindQuads(greyscaleImage)) {
            auto tag = mDecode(mReadBits(greyscaleImage, quad), quad);
            if (tag.first != Decode::INVALID_TAG) tags[tag.first] = tag.second;
        }
    }
    return mFilter(tags);
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

EnsureGreyscale mEnsureGreyscale;
FindQuads mFindQuads;

Refine mRefine;
ReadBits mReadBits;
Decode mDecode;

Filter<int, Quad> mFilter;

bool mRefineCorners;

};

Chilitags::Chilitags() :
    mImpl(new Impl())
{
}

void Chilitags::setFilter(int persistence, double gain) {
    mImpl->setFilter(persistence, gain);
}

void Chilitags::tunePerformance(PerformancePreset preset) {
    mImpl->tunePerformance(preset);
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

std::map<int, Quad> Chilitags::find(
    const cv::Mat &inputImage) {
    return mImpl->find(inputImage);
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
