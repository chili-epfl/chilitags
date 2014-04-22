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

#include "GrowRoi.hpp"
#include <opencv2/imgproc/imgproc.hpp>

cv::Rect chilitags::growRoi(const cv::Mat &inputImage, cv::InputArray points, float growthRatio)
{
    // Taking a ROI around the raw corners with some margin
    cv::Rect roi = cv::boundingRect(points);
    int xGrowth = (int)(growthRatio*roi.width);
    int yGrowth = (int)(growthRatio*roi.height);
    roi.x -= xGrowth;
    roi.y -= yGrowth;
    roi.width += 2*xGrowth;
    roi.height += 2*yGrowth;

    // Making sure the ROI is still in the image
    int previousRoiX = roi.x;
    int previousRoiY = roi.y;
    roi.x = std::max(roi.x, 0);
    roi.y = std::max(roi.y, 0);
    roi.width -= roi.x - previousRoiX;
    roi.height -= roi.y - previousRoiY;
    roi.width = cv::min(roi.x+roi.width, inputImage.cols)-roi.x;
    roi.height = cv::min(roi.y+roi.height, inputImage.rows)-roi.y;

    return roi;
}
