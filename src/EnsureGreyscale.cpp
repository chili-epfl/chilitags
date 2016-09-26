/*******************************************************************************
*   Copyright 2013-2014 EPFL                                                   *
*   Copyright 2013-2014 Quentin Bonnard                                        *
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
#include <opencv2/imgproc/imgproc.hpp>

namespace chilitags {

EnsureGreyscale::EnsureGreyscale() : mOutputImage(){
}

const cv::Mat &EnsureGreyscale::operator()(const cv::Mat &inputImage)
{
    if (inputImage.channels() != 1) {
        // assuming BGR
        cv::cvtColor(inputImage, mOutputImage, cv::COLOR_BGR2GRAY);
    } else {
        // Shallow copy
        mOutputImage = inputImage;
    }
    return mOutputImage;
}

} /* namespace chilitags */
