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

#include "CachingFilter.hpp"
#include "EnsureGreyscale.hpp"
#include "FindQuads.hpp"
#include "ReadBits.hpp"
#include "Decode.hpp"
#include "Refine.hpp"

#include <opencv2/imgproc/imgproc.hpp>

// The class that takes care of all the detection of Chilitags.
namespace chilitags {

class Chilitags::Impl
{

public:

Impl():
	mCachingFilter(5),
	mEnsureGreyscale(),
	mFindQuads(),

	mRefine(),
	mReadBits(),
	mDecode()
{
}

void setPersistence(int pPersistence) {
	mCachingFilter.setPersistence(pPersistence);
}

std::map<int, std::vector<cv::Point2f>> find(const cv::Mat &pInputImage){
	auto tGreyscaleImage = mEnsureGreyscale(pInputImage);

	std::map<int, std::vector<cv::Point2f>> tTags;

	for (const auto & tQuad : mFindQuads(tGreyscaleImage)) {
		auto tRefinedQuad = mRefine(tGreyscaleImage, tQuad);
		auto &tTag = mDecode(mReadBits(tGreyscaleImage, tRefinedQuad), tRefinedQuad);
		if (tTag.first != Decode::INVALID_TAG) tTags.insert(tTag);
	}
	return mCachingFilter(tTags);
};

std::vector<bool> encode(int pId) const {
	unsigned char tData[36];
	mDecode.getCodec().getTagEncodedId(pId, tData);
	std::vector<bool> tBits(36);
	for (int i = 0; i<36; ++i) {
		tBits[i] = tData[i];
	}
	return tBits;
}

int decode(const std::vector<bool> &pBits) const {
	unsigned char tData[36];
	for (int i = 0; i<36; ++i) {
		tData[i] = pBits[i]?1:0;
	}
	int tId = -1;
	mDecode.getCodec().decode(tData, tId);
	return tId;
}

cv::Mat draw(int pId, int pZoom, bool pWithMargin) const {
	// Creating the image of the bit matrix
	static const int DATA_SIZE = 6;
	cv::Size tDataDim(DATA_SIZE,DATA_SIZE);
	unsigned char tDataMatrix[DATA_SIZE*DATA_SIZE];
	mDecode.getCodec().getTagEncodedId(pId, tDataMatrix);
	cv::Mat tDataImage(tDataDim, CV_8U, tDataMatrix);
	tDataImage *= 255;

	// Adding the black border arounf the bit matrix
	cv::Size tBorderSize(2,2);
	cv::Mat tTagImage(tDataImage.size()+tBorderSize*2, CV_8U, cv::Scalar(0));
	tDataImage.copyTo(tTagImage(cv::Rect(tBorderSize, tDataImage.size())));

	// Adding the optionnal white margin
	cv::Size tMarginSize(0,0);
	if (pWithMargin) tMarginSize += tBorderSize;
	cv::Mat tOutlinedImage(tTagImage.size()+tMarginSize*2, CV_8U, cv::Scalar(255));
	tTagImage.copyTo(tOutlinedImage(cv::Rect(tMarginSize, tTagImage.size())));

	// Resizing to specified zoom
	cv::Mat tOutputImage(tOutlinedImage.size()*pZoom, CV_8U);
	cv::resize(tOutlinedImage, tOutputImage, tOutputImage.size(), 0, 0, cv::INTER_NEAREST);
	return tOutputImage;
}

protected:

CachingFilter mCachingFilter;

EnsureGreyscale mEnsureGreyscale;
FindQuads mFindQuads;

Refine mRefine;
ReadBits mReadBits;
Decode mDecode;
};


Chilitags::Chilitags():
		mImpl(new Impl())
{}

void Chilitags::setPersistence(int pPersistence) {
	mImpl->setPersistence(pPersistence);
}

std::map<int, std::vector<cv::Point2f>> Chilitags::find(
	const cv::Mat &pInputImage) const{
	return mImpl->find(pInputImage);
}

std::vector<bool> Chilitags::encode(int pId) const {
	return mImpl->encode(pId);}

int Chilitags::decode(const std::vector<bool> & pBits) const {
	return mImpl->decode(pBits);
}

cv::Mat Chilitags::draw(int pId, int pZoom, bool pWithMargin) const {
	return mImpl->draw(pId, pZoom, pWithMargin);
}

Chilitags::~Chilitags() = default;

}
