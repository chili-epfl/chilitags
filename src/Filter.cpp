/*******************************************************************************
*   Copyright 2013-2014 EPFL                                                   *
*   Copyright 2013-2014 Quentin Bonnard                                        *
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

#include "Filter.hpp"

#include <opencv2/core/core.hpp>

namespace chilitags {

FindOutdated::FindOutdated(int persistence) :
    mPersistence(persistence),
    mDisappearanceTime()
{
}

std::vector<int> FindOutdated::operator()(const std::map<int, Quad> &tags){

    std::vector<int> tagsToForget;

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

Filter::Filter(int persistence, float gain) :
    mFindOutdated(persistence),
    mGain(gain),
    mFilteredCoordinates()
{
}

const std::map<int, Quad> & Filter::operator()(
    const std::map<int, Quad> &tags) {

    for(const auto &tagToForget : mFindOutdated(tags)) {
        //TODO lookup can be avoided if Ids are sorted
        mFilteredCoordinates.erase(tagToForget);
    }

    const float gainComplement = 1.0f - mGain;

    auto filteredIt = mFilteredCoordinates.begin();
    for (const auto &tag : tags) {
        while (filteredIt != mFilteredCoordinates.end()
               && filteredIt->first < tag.first) {
            ++filteredIt;
        }

        if (filteredIt != mFilteredCoordinates.end()
            && filteredIt->first == tag.first) {
            cv::addWeighted(filteredIt->second, mGain,
                            tag.second, gainComplement,
                            0.0f, filteredIt->second);
        }
        else {
            filteredIt = mFilteredCoordinates.insert(filteredIt, tag);
        }
    }

    return mFilteredCoordinates;
}

}
