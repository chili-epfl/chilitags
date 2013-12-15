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

/** This header contains various utilities to paliate with imperfect detection.
 */

#ifndef CachingFilter_HPP
#define CachingFilter_HPP

#include <map>
#include <vector>
#include <opencv2/core/core.hpp>

namespace chilitags{

/** CachingFilter aims at preventing that tags "flicker", i.e. that they rapidly
 *  appear and disappear in the detection. To do so, CachingFilter takes as
 *  parameter of how long the tag should be artificially kept present, and
 *  simply returns the last known position.
 */
class CachingFilter {

public:

	/** \param pPersistence defines how many updates of the tag positions should
	 *  happen before an undetected tag actually disappear from the filtered
	 * output.
	 */
	CachingFilter(int pPersistence):
	mPersistence(pPersistence),
	mCachedTags(),
	mCacheAge()
	{
	}

	void setPersistence(int pPersistence) {
		mPersistence = pPersistence;
	}

	const std::map<int, std::vector<cv::Point2f>> &operator()(
		const std::map<int, std::vector<cv::Point2f>> &pRawTags){

		if (mPersistence <= 0) return pRawTags;

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

protected:
	int mPersistence;
	/** The filtered tag list
	*/
	std::map<int, std::vector<cv::Point2f>> mCachedTags;
	/** Keeps track of how many times a cached tag has been returned
	*/
	std::map<int, int> mCacheAge;

};

}

#endif
