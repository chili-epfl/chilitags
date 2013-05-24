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
#include <CvConvenience.hpp>

//#define DEBUG_Binarize
#ifdef DEBUG_Binarize
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#endif

chilitags::Binarize::Binarize(
        float pThreshold,
        float pWindowSizePerc,
        const IplImage *const *pInputImage) :
	mThreshold(pThreshold),
	mWindowSizePerc(pWindowSizePerc),
	mInputImage(pInputImage),
	mInputWidth((*mInputImage)->width),
	mInputHeight((*mInputImage)->height),
	mIntegralImage(cvCreateImage(cvSize(mInputWidth+1, mInputHeight+1), IPL_DEPTH_32S, 1)),
	mOutputImage(cvCreateImage(cvGetSize(*mInputImage), IPL_DEPTH_8U, 1))
{
#ifdef DEBUG_Binarize
	cvNamedWindow("Binarize");
#endif
}

chilitags::Binarize::~Binarize(){
	cvReleaseImage(&mOutputImage);
	cvReleaseImage(&mIntegralImage);
}

void chilitags::Binarize::run(){
	const IplImage *const tInputImage= *mInputImage;
	if (CvConvenience::matchImageFormats(tInputImage, &mOutputImage, true))
	{
		mInputWidth = tInputImage->width;
		mInputHeight = tInputImage->height;

		CvConvenience::matchImageFormats(mInputWidth+1, mInputHeight+1, &mIntegralImage);
	}

	uchar *tInputImageData = (uchar *) tInputImage->imageData;
	int tInputWidthStep = tInputImage->widthStep;
	uchar *tImageLineStart = tInputImageData;

	int tHalfSection = int (std::min(mInputWidth,mInputHeight) * mWindowSizePerc /2.0f);

	cvIntegral(tInputImage, mIntegralImage);
	int *tIntegralImageData = (int *) mIntegralImage->imageData;
	int tIntegralWidthStep = mIntegralImage->widthStep/sizeof(int);

	uchar *tOutputImageData = (uchar *) mOutputImage->imageData;
	int tOutputWidthStep = mOutputImage->widthStep;
	uchar *tOutputLineStart = tOutputImageData;
	for (int tY=0; tY<mInputHeight; ++tY)
	{
		int tY1=tY-tHalfSection;
		int tY2=tY+tHalfSection;
		tY1 = CV_IMAX(tY1, 0);
		tY2 = CV_IMIN(tY2, mInputHeight-1);
		int tX1 = 0;
		int *tIy1x1 = tIntegralImageData + tY1*tIntegralWidthStep;
		int *tIy2x1 = tIntegralImageData + tY2*tIntegralWidthStep;
		int tX2 = tHalfSection;
		int *tIy1x2 = tIy1x1 + tHalfSection;
		int *tIy2x2 = tIy2x1 + tHalfSection;
		int tSectionHeight = tY2 - tY1;
		int tCount = tHalfSection*tSectionHeight;
		for (; tX2 < 2*tHalfSection; ++tX2)
		{
#ifdef DEBUG_Binarize
			std::cout << "A ";
			std::cout << tX1 << ","<< tY1 << ":" << tX2 << ","<< tY2 << " " << tOutputImageData-((uchar *) mOutputImage->imageData) << " " << tImagePointer-tInputImageData << " " << tCount << " " << tIy2x2-mIntegralImage << "-"<< tIy1x2-mIntegralImage << "-" << tIy2x1-mIntegralImage << "+" << tIy1x1-mIntegralImage << std::endl;
#endif
			int tSum = *tIy2x2++ - *tIy1x2++ - *tIy2x1 + *tIy1x1;
			*tOutputImageData++ = (*tInputImageData++ *tCount < tSum*mThreshold) - 1;
			tCount += tSectionHeight;
		}
		for (; tX2 < mInputWidth; ++tX1, ++tX2)
		{
#ifdef DEBUG_Binarize
			std::cout << "B ";
			std::cout << tX1 << ","<< tY1 << ":" << tX2 << ","<< tY2 << " " << tOutputImageData-((uchar *) mOutputImage->imageData) << " " << tImagePointer-tInputImageData << " " << tCount << " " << tIy2x2-mIntegralImage << "-"<< tIy1x2-mIntegralImage << "-" << tIy2x1-mIntegralImage << "+" << tIy1x1-mIntegralImage << std::endl;
#endif
			int tSum = *tIy2x2++ - *tIy1x2++ - *tIy2x1++ + *tIy1x1++;
			*tOutputImageData++ = (*tInputImageData++ *tCount < tSum*mThreshold) - 1;
		}
		--tX2;
		--tIy1x2;
		--tIy2x2;
		tCount -= tSectionHeight;
		for (; tX1 < mInputWidth-tHalfSection; ++tX1)
		{
#ifdef DEBUG_Binarize
			std::cout << "C ";
			std::cout << tX1 << ","<< tY1 << ":" << tX2 << ","<< tY2 << " " << tOutputImageData-((uchar *) mOutputImage->imageData) << " " << tImagePointer-tInputImageData << " " << tCount << " " << tIy2x2-mIntegralImage << "-"<< tIy1x2-mIntegralImage << "-" << tIy2x1-mIntegralImage << "+" << tIy1x1-mIntegralImage << std::endl;
#endif
			int tSum = *tIy2x2 - *tIy1x2 - *tIy2x1++ + *tIy1x1++;
			*tOutputImageData++ = (*tInputImageData++ *tCount < tSum*mThreshold) - 1;
			tCount -= tSectionHeight;
		}

		tOutputLineStart += tOutputWidthStep;
		tOutputImageData = tOutputLineStart;
		tImageLineStart += tInputWidthStep;
		tInputImageData = tImageLineStart;
	}
}
