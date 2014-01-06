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

#ifndef PersistenceManager_HPP
#define PersistenceManager_HPP

#include <map>
#include <vector>
#include <opencv2/core/core.hpp>

namespace chilitags {

template<typename Coordinates>
class Cache {
public:
    Cache(const Coordinates &coordinates):
    mCachedCoordinates(coordinates)
    {}

    Coordinates update(const Coordinates &coordinates) {
        return mCachedCoordinates = coordinates;
    }

    Coordinates update() {
        return mCachedCoordinates;
    }
protected:
    Coordinates mCachedCoordinates;
};


/** PersistenceManager aims at preventing that tags "flicker", i.e. that they
 * rapidly appear and disappear in the detection. To do so, PersistenceManager
 * takes as parameter of how long the tag should be artificially kept present,
 * and simply returns the last known position.
 */
template<typename Id, typename Coordinates, typename Filter = Cache<Coordinates> >
class PersistenceManager {

public:

/** \param persistence defines how many updates of the tag positions should
 * happen before an undetected tag actually disappear from the filtered output.
 */
PersistenceManager(int persistence) :
    mPersistence(persistence),
    mFilters()
{
}

void setPersistence(int persistence) {
    mPersistence = persistence;
}

std::map<Id, Coordinates> operator()(
    const std::map<Id, Coordinates > &rawTags){

    std::map<Id, Coordinates > filteredTags;

    auto rawTagIt = rawTags.cbegin();
    auto cacheIt = mFilters.begin();

    // for each tags that are detected in the current frame
    while (rawTagIt != rawTags.end()) {

        // update all the tags that come before the current tag,
        // i.e. that haven't bee detected this time
        while (cacheIt != mFilters.end()
               && id(cacheIt) < rawTagIt->first) {

            // remove the tags that haven't been seen for too long
            if (age(cacheIt) >= mPersistence) {
                cacheIt = mFilters.erase(cacheIt);
            // mark as older the last update of the others
            } else {
                ++age(cacheIt);
                filteredTags.insert(std::make_pair(id(cacheIt), filter(cacheIt).update()));
                ++cacheIt;
            }
        }

        // update the filter of the current tag with the new data
        if (cacheIt != mFilters.end()
            && id(cacheIt) == rawTagIt->first) {
            age(cacheIt) = 0;
            filteredTags.insert(std::make_pair(rawTagIt->first,
                                               filter(cacheIt).update(rawTagIt->second)));
        // or just create a new one if it is the first occurence
        } else {
            cacheIt = mFilters.insert(cacheIt,
                                    std::make_pair(rawTagIt->first,
                                                   std::make_pair(0, rawTagIt->second)));
            filteredTags.insert(*rawTagIt);
        }

        ++rawTagIt;
        ++cacheIt;
    }

    // update the remaining tags that haven been detected in this frame either
    while (cacheIt != mFilters.end()) {

        // remove the tags that haven't been seen for too long
        if (age(cacheIt) >= mPersistence) {
            cacheIt  = mFilters.erase(cacheIt);

        // mark as older the last update of the others
        } else {
            ++age(cacheIt);
            filteredTags.insert(std::make_pair(id(cacheIt),
                                               filter(cacheIt).update()));
            ++cacheIt;
        }
    }

    return filteredTags;
}

protected:

int mPersistence;

std::map<Id, std::pair<int, Filter> > mFilters;

// Helpers to access the elements of the datastructure above
typedef typename std::map<Id, std::pair<int, Filter> >::const_iterator
        FilterConstIterator;

typedef typename std::map<Id, std::pair<int, Filter> >::iterator
        FilterIterator;

static const Id & id(const FilterConstIterator & it) {
    return it->first;
}

static int & age(const FilterIterator & it) {
    return it->second.first;
}

static const int & age(const FilterConstIterator & it) {
    return it->second.first;
}

static Filter & filter(const FilterIterator & it) {
    return it->second.second;
}

static const Filter & filter(const FilterConstIterator & it) {
    return it->second.second;
}

};

}

#endif
