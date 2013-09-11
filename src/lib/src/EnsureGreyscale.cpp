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

#include "EnsureGreyscale.hpp"
#include <opencv2/imgproc/imgproc.hpp>

chilitags::EnsureGreyscale::EnsureGreyscale(
        const cv::Mat *pInputImage) :
	mInputImage(pInputImage),
	mOutputImage()
{
}

chilitags::EnsureGreyscale::~EnsureGreyscale()
{
}

void chilitags::EnsureGreyscale::run()
{
	const cv::Mat tInputImage = *mInputImage;
	if (tInputImage.channels() != 1) {
		// assuming BGR
		cv::cvtColor(tInputImage, mOutputImage, cv::COLOR_BGR2GRAY);
	} else {
		// Shallow copy should be OK, since we only give access to a const Mat
		mOutputImage = tInputImage;
	}
}
