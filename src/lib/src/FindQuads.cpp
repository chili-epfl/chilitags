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

struct IsSimilarTo{
	IsSimilarTo(chilitags::Quad pQuad):mQuad(pQuad){}
	bool operator()(const chilitags::Quad &pQuad) {
		// TODO make it function of the dist
		static const int scEpsilon = chilitags::Quad::scNPoints*1;
		// TODO no seriously, do something
		float tDistSum = mQuad[0].x+mQuad[0].y+mQuad[1].x+mQuad[1].y+mQuad[2].x+mQuad[2].y+mQuad[3].x+mQuad[3].y-pQuad[0].x-pQuad[0].y-pQuad[1].x-pQuad[1].y-pQuad[2].x-pQuad[2].y-pQuad[3].x-pQuad[3].y;
		return -scEpsilon < tDistSum && tDistSum < scEpsilon;
	}

	private:
	chilitags::Quad mQuad;
};

}

chilitags::FindQuads::FindQuads(
        const cv::Mat *pBinaryImage) :
	mBinaryImage(pBinaryImage),
	mQuads()
{
}

chilitags::FindQuads::~FindQuads()
{
}

void chilitags::FindQuads::run()
{
	//TODO function too long, split it

	mQuads.clear();
	const cv::Mat tBinaryImage = *mBinaryImage;
#ifdef DEBUG_FindQuads
	cv::Mat tContourImage(tBinaryImage.size(), tBinaryImage->depth, 3);
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
					Quad tCandidate;
					tCandidate[0] = tScale*approxContour[0];
					tCandidate[1] = tScale*approxContour[1];
					tCandidate[2] = tScale*approxContour[2];
					tCandidate[3] = tScale*approxContour[3];

					IsSimilarTo tIsSimilarToCandidate(tCandidate);

					std::vector<Quad>::iterator tSameQuad = std::find_if(
						mQuads.begin(),
						mQuads.end(),
						tIsSimilarToCandidate);
					if (tSameQuad != mQuads.end()) *tSameQuad = tCandidate;
					else mQuads.push_back(tCandidate);

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
