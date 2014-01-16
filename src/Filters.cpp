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

#include "Filters.hpp"

#include <opencv2/core/core.hpp>

#include <iostream>

namespace chilitags {

template<typename Id>
FindOutdated<Id>::FindOutdated(int persistence) :
    mPersistence(persistence),
    mDisappearanceTime()
{
}

template<typename Id>
void FindOutdated<Id>::setPersistence(int persistence) {
    mPersistence = persistence;
}

template <typename Id>
template <typename Coordinates>
std::vector<Id> FindOutdated<Id>::operator()(const std::map<Id, Coordinates > &tags){

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

template<typename Id, typename Coordinates>
SimpleFilter<Id, Coordinates>::SimpleFilter(
    FindOutdated<Id> &findOutdated,
    int span):
mFindOutdated(findOutdated),
mSpan(span),
mCoordinates()
{}

template<typename Id, typename Coordinates>
void SimpleFilter<Id, Coordinates>::setPersistence(int persistence) {
    mFindOutdated.setPersistence(persistence);
}

namespace {
    std::vector<cv::Point2f> average(std::deque<std::vector<cv::Point2f> >coordinates) {

        std::vector<cv::Point2f> result = {
            {0.f, 0.f},
            {0.f, 0.f},
            {0.f, 0.f},
            {0.f, 0.f},
        };

        for (const auto & component : coordinates) {
            result[0] += component[0];
            result[1] += component[1];
            result[2] += component[2];
            result[3] += component[3];
        }

        float ratio = 1.f/(float) coordinates.size(); 
        result[0] *= ratio;
        result[1] *= ratio;
        result[2] *= ratio;
        result[3] *= ratio;

        return result;
    }

    cv::Matx44d average(std::deque<cv::Matx44d> coordinates) {
        cv::Matx44d result;
        for (const auto & component : coordinates) {
            result += component;
        }
        float ratio = 1.f/(float) coordinates.size(); 
        result *= ratio;
        return result;
    }

}

template<typename Id, typename Coordinates>
std::map<Id, Coordinates> SimpleFilter<Id, Coordinates>::operator()(
    const std::map<Id, Coordinates > &tags) {

    for(const auto &tagToForget : mFindOutdated(tags)) {
        //TODO lookup can be avoided if Ids are sorted
        mCoordinates.erase(tagToForget);
    }

    std::map<Id, Coordinates> filteredTags;
    for (const auto &tag : tags) {
        //TODO lookup can be avoided by iterating the maps simultaneously
        auto & coordinates = mCoordinates[tag.first];
        if (coordinates.size() >= mSpan) coordinates.pop_front();
        mCoordinates[tag.first].push_back(tag.second);

        filteredTags[tag.first] = average(coordinates);
    }

    return filteredTags;
}


template<typename Id, int NORDERS>
KalmanFilter<Id, NORDERS>::KalmanFilter(FindOutdated<Id> &findOutdated):
mFindOutdated(findOutdated),
mFilters() {
}

namespace {
    template <typename Coordinates>
    struct Info {
    };

    template<> struct Info <std::vector<cv::Point2f> > {
        static const int rows = 4;
        static const int cols = 1;
        static const int channels = 2;
        static const int elements = rows*cols*channels;
    };

    template<> struct Info <cv::Matx44d> {
        static const int rows = 4;
        static const int cols = 4;
        static const int channels = 1;
        static const int elements = rows*cols*channels;
    };
}

template<typename Id, int NORDERS>
template<typename Coordinates>
std::map<Id, Coordinates> KalmanFilter<Id, NORDERS>::operator()(
        const std::map<Id, Coordinates > &tags){

    for(const auto &tagToForget : mFindOutdated(tags)) {
        //TODO lookup can be avoided if Ids are sorted
        mFilters.erase(tagToForget);
    }

    auto tagIt = tags.cbegin();
    auto filterIt = mFilters.begin();
    std::map<Id, Coordinates> filteredTags;

    while (tagIt != tags.end()) {
        while (filterIt != mFilters.end() && filterIt->first < tagIt->first) {
            std::cout << "update front" << std::endl;
            filteredTags[filterIt->first] =
                filterIt->second.predict()
                (cv::Rect(0,0,1,Info<Coordinates>::elements))
                .reshape(Info<Coordinates>::channels,
                         Info<Coordinates>::rows);
            ++filterIt;
        }

        if (filterIt != mFilters.end() && filterIt->first == tagIt->first) {
            std::cout << "update measurement" << std::endl;
            filterIt->second.predict();

            cv::Mat measurement;
            cv::Mat(tagIt->second)
                .reshape(1, Info<Coordinates>::elements)
                .convertTo(measurement, CV_32F);

            //TODO avoid lookup
            filteredTags[tagIt->first] = filterIt->second.correct(measurement)
                (cv::Rect(0,0,1,Info<Coordinates>::elements))
                .reshape(Info<Coordinates>::channels, Info<Coordinates>::rows);

        } else {
            std::cout << "new" << std::endl;

            filterIt = mFilters.insert(filterIt, std::make_pair(
                tagIt->first,
                cv::KalmanFilter(
                    Info<Coordinates>::elements*NORDERS,
                    Info<Coordinates>::elements,
                    0)));


            auto &filter = filterIt->second;
            filter.transitionMatrix = cv::Mat::zeros(
                Info<Coordinates>::elements*NORDERS,
                Info<Coordinates>::elements*NORDERS,
                CV_32F);
            for (int d = 0;
                 d < Info<Coordinates>::elements*NORDERS;
                 d += Info<Coordinates>::elements) {
                filter.transitionMatrix.diag(d) = 1.f;
            }

            cv::setIdentity(filter.measurementMatrix);
            //cv::setIdentity(filter.processNoiseCov, cv::Scalar::all(1e-5));
            //cv::setIdentity(filter.measurementNoiseCov, cv::Scalar::all(1e-1));
            //cv::setIdentity(filter.errorCovPost, cv::Scalar::all(1));

            // Initialize the filter with the current position
            // The rest (speeds) is already initialised to 0 by default.
            filter.statePost(cv::Rect(0,0,1,Info<Coordinates>::elements)) =
                cv::Mat(tagIt->second).reshape(1, Info<Coordinates>::elements);

            filter.predict();
            filteredTags[tagIt->first] = tagIt->second;
        }

        ++filterIt; //FIXME: iterator after inster
        ++tagIt;
    }

    while (filterIt != mFilters.end()) {
        std::cout << "update tail" << std::endl;
        filteredTags[filterIt->first] =
            filterIt->second.predict()
            (cv::Rect(0,0,1,Info<Coordinates>::elements))
            .reshape(Info<Coordinates>::channels,
                     Info<Coordinates>::rows);

        ++filterIt;
    }

    return filteredTags;
}


template class FindOutdated<int>;
template class SimpleFilter<int, std::vector<cv::Point2f>>;
template class KalmanFilter<int, 1>;
template
    std::map<int, std::vector<cv::Point2f>>
    KalmanFilter<int, 1>::operator()(
        const std::map<int, std::vector<cv::Point2f>> &tags);

template class FindOutdated<std::string>;
template class SimpleFilter<std::string, cv::Matx44d>;
template class KalmanFilter<std::string, 1>;
template
    std::map<std::string, cv::Matx44d>
    KalmanFilter<std::string, 1>::operator()(
        const std::map<std::string, cv::Matx44d> &tags);

}
