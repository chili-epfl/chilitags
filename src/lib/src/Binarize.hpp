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

#ifndef Binarize_HPP
#define Binarize_HPP

#include "Pipeable.hpp"
#include <opencv2/opencv.hpp>

namespace chilitags {

// This class is an implementation of:
// BRADLEY, Derek et ROTH, Gerhard. Adaptive thresholding using the integral
// image. journal of graphics, gpu, and game tools, 2007, vol. 12, no 2,
// p. 13-21.
class Binarize : public Pipeable {
public:
Binarize(
        float pThreshold,
        float pWindowSizePerc,
        const cv::Mat *pInputImage);

virtual ~Binarize();

const cv::Mat *GetOutputImage() const {
	return &mOutputImage;
};

protected:
void run();

float mThreshold;
float mWindowSizePerc;
const cv::Mat *mInputImage;
int mInputWidth;
int mInputHeight;
cv::Mat mIntegralImage;
cv::Mat mOutputImage;

private:
Binarize(const Binarize&);
Binarize &operator=(const Binarize&);
};


}

#endif
