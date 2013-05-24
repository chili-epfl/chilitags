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

#ifndef CvConvenience_HPP
#define CvConvenience_HPP

#include <opencv2/core/types_c.h>

// This namespace provides some conveninent operators and functions for
// CvPoint2D32f. It also provides matchImageFormats(), which checks whether two
// images have an expected format, and adapt it if necessary.

namespace CvConvenience {

inline CvPoint2D32f operator *(const float pA, const CvPoint2D32f pB)
{
	CvPoint2D32f tResult = pB;
	tResult.x *= pA;
	tResult.y *= pA;
	return tResult;
}

inline CvPoint2D32f operator -(const CvPoint2D32f pA, const CvPoint2D32f pB)
{
	CvPoint2D32f tResult = pA;
	tResult.x -= pB.x;
	tResult.y -= pB.y;
	return tResult;
}

inline CvPoint2D32f operator +(const CvPoint2D32f pA, const CvPoint2D32f pB)
{
	CvPoint2D32f tResult = pA;
	tResult.x += pB.x;
	tResult.y += pB.y;
	return tResult;
}

inline float square(float value){
	return value*value;
}

inline float squaredNorm(CvPoint2D32f p) {
	return square(p.x)+square(p.y);
}
inline float squaredDist(CvPoint2D32f a, CvPoint2D32f b){
	return squaredNorm(b-a);
}

inline float norm(CvPoint2D32f p) {
	return std::sqrt(squaredNorm(p));
}
inline float dist(CvPoint2D32f a, CvPoint2D32f b) {
	return norm(a-b);
}

inline float cross(CvPoint2D32f a, CvPoint2D32f b){
	return a.x*b.y - a.y*b.x;
}



inline bool matchImageFormats(int pWidth, int pHeight, IplImage **pDstImage)
{
	if (pWidth != (*pDstImage)->width
	    || pHeight != (*pDstImage)->height)
	{
		int tDepth = (*pDstImage)->depth;
		int tChannels = (*pDstImage)->nChannels;
		cvReleaseImage(pDstImage);
		*pDstImage = cvCreateImage(cvSize(pWidth, pHeight), tDepth, tChannels);
		return true;
	}
	return false;
}

inline bool matchImageFormats(int pWidth, int pHeight, int pDepth, int pNChannels, IplImage **pDstImage)
{
	if (pWidth != (*pDstImage)->width
	    || pHeight != (*pDstImage)->height
	    || pDepth != (*pDstImage)->depth
	    || pNChannels != (*pDstImage)->nChannels)
	{
		cvReleaseImage(pDstImage);
		*pDstImage = cvCreateImage(cvSize(pWidth, pHeight), pDepth, pNChannels);
		return true;
	}
	return false;
}

inline bool matchImageFormats(const IplImage *pSrcImage, IplImage **pDstImage, bool pSizeOnly = false)
{
	if (pSizeOnly)
	{
		return matchImageFormats(pSrcImage->width, pSrcImage->height, pDstImage);
	}
	return matchImageFormats(pSrcImage->width, pSrcImage->height, pSrcImage->depth, pSrcImage->nChannels, pDstImage);
}
}

#endif
