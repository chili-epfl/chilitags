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

#ifndef DetectChilitags_HPP
#define DetectChilitags_HPP

#include <map>
#include <vector>
#include <opencv2/core/core.hpp>
#include <memory>

namespace chilitags {

/** The class that takes care of the detection of Chilitags. */
class DetectChilitags
{

public:

DetectChilitags();

/** This method needs to be called everytime the input image is updated. */
void operator()(const cv::Mat pInputImage);

/** The result of the detection is accessed here */
const std::map<int, std::vector<cv::Point2f>> &Tags() const;

~DetectChilitags();

private:
class Impl;
std::unique_ptr<Impl> mImpl;

};


}

#endif
