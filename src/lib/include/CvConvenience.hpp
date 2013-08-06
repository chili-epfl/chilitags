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

#include <opencv2/core/core.hpp>

// This namespace provides some conveninent operators and functions for
// Point2f. It also provides matchImageFormats(), which checks whether two
// images have an expected format, and adapt it if necessary.

namespace CvConvenience {

inline float square(float value){
	return value*value;
}

inline float squaredNorm(cv::Point2f p) {
	return square(p.x)+square(p.y);
}
inline float squaredDist(cv::Point2f a, cv::Point2f b){
	return squaredNorm(b-a);
}

inline float norm(cv::Point2f p) {
	return std::sqrt(squaredNorm(p));
}
inline float dist(cv::Point2f a, cv::Point2f b) {
	return norm(a-b);
}

inline float cross(cv::Point2f a, cv::Point2f b){
	return a.x*b.y - a.y*b.x;
}

}

#endif
