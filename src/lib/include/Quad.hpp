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

#ifndef Quad_HPP
#define Quad_HPP

#include <opencv2/core/core.hpp>

namespace chilitags {

// A representation of a quadrilateral, with a minimum set of geometrical
// functionalities (center, scale, and orientation).
struct Quad {

	static const size_t scNPoints = 4;
	cv::Point2f mCorners[scNPoints];

	Quad() { }

	Quad(const std::vector<cv::Point2f> &pCorners) {
		for (size_t i=0; i<Quad::scNPoints; ++i) mCorners[i] = pCorners[i];
	}

	Quad(const cv::Point2f pCorners[4]) {
		for (size_t i=0; i<Quad::scNPoints; ++i) mCorners[i] = pCorners[i];
	}


	cv::Point2f &operator [](size_t pIndex) {
		return mCorners[pIndex];
	}

	const cv::Point2f &operator [] (size_t pIndex) const {
		return mCorners[pIndex];
	}

	std::vector<cv::Point2f> toVector() const {
		std::vector<cv::Point2f> tResult(4);
		for (size_t i=0; i<Quad::scNPoints; ++i) tResult[i] = mCorners[i];
		return tResult;
	}

	// Returns the intersection of the diagonals.
	cv::Point2f getCenter() const {

		cv::Point2f d1 = mCorners[2] - mCorners[0];
		cv::Point2f d2 = mCorners[3] - mCorners[1];
		cv::Point2f d3 = mCorners[0] - mCorners[1];

		float ratio = d1.x * d2.y - d1.y * d2.x;

		static const float eps = 1e-8f;
		if (std::abs(ratio) > eps) {
		return mCorners[0] + ( (d2.x * d3.y - d2.y * d3.x) / ratio) * d1;
		}

		return mCorners[0];
	}

	// Returns the area of the quadrilateral
	float getScale() const {
		cv::Point2f d1 = mCorners[2] - mCorners[0];
		cv::Point2f d2 = mCorners[3] - mCorners[1];
		return 0.5f* (d1.x * d2.y - d1.y * d2.x);
	}

	// Returns the orientation in gradian of the top-left to top-right vector
	float getAngle() const {
		cv::Point2f tTopLine = mCorners[1]-mCorners[0];
		return std::atan2(tTopLine.y, tTopLine.x);
	}

};

}

#endif
