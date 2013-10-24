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

#ifndef TagDrawer_HPP
#define TagDrawer_HPP

#include <Codec.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace chilitags {

class TagDrawer {

public:

	TagDrawer():
	mCodec()
	{
	}

	cv::Mat operator()(int pTagId, int pZoom = 1, bool pWithMargin = false) {
		// Creating the image of the bit matrix
		static const int DATA_SIZE = 6;
		cv::Size tDataDim(DATA_SIZE,DATA_SIZE);
		unsigned char tDataMatrix[DATA_SIZE*DATA_SIZE];
		mCodec.getTagEncodedId(pTagId, tDataMatrix);
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

private:
	Codec mCodec;
};

}

#endif
