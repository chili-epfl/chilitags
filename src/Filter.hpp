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

/** This header contains various utilities to paliate with imperfect detection.
 */

#ifndef Filters_HPP
#define Filters_HPP

#include <map>
#include <vector>

#include <chilitags.hpp>

namespace chilitags {

template<typename Id>
class FindOutdated {

public:

FindOutdated(int persistence);

void setPersistence(int persistence) {
    mPersistence = persistence;
}

template <typename Coordinates>
std::vector<Id> operator()(const std::map<Id, Coordinates > &tags);

protected:

int mPersistence;
std::map<Id, int> mDisappearanceTime;

};



template<typename Id, typename Coordinates>
class Filter {
public:
    Filter(int persistence, float gain);

    void setPersistence(int persistence) {
        mFindOutdated.setPersistence(persistence);
    }

    void setGain(float gain) {
        mGain = gain;
    }

    const std::map<Id, Coordinates> & operator()(
        const std::map<Id, Coordinates > &tags) ;

protected:
    FindOutdated<Id> mFindOutdated;
    float mGain;
    std::map<Id, Coordinates> mFilteredCoordinates;
};


}

#endif
