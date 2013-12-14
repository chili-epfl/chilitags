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

#include <CachingFilter.hpp>

chilitags::CachingFilter::CachingFilter(int pPersistence):
mPersistence(pPersistence),
mCachedTags(),
mCacheAge()
{
}

const std::map<int, std::vector<cv::Point2f>> &chilitags::CachingFilter::operator()(const std::map<int, std::vector<cv::Point2f>> &pRawTags) {
	auto tRawTagIt = pRawTags.cbegin();
	auto tCachedTagIt = mCachedTags.begin();
	auto tCacheAgeIt = mCacheAge.begin();
	while (tRawTagIt != pRawTags.end()) {
		while (tCachedTagIt != mCachedTags.end()
		    && tCachedTagIt->first < tRawTagIt->first) {
			if (tCacheAgeIt->second > mPersistence) {
				mCacheAge.erase(tCacheAgeIt);
				mCachedTags.erase(tCachedTagIt);
			} else {
				++tCacheAgeIt->second;
			}
			++tCacheAgeIt;
			++tCachedTagIt;
		}
		if (tCachedTagIt != mCachedTags.end()
		 && tCachedTagIt->first == tRawTagIt->first) {
			tCacheAgeIt->second = 0;
			tCachedTagIt->second = tRawTagIt->second;
		} else {
			mCacheAge.insert(tCacheAgeIt,
				std::make_pair(tRawTagIt->first, 0));
			mCachedTags.insert(tCachedTagIt, *tRawTagIt);
		}
		++tRawTagIt;
		++tCacheAgeIt;
		++tCachedTagIt;
	}
	while (tCachedTagIt != mCachedTags.end()) {
		if (tCacheAgeIt->second > mPersistence) {
			mCacheAge.erase(tCacheAgeIt);
			mCachedTags.erase(tCachedTagIt);
		} else {
			++tCacheAgeIt->second;
		}
		++tCacheAgeIt;
		++tCachedTagIt;
	}

	return mCachedTags;
}
