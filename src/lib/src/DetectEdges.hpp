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

#ifndef DetectEdges_HPP
#define DetectEdges_HPP

#include "Pipeable.hpp"
#include <opencv2/core/core.hpp>

namespace chilitags {

class DetectEdges : public Pipeable
{
public:

DetectEdges(
        const int pLowThreshold,
        const int pHighThreshold,
        const int pApertureSize,
        const cv::Mat *pInputImage);

virtual ~DetectEdges();

const cv::Mat *GetOutputImage() const {
	return &mOutputImage;
}

protected:

const int mLowThreshold;
const int mHighThreshold;
const int mApertureSize;
const cv::Mat *mInputImage;
cv::Mat mOutputImage;

void run();

private:
DetectEdges(const DetectEdges&);
DetectEdges &operator=(const DetectEdges&);
};


}

#endif
