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

#include "Binarize.hpp"
#include <opencv2/imgproc/imgproc.hpp>

chilitags::Binarize::Binarize(
        float pThreshold,
        float pWindowSizePerc,
        const cv::Mat *pInputImage) :
	mThreshold(pThreshold),
	mWindowSizePerc(pWindowSizePerc),
	mInputImage(pInputImage),
	mIntegralImage(),
	mOutputImage()
{
}

chilitags::Binarize::~Binarize(){
}

void chilitags::Binarize::run(){
	const cv::Mat tInputImage= *mInputImage;
	int mInputWidth = tInputImage.cols;
	int mInputHeight = tInputImage.rows;
	int tHalfSection = int (std::min(mInputWidth,mInputHeight) * mWindowSizePerc /2.0f);

	cv::integral(tInputImage, mIntegralImage, CV_32S);
	mOutputImage.create(tInputImage.size(), tInputImage.type());

//TODO If you need to process a whole row of a 2d array, the most efficient way is to get the pointer to the row first, and then just use plain C operator [] :
// compute sum of positive matrix elements
// (assuming that M is double-precision matrix)
// double sum=0;
// for(int i = 0; i < M.rows; i++)
    //const double* Mi = M.ptr<double>(i);
	//for(int j = 0; j < M.cols; j++)
		//sum += std::max(Mi[j], 0.);
	//}

	for (int tY=0; tY<mInputHeight; ++tY)
	{
		int tY1=tY-tHalfSection;
		int tY2=tY+tHalfSection;
		tY1 = std::max(tY1, 0);
		tY2 = std::min(tY2, mInputHeight-1);
		int tX = 0;
		int tX1 = 0;
		int *tIy1x1 = mIntegralImage.ptr<int>(tY1);
		int *tIy2x1 = mIntegralImage.ptr<int>(tY2);
		int tX2 = tHalfSection;
		int *tIy1x2 = tIy1x1 + tHalfSection;
		int *tIy2x2 = tIy2x1 + tHalfSection;
		int tSectionHeight = tY2 - tY1;
		int tCount = tHalfSection*tSectionHeight;
		for (; tX2 < 2*tHalfSection; ++tX, ++tX2)
		{
			int tSum = *tIy2x2++ - *tIy1x2++ - *tIy2x1 + *tIy1x1;
			mOutputImage.at<uchar>(tY, tX) = (tInputImage.at<uchar>(tY, tX)*tCount < tSum*mThreshold) - 1;
			tCount += tSectionHeight;
		}
		for (; tX2 < mInputWidth; ++tX, ++tX1, ++tX2)
		{
			int tSum = *tIy2x2++ - *tIy1x2++ - *tIy2x1++ + *tIy1x1++;
			mOutputImage.at<uchar>(tY, tX) = (tInputImage.at<uchar>(tY, tX)*tCount < tSum*mThreshold) - 1;
		}
		--tX2;
		--tIy1x2;
		--tIy2x2;
		tCount -= tSectionHeight;
		for (; tX1 < mInputWidth-tHalfSection; ++tX, ++tX1)
		{
			int tSum = *tIy2x2 - *tIy1x2 - *tIy2x1++ + *tIy1x1++;
			mOutputImage.at<uchar>(tY, tX) = (tInputImage.at<uchar>(tY, tX)*tCount < tSum*mThreshold) - 1;
			tCount -= tSectionHeight;
		}
	}
}
