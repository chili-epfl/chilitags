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

template<typename Id>
class PersistenceManager {

public:

PersistenceManager(int persistence) :
    mPersistence(persistence),
    mDisappearanceTime()
{
}

void setPersistence(int persistence) {
    mPersistence = persistence;
}

template <typename Coordinates>
std::vector<Id> operator()(const std::map<Id, Coordinates > &tags){

    std::vector<Id> tagsToForget;

    auto tagIt = tags.cbegin();
    auto ageIt = mDisappearanceTime.begin();

    // for each tags that are detected in the current frame
    while (tagIt != tags.end()) {

        // update all the tags that come before the current tag,
        // i.e. that haven't bee detected this time
        while (ageIt != mDisappearanceTime.end()
               && ageIt->first < tagIt->first) {

            if (ageIt->second >= mPersistence) {
                // remove the tags that haven't been seen for too long
                tagsToForget.push_back(ageIt->first);
                ageIt = mDisappearanceTime.erase(ageIt);
            } else {
                // mark as older the last update of the others
                ++(ageIt->second);
                ++ageIt;
            }
        }

        ageIt = mDisappearanceTime.insert(ageIt, std::make_pair(tagIt->first, 0));

        ++tagIt;
        ++ageIt;
    }

    // update the remaining tags that have not been detected in this frame either
    while (ageIt != mDisappearanceTime.end()) {

        if (ageIt->second >= mPersistence) {
            // remove the tags that haven't been seen for too long
            tagsToForget.push_back(ageIt->first);
            ageIt  = mDisappearanceTime.erase(ageIt);
        } else {
            // mark as older the last update of the others
            ++ageIt->second;
            ++ageIt;
        }
    }


    return tagsToForget;
}

protected:

int mPersistence;
std::map<Id, int> mDisappearanceTime;

};

template<typename Id, typename Coordinates>
class Cache {
public:
    Cache(PersistenceManager<Id> &persistenceManager):
    mPersistenceManager(persistenceManager),
    mCachedCoordinates()
    {}

    void setPersistence(int persistence) {
        mPersistenceManager.setPersistence(persistence);
    }

    const std::map<Id, Coordinates> & operator()(
        const std::map<Id, Coordinates > &tags) {

        for(const auto &tagToForget : mPersistenceManager(tags)) {
            //TODO lookup can be avoided if Ids are sorted
            mCachedCoordinates.erase(tagToForget);
        }

        for (const auto &tag : tags) {
            //TODO lookup can be avoided by iterating the maps simultaneously
            mCachedCoordinates[tag.first] = tag.second;
        }

        return mCachedCoordinates;
    }

protected:
    PersistenceManager<Id> &mPersistenceManager;
    std::map<Id, Coordinates> mCachedCoordinates;
};


}

#endif
