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

#include <chilitags.hpp>

#include "EnsureGreyscale.hpp"
#include "FindQuads.hpp"

#include "ReadBits.hpp"
#include "Decode.hpp"
#include "Refine.hpp"

#include "Filters.hpp"

#include <opencv2/imgproc/imgproc.hpp>

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

    mFindOutdated(5),
    //mFilter(mFindOutdated, 5),
    mFilter(mFindOutdated)
{
}

void setPersistence(int persistence) {
    mFindOutdated.setPersistence(persistence);
}

std::map<int, std::vector<cv::Point2f> > find(const cv::Mat &inputImage){
    auto greyscaleImage = mEnsureGreyscale(inputImage);

    std::map<int, std::vector<cv::Point2f> > tags;

    for (const auto & quad : mFindQuads(greyscaleImage)) {
        auto refinedQuad = mRefine(greyscaleImage, quad);
        auto &tag = mDecode(mReadBits(greyscaleImage, refinedQuad), refinedQuad);
        if (tag.first != Decode::INVALID_TAG) tags.insert(tag);
    }
    return mFilter(tags);
};

std::vector<bool> encode(int id) const {
    unsigned char data[36];
    mDecode.getCodec().getTagEncodedId(id, data);
    std::vector<bool> bits(36);
    for (int i = 0; i<36; ++i) {
        bits[i] = data[i];
    }
    return bits;
}

int decode(const std::vector<bool> &bits) const {
    unsigned char data[36];
    for (int i = 0; i<36; ++i) {
        data[i] = bits[i] ? 1 : 0;
    }
    int id = -1;
    mDecode.getCodec().decode(data, id);
    return id;
}

cv::Mat draw(int id, int zoom, bool withMargin) const {
    // Creating the image of the bit matrix
    static const int DATA_SIZE = 6;
    cv::Size dataDim(DATA_SIZE,DATA_SIZE);
    unsigned char dataMatrix[DATA_SIZE*DATA_SIZE];
    mDecode.getCodec().getTagEncodedId(id, dataMatrix);
    cv::Mat dataImage(dataDim, CV_8U, dataMatrix);
    dataImage *= 255;

    // Adding the black border arounf the bit matrix
    cv::Size borderSize(2,2);
    cv::Mat tagImage(dataImage.size()+borderSize*2, CV_8U, cv::Scalar(0));
    dataImage.copyTo(tagImage(cv::Rect(borderSize, dataImage.size())));

    // Adding the optionnal white margin
    cv::Size marginSize(0,0);
    if (withMargin) marginSize += borderSize;
    cv::Mat outlinedImage(tagImage.size()+marginSize*2, CV_8U, cv::Scalar(255));
    tagImage.copyTo(outlinedImage(cv::Rect(marginSize, tagImage.size())));

    // Resizing to specified zoom
    cv::Mat outputImage(outlinedImage.size()*zoom, CV_8U);
    cv::resize(outlinedImage, outputImage, outputImage.size(), 0, 0, cv::INTER_NEAREST);
    return outputImage;
}

protected:

EnsureGreyscale mEnsureGreyscale;
FindQuads mFindQuads;

Refine mRefine;
ReadBits mReadBits;
Decode mDecode;

FindOutdated<int> mFindOutdated;
//SimpleFilter<int, std::vector<cv::Point2f>> mFilter;
KalmanFilter<int, 2> mFilter;

};


Chilitags::Chilitags() :
    mImpl(new Impl())
{
}

void Chilitags::setPersistence(int persistence) {
    mImpl->setPersistence(persistence);
}

std::map<int, std::vector<cv::Point2f> > Chilitags::find(
    const cv::Mat &inputImage) {
    return mImpl->find(inputImage);
}

std::vector<bool> Chilitags::encode(int id) const {
    return mImpl->encode(id);
}

int Chilitags::decode(const std::vector<bool> & bits) const {
    return mImpl->decode(bits);
}

cv::Mat Chilitags::draw(int id, int zoom, bool withMargin) const {
    return mImpl->draw(id, zoom, withMargin);
}

Chilitags::~Chilitags() = default;

}
