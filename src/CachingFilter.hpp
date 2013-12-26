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

namespace chilitags {

/** CachingFilter aims at preventing that tags "flicker", i.e. that they rapidly
 *  appear and disappear in the detection. To do so, CachingFilter takes as
 *  parameter of how long the tag should be artificially kept present, and
 *  simply returns the last known position.
 */
class CachingFilter {

public:

/** \param persistence defines how many updates of the tag positions should
 *  happen before an undetected tag actually disappear from the filtered
 * output.
 */
CachingFilter(int persistence) :
    mPersistence(persistence),
    mCachedTags(),
    mCacheAge()
{
}

void setPersistence(int persistence) {
    mPersistence = persistence;
}

const std::map<int, std::vector<cv::Point2f> > &operator()(
    const std::map<int, std::vector<cv::Point2f> > &rawTags){

    if (mPersistence <= 0) return rawTags;

    auto rawTagIt = rawTags.cbegin();
    auto cachedTagIt = mCachedTags.begin();
    auto cacheAgeIt = mCacheAge.begin();
    while (rawTagIt != rawTags.end()) {
        while (cachedTagIt != mCachedTags.end()
               && cachedTagIt->first < rawTagIt->first) {
            if (cacheAgeIt->second > mPersistence) {
                mCacheAge.erase(cacheAgeIt);
                mCachedTags.erase(cachedTagIt);
            } else {
                ++cacheAgeIt->second;
            }
            ++cacheAgeIt;
            ++cachedTagIt;
        }
        if (cachedTagIt != mCachedTags.end()
            && cachedTagIt->first == rawTagIt->first) {
            cacheAgeIt->second = 0;
            cachedTagIt->second = rawTagIt->second;
        } else {
            mCacheAge.insert(cacheAgeIt,
                             std::make_pair(rawTagIt->first, 0));
            mCachedTags.insert(cachedTagIt, *rawTagIt);
        }
        ++rawTagIt;
        ++cacheAgeIt;
        ++cachedTagIt;
    }
    while (cachedTagIt != mCachedTags.end()) {
        if (cacheAgeIt->second > mPersistence) {
            mCacheAge.erase(cacheAgeIt);
            mCachedTags.erase(cachedTagIt);
        } else {
            ++cacheAgeIt->second;
        }
        ++cacheAgeIt;
        ++cachedTagIt;
    }

    return mCachedTags;
}

protected:
int mPersistence;
/** The filtered tag list
 */
std::map<int, std::vector<cv::Point2f> > mCachedTags;
/** Keeps track of how many times a cached tag has been returned
 */
std::map<int, int> mCacheAge;

};

}

#endif
