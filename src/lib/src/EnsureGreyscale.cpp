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
#include "CvConvenience.hpp"

chilitags::EnsureGreyscale::EnsureGreyscale(
        const IplImage *const *pInputImage) :
	mInputImage(pInputImage),
	mOutputImage(cvCreateImage(cvSize(1,1), IPL_DEPTH_8U, 1))
{
}

chilitags::EnsureGreyscale::~EnsureGreyscale()
{
	cvReleaseImage(&mOutputImage);
}

void chilitags::EnsureGreyscale::run()
{
	const IplImage *const tInputImage = *mInputImage;
	CvConvenience::matchImageFormats(tInputImage, &mOutputImage, true);
	if (tInputImage->nChannels != 1) {
		cvCvtColor(tInputImage, mOutputImage, CV_BGR2GRAY);
	} else {
		cvCopy(tInputImage, mOutputImage);
	}
}
