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

#include "DetectEdges.hpp"
#include <CvConvenience.hpp>

chilitags::DetectEdges::DetectEdges(
        const int pLowThreshold,
        const int pHighThreshold,
        const int pApertureSize,
        const cv::Mat *pInputImage
        ) :
	mLowThreshold(pLowThreshold),
	mHighThreshold(pHighThreshold),
	mApertureSize(pApertureSize),
	mInputImage(pInputImage),
	mOutputImage(cvCreateImage(cvSize(1,1), IPL_DEPTH_8U,1))
{
}

chilitags::DetectEdges::~DetectEdges()
{
	cvReleaseImage(&mOutputImage);
}

void chilitags::DetectEdges::run()
{
	const cv::Mat tInputImage = *mInputImage;
	CvConvenience::matchImageFormats(tInputImage, &mOutputImage, true);
	cvCanny(tInputImage,mOutputImage,mLowThreshold,mHighThreshold,mApertureSize);
}
