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

#ifndef CachingFilter_HPP
#define CachingFilter_HPP

#include <map>
#include <vector>
#include <opencv2/core/core.hpp>

namespace chilitags{

class CachingFilter {
public:
	CachingFilter(int pPersistence = 5);
	const std::map<int, std::vector<cv::Point2f>> &operator()(const std::map<int, std::vector<cv::Point2f>> &pRawTags);

protected:
	int mPersistence;
	std::map<int, std::vector<cv::Point2f>> mCachedTags;
	std::map<int, int> mCacheAge;

};

}

#endif
