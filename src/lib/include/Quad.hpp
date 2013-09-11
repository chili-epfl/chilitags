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

#include <vector>

namespace chilitags {

// A representation of a quadrilateral, with a minimum set of geometrical
// functionalities (center, scale, and orientation).
struct Quad {

	std::vector<cv::Point2f> points;

	Quad() {
	    points = std::vector<cv::Point2f>(4);
	}

	Quad(const cv::Point2f pCorners[4]) {
	    points = std::vector<cv::Point2f>(4);
		for (size_t i=0; i<4;i++) points[i] = pCorners[i];
	}

	int size() const {
		return points.size();
	}

	double perimeter() const {
		double length = 0.0;
		for (int i = 0; i < size() - 1; i++)
		{
			length += cv::norm(points[i]-points[i+1]);
		}
		return length;
	}


	cv::Point2f &operator [](size_t pIndex) {
		return points[pIndex];
	}

	const cv::Point2f &operator [] (size_t pIndex) const {
		return points[pIndex];
	}

	// Returns the intersection of the diagonals.
	cv::Point2f getCenter() const {

		cv::Point2f d1 = points[2] - points[0];
		cv::Point2f d2 = points[3] - points[1];
		cv::Point2f d3 = points[0] - points[1];

		float ratio = d1.cross(d2);

		static const float eps = 1e-8f;
		if (std::abs(ratio) > eps) {
		return points[0] + (d2.cross(d3) / ratio) * d1;
		}

		return points[0];
	}

	// Returns the area of the quadrilateral
	float getScale() const {
		cv::Point2f d1 = points[2] - points[0];
		cv::Point2f d2 = points[3] - points[1];
		return 0.5f*d1.cross(d2);
	}

	// Returns the orientation in gradian of the top-left to top-right vector
	float getAngle() const {
		cv::Point2f tTopLine = points[1]-points[0];
		return std::atan2(tTopLine.y, tTopLine.x);
	}

};

}

#endif
