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

#include "FindQuads.hpp"

//#define DEBUG_FindQuads
#ifdef DEBUG_FindQuads
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <time.h>
#endif

namespace {
const int scMatrixSize = 10;
const int scMinTagSize = 2*scMatrixSize;

bool isTheSame(const chilitags::Quad &pQuad, float pP0X, float pP0Y, float pP1X, float pP1Y, float pP2X, float pP2Y, float pP3X, float pP3Y)
{
	static const int scEpsilon = chilitags::Quad::scNPoints*1;
	float tDistSum = pP0X+pP0Y+pP1X+pP1Y+pP2X+pP2Y+pP3X+pP3Y-pQuad[0].x-pQuad[0].y-pQuad[1].x-pQuad[1].y-pQuad[2].x-pQuad[2].y-pQuad[3].x-pQuad[3].y;
	return -scEpsilon < tDistSum && tDistSum < scEpsilon;
}
}

chilitags::FindQuads::FindQuads(
        const cv::Mat *pBinaryImage) :
	mBinaryImage(pBinaryImage),
	mQuadsCorners(new Quad[scMaxNumQuads]),
	mNumQuads(0)
{
#ifdef DEBUG_FindQuads
	cvNamedWindow("contours");
	cvNamedWindow("noise");
#endif
}

chilitags::FindQuads::~FindQuads()
{
	delete [] mQuadsCorners;
}

void chilitags::FindQuads::run()
{
	//TODO function too long, split it

	mNumQuads = 0;
	const cv::Mat tBinaryImage = *mBinaryImage;
#ifdef DEBUG_FindQuads
	cv::Mat tContourImage = cvCreateImage(cvSize(tBinaryImage->width,tBinaryImage->height),tBinaryImage->depth,3);
	cv::Mat tNoiseImage = cvCreateImage(cvSize(tBinaryImage->width,tBinaryImage->height),tBinaryImage->depth,3);
#endif

	mScaledCopies[0] = tBinaryImage;
	for (int i = 1; i < scScaledCopiesCount; ++i) {
		cv::pyrDown(mScaledCopies[i-1], mScaledCopies[i]);
	}

	for (int i = scScaledCopiesCount-1; i>=0; --i) //starting with the lowest definition, so the highest definition are last, and can simply override the first ones.
	{
		int tScale = 1 << i;
		std::vector<std::vector<cv::Point> > contours;
		std::vector<cv::Vec4i> hierarchy;
		cv::findContours(mScaledCopies[i], contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

		for (std::vector<std::vector<cv::Point> >::iterator contour = contours.begin();
			contour != contours.end();
			++contour)
		{
			double tPerimeter = std::abs(cv::arcLength(*contour, false)); //FIXME? not sure about false
			double tArea = std::abs(cv::contourArea(*contour));

			if (tPerimeter > Quad::scNPoints*scMinTagSize && tArea > scMinTagSize*scMinTagSize)
			{
				std::vector<cv::Point> approxContour;
				cv::approxPolyDP( *contour, approxContour, tPerimeter*0.02, false); //TODO not sure about false

				//TODO: get convex hull
				//http://stackoverflow.com/questions/10533233/opencv-c-obj-c-advanced-square-detection

				if (approxContour.size() >= (int) Quad::scNPoints
				    && cv::isContourConvex(approxContour))
				{
					//FIXME: take the right points, not simply the first 4
					cv::Point tPoint0 = approxContour[1];
					cv::Point tPoint1 = approxContour[0];
					cv::Point tPoint2 = approxContour[2];
					cv::Point tPoint3 = approxContour[3];
					float tP0X = (float)(tPoint0.x*tScale);
					float tP0Y = (float)(tPoint0.y*tScale);
					float tP1X = (float)(tPoint1.x*tScale);
					float tP1Y = (float)(tPoint1.y*tScale);
					float tP2X = (float)(tPoint2.x*tScale);
					float tP2Y = (float)(tPoint2.y*tScale);
					float tP3X = (float)(tPoint3.x*tScale);
					float tP3Y = (float)(tPoint3.y*tScale);
					unsigned int tQuadIndex = 0;
					while (tQuadIndex < mNumQuads && !isTheSame(mQuadsCorners[tQuadIndex], tP0X, tP0Y, tP1X, tP1Y, tP2X, tP2Y, tP3X, tP3Y)) ++tQuadIndex;
					if (tQuadIndex == mNumQuads) ++mNumQuads;

					mQuadsCorners[tQuadIndex][0].x   = tP0X;
					mQuadsCorners[tQuadIndex][0].y   = tP0Y;
					mQuadsCorners[tQuadIndex][1].x = tP1X;
					mQuadsCorners[tQuadIndex][1].y   = tP1Y;
					mQuadsCorners[tQuadIndex][3].x = tP2X;
					mQuadsCorners[tQuadIndex][3].y   = tP2Y;
					mQuadsCorners[tQuadIndex][2].x = tP3X;
					mQuadsCorners[tQuadIndex][2].y   = tP3Y;
#ifdef DEBUG_FindQuads
					if (tApproxContourSeq->total == scNCornersInQuads) cvDrawContours(tContourImage, tApproxContourSeq, cvScalar(0.0,255.0,0.0), cvScalar(0.0,255.0,0.0), 100);
					else cvDrawContours(tContourImage, tApproxContourSeq, cvScalar(0.0,255.0,255.0), cvScalar(0.0,255.0,255.0), 100);
				}
				else
				{
					cvDrawContours(tContourImage, tApproxContourSeq, cvScalar(0.0,0.0,255.0), cvScalar(0.0,0.0,255.0), 100);
				}
			}
			else
			{
				//if (tPerimeter >  scNCornersInQuads*scMinTagSize)
				{
					double tR = rand() % 255;
					double tG = rand() % 255;
					double tB = rand() % 255;
					cvDrawContours(tNoiseImage, tContourSeq, cvScalar(tB, tG, tR), cvScalar(tB, tG, tR), 100);
				}
			}
		}
	}
	cvShowImage("noise", tNoiseImage);
	cvShowImage("contours", tContourImage);
	cvReleaseImage(&tNoiseImage);
	cvReleaseImage(&tContourImage);
	cvWaitKey(5);
#else
				}
			}
		}
	}
#endif
}
