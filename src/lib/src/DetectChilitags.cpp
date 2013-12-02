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

#include <DetectChilitags.hpp>

#include "EnsureGreyscale.hpp"
#include "FindQuads.hpp"
#include "ReadBits.hpp"
#include "Decode.hpp"
#include "Refine.hpp"

// The class that takes care of all the detection of Chilitags.
namespace chilitags {

class DetectChilitags::Impl
{

public:

Impl():
	mEnsureGreyscale(),
	mFindQuads(),

	mRefine(),
	mReadBits(),
	mDecode()
{
}


std::map<int, std::vector<cv::Point2f>> operator()(const cv::Mat &pInputImage){
	auto tGreyscaleImage = mEnsureGreyscale(pInputImage);

	std::map<int, std::vector<cv::Point2f>> tTags;

	for (const auto & tQuad : mFindQuads(tGreyscaleImage)) {
		auto tRefinedQuad = mRefine(tGreyscaleImage, tQuad);
		auto &tTag = mDecode(mReadBits(tGreyscaleImage, tRefinedQuad), tRefinedQuad);
		if (tTag.first != Decode::INVALID_TAG) tTags.insert(tTag);
	}

	return tTags;
};

protected:

EnsureGreyscale mEnsureGreyscale;
FindQuads mFindQuads;

ReadBits mReadBits;
Decode mDecode;
Refine mRefine;
};


DetectChilitags::DetectChilitags():
		mImpl(new Impl())
{}

std::map<int, std::vector<cv::Point2f>> DetectChilitags::operator()(const cv::Mat &pInputImage){
	return mImpl->operator()(pInputImage);
}

DetectChilitags::~DetectChilitags() = default;

}
