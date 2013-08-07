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

//#define DEBUG_ReadBits
#ifdef DEBUG_ReadBits
#include <opencv2/highgui/highgui.hpp>
#endif

namespace {
static const int scDataSize = 6;
static const int scTagWarpZoom = 16;
}

chilitags::ReadBits::ReadBits(const cv::Mat *pInputImage) :
	mBinarize(0.95f, 0.5f, pInputImage),
	mMatrix(new unsigned char[scDataSize*scDataSize])
{
#ifdef DEBUG_ReadBits
	cvNamedWindow("ReadBits");
#endif
}

chilitags::ReadBits::~ReadBits()
{
	delete[] mMatrix;
}


void chilitags::ReadBits::run()
{
	mBinarize.start();
	const cv::Mat tBinarizedImage = *mBinarize.GetOutputImage();
	int tWidthStep = tBinarizedImage.cols;

#ifdef DEBUG_ReadBits
	cvShowImage("ReadBits", tBinarizedImage);
	cvWaitKey(0);
#endif

	for (int i = 0; i < scDataSize; ++i)
	{
		for (int j = 0; j < scDataSize; ++j)
		{
			int tVotesForWhite = 0;
			for(int y=0; y<scTagWarpZoom; ++y)
			{
				for(int x=0; x<scTagWarpZoom; ++x)
				{
					int tPosition = (scTagWarpZoom*i+y)*tWidthStep + j*scTagWarpZoom+x;
					tVotesForWhite += tBinarizedImage.at<char>(tPosition)/255;
				}
			}
			mMatrix[i*scDataSize + j] = (tVotesForWhite > scTagWarpZoom*scTagWarpZoom/2);
		}
	}
}
