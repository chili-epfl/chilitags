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
#include <opencv2/imgproc/imgproc.hpp>

//#define DEBUG_FindQuads
#ifdef DEBUG_FindQuads
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core_c.h> // CV_AA
#endif

namespace {
const int scMatrixSize = 10;
const int scMinTagSize = 1.2*scMatrixSize;

struct IsSimilarTo{
	IsSimilarTo(chilitags::Quad pQuad):mQuad(pQuad){}
	bool operator()(const chilitags::Quad &pQuad) {
		// TODO make it function of the perimeter
		static const int scEpsilon = chilitags::Quad::scNPoints*1;
		// TODO no seriously, do something
		float tDistSum = mQuad[0].x+mQuad[0].y+mQuad[1].x+mQuad[1].y+mQuad[2].x+mQuad[2].y+mQuad[3].x+mQuad[3].y-pQuad[0].x-pQuad[0].y-pQuad[1].x-pQuad[1].y-pQuad[2].x-pQuad[2].y-pQuad[3].x-pQuad[3].y;
		return -scEpsilon < tDistSum && tDistSum < scEpsilon;
	}

	private:
	chilitags::Quad mQuad;
};

#ifdef DEBUG_FindQuads
void drawContour(cv::Mat &pImage, std::vector<cv::Point> &pContour, cv::Scalar pColor, cv::Point pOffset) {
	std::vector<std::vector<cv::Point> >tContours;
	tContours.push_back(pContour);
	cv::drawContours(pImage, tContours, 0, pColor, 1, CV_AA, cv::noArray(), INT_MAX, pOffset);
	double tPerimeter = std::abs(cv::arcLength(pContour, true));
	cv::putText(pImage, cv::format("%.1f", tPerimeter), pOffset+pContour[0],
		cv::FONT_HERSHEY_SIMPLEX, 1.0, pColor);
}
#endif

}

chilitags::FindQuads::FindQuads(
        const cv::Mat *pBinaryImage) :
	mBinaryImage(pBinaryImage),
	mQuads()
{
#ifdef DEBUG_FindQuads
	cv::namedWindow("FindQuads");
#endif
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
	cv::RNG tRNG( 0xFFFFFFFF );
	cv::Mat tDebugImage = cv::Mat::zeros(cv::Size(2*tBinaryImage.cols, tBinaryImage.rows), CV_8UC3);
#endif

	mScaledCopies[0] = tBinaryImage;
	for (int i = 1; i < scScaledCopiesCount; ++i) {
		cv::pyrDown(mScaledCopies[i-1], mScaledCopies[i]);
	}

	for (int i = scScaledCopiesCount-1; i>=0; --i) //starting with the lowest definition, so the highest definition are last, and can simply override the first ones.
	{
		int tScale = 1 << i;
#ifdef DEBUG_FindQuads
		cv::Point tOffset(tDebugImage.cols-2*mScaledCopies[i].cols,0);
		cv::Size tScaledSize = mScaledCopies[i].size();
#endif
		std::vector<std::vector<cv::Point> > contours;
		cv::findContours(mScaledCopies[i], contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

		for (std::vector<std::vector<cv::Point> >::iterator contour = contours.begin();
			contour != contours.end();
			++contour)
		{
			double tPerimeter = std::abs(cv::arcLength(*contour, true));
			double tArea = std::abs(cv::contourArea(*contour));

			if (tPerimeter > Quad::scNPoints*scMinTagSize && tArea > scMinTagSize*scMinTagSize)
			{
				std::vector<cv::Point> tApproxContour;
				cv::approxPolyDP( *contour, tApproxContour, tPerimeter*0.02, true);

				std::vector<cv::Point> tNormalisedContour;
				cv::convexHull(tApproxContour, tNormalisedContour, false);

				if (tNormalisedContour.size() == (int) Quad::scNPoints)
				{
					Quad tCandidate;
					tCandidate[0] = tScale*tNormalisedContour[0];
					tCandidate[1] = tScale*tNormalisedContour[1];
					tCandidate[2] = tScale*tNormalisedContour[2];
					tCandidate[3] = tScale*tNormalisedContour[3];

					IsSimilarTo tIsSimilarToCandidate(tCandidate);

					std::vector<Quad>::iterator tSameQuad = std::find_if(
						mQuads.begin(),
						mQuads.end(),
						tIsSimilarToCandidate);
					if (false && tSameQuad != mQuads.end()) // TODO move to Decode
					{
						*tSameQuad = tCandidate;
#ifdef DEBUG_FindQuads
						drawContour(tDebugImage, tNormalisedContour, cv::Scalar(0,255,255), tOffset);
#endif
					}
					else
					{
						mQuads.push_back(tCandidate);
#ifdef DEBUG_FindQuads
						drawContour(tDebugImage, tNormalisedContour, cv::Scalar(0,255,0), tOffset);
#endif
					}
				}
#ifdef DEBUG_FindQuads
				else // not quadrilaterals
				{
					drawContour(tDebugImage, tNormalisedContour, cv::Scalar(0,0,255), tOffset);
				}
#endif
			}
#ifdef DEBUG_FindQuads
			else // too small
			{
				drawContour(tDebugImage, *contour, cv::Scalar(128,128,128), tOffset);
			}
#endif
		}
#ifdef DEBUG_FindQuads
		cv::putText(tDebugImage, cv::format("%d", contours.size()), tOffset+cv::Point(32,32),
			cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar::all(255));
#endif
	}
#ifdef DEBUG_FindQuads
	cv::imshow("FindQuads", tDebugImage);
	cv::waitKey(0);
#endif
}
