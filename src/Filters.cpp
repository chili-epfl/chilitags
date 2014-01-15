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

template<typename Id, int NORDERS>
template<typename Coordinates>
std::map<Id, Coordinates> KalmanFilter<Id, NORDERS>::operator()(
        const std::map<Id, Coordinates > &tags){
std::cout << __LINE__ << std::endl;

    for(const auto &tagToForget : mFindOutdated(tags)) {
        //TODO lookup can be avoided if Ids are sorted
        mFilters.erase(tagToForget);
    }
std::cout << __LINE__ << std::endl;

    auto tagIt = tags.cbegin();
    auto filterIt = mFilters.begin();
    std::map<Id, Coordinates> filteredTags;
std::cout << __LINE__ << std::endl;

    while (tagIt != tags.end()) {
        while (filterIt != mFilters.end()
                && filterIt->first < tagIt->first) {
std::cout << __LINE__ << std::endl;

            auto & filter = filterIt->second;

            filter.statePre = filter.transitionMatrix*filter.statePost;
std::cout << __LINE__ << std::endl;

            filter.temp1 = filter.transitionMatrix*filter.errorCovPost;
std::cout << __LINE__ << std::endl;

            gemm(filter.temp1, filter.transitionMatrix, 1, filter.processNoiseCov, 1, filter.errorCovPre, cv::GEMM_2_T);
std::cout << __LINE__ << std::endl;

            filter.statePre.copyTo(filter.statePost);
std::cout << __LINE__ << std::endl;
            filter.errorCovPre.copyTo(filter.errorCovPost);
std::cout << __LINE__ << std::endl;

            filteredTags[filterIt->first] = filter.statePre(cv::Rect(0,0,1,filter.measurementMatrix.cols));
std::cout << __LINE__ << std::endl;

            //filteredTags[filterIt->first] = filterIt->second.predict().col(0);
std::cout << __LINE__ << std::endl;
            ++filterIt;
        }

std::cout << __LINE__ << std::endl;
        if (filterIt != mFilters.end() && filterIt->first == tagIt->first) {

            auto &filter = filterIt->second;
std::cout << __LINE__ << std::endl;


std::cout << filter.statePost.type() << "\t" << filter.statePost.channels() << "\t" << filter.statePost.size() << std::endl;
std::cout << filter.transitionMatrix.type() << "\t" << filter.transitionMatrix.channels() << "\t" << filter.transitionMatrix.size() << std::endl;
std::cout << filter.statePre.type() << "\t" << filter.statePre.channels() << "\t" << filter.statePre.size() << std::endl;
            filter.statePre = filter.transitionMatrix*filter.statePost;
std::cout << __LINE__ << std::endl;

            filter.temp1 = filter.transitionMatrix*filter.errorCovPost;
std::cout << __LINE__ << std::endl;

            gemm(filter.temp1, filter.transitionMatrix, 1, filter.processNoiseCov, 1, filter.errorCovPre, cv::GEMM_2_T);
std::cout << __LINE__ << std::endl;

            filter.statePre.copyTo(filter.statePost);
std::cout << __LINE__ << std::endl;
            filter.errorCovPre.copyTo(filter.errorCovPost);
std::cout << __LINE__ << std::endl;

            //filter.predict();




std::cout << __LINE__ << std::endl;
            cv::Mat measurement;
            cv::Mat coordinates(tagIt->second);
std::cout << coordinates.type() << "\t" << coordinates.channels() << "\t" << coordinates.size() << std::endl;
            int nChannels = coordinates.channels();
            int nRows = coordinates.rows;
            coordinates
                .reshape(1, coordinates.total()*coordinates.channels())
                .convertTo(measurement, CV_32F);

std::cout << __LINE__ << std::endl;

filter.temp2 = filter.measurementMatrix * filter.errorCovPre;
std::cout << __LINE__ << std::endl;

gemm(filter.temp2, filter.measurementMatrix, 1, filter.measurementNoiseCov, 1, filter.temp3, cv::GEMM_2_T);
std::cout << __LINE__ << std::endl;

solve(filter.temp3, filter.temp2, filter.temp4, cv::DECOMP_SVD);
std::cout << __LINE__ << std::endl;

filter.gain = filter.temp4.t();
std::cout << __LINE__ << std::endl;

std::cout << filter.temp5.type() << "\t" << filter.temp5.channels() << "\t" << filter.temp5.size() << std::endl;
std::cout << measurement.type() << "\t" << measurement.channels() << "\t" << measurement.size() << std::endl;
std::cout << filter.measurementMatrix.type() << "\t" << filter.measurementMatrix.channels() << "\t" << filter.measurementMatrix.size() << std::endl;
std::cout << filter.statePre.type() << "\t" << filter.statePre.channels() << "\t" << filter.statePre.size() << std::endl;
filter.temp5 = measurement - filter.measurementMatrix*filter.statePre;
std::cout << __LINE__ << std::endl;

filter.statePost = filter.statePre + filter.gain*filter.temp5;
std::cout << __LINE__ << std::endl;

filter.errorCovPost = filter.errorCovPre - filter.gain*filter.temp2;
std::cout << __LINE__ << std::endl;

filteredTags[tagIt->first] = filter.statePost(cv::Rect(0,0,1,measurement.total())).reshape(nChannels, nRows);
std::cout << __LINE__ << std::endl;

            //TODO avoid lookup
            //filteredTags[tagIt->first] = filterIt->second.correct(measurement).col(0);
        } else {
std::cout << __LINE__ << std::endl;
            cv::Mat firstMeasurement(tagIt->second);
            const int NDIMS = firstMeasurement.total()*firstMeasurement.channels();
            const auto TYPE = firstMeasurement.depth();
            std::cout << NDIMS << std::endl;
            std::cout << TYPE << std::endl;
            std::cout << CV_32F << std::endl;
            std::cout << CV_64F << std::endl;
            std::cout << CV_64FC1 << std::endl;

            filterIt = mFilters.insert(filterIt, std::make_pair(
                tagIt->first,
                cv::KalmanFilter(NORDERS*NDIMS, NDIMS, 0)));


std::cout << __LINE__ << std::endl;
            auto &filter = filterIt->second;
            // transitionMatrix<NDIMS=3, NORDERS=2> =
            // 1 0 0 1 0 0
            // 0 1 0 0 1 0
            // 0 0 1 0 0 1
            // 0 0 0 1 0 0
            // 0 0 0 0 1 0
            // 0 0 0 0 0 1
            filter.transitionMatrix = cv::Mat::zeros(
                    NORDERS*NDIMS, NORDERS*NDIMS, CV_32F);
            for (int d = 0; d<NDIMS*NORDERS; d+=NDIMS) {
                filter.transitionMatrix.diag(d) = 1.f;
                //std::cout << filter.transitionMatrix << std::endl;
                //filter.transitionMatrix.at(i, j) = 1.f;
            }

std::cout << __LINE__ << std::endl;
            cv::setIdentity(filter.measurementMatrix);
            cv::setIdentity(filter.processNoiseCov, cv::Scalar::all(1e-5));
            cv::setIdentity(filter.measurementNoiseCov, cv::Scalar::all(1e-1));
            cv::setIdentity(filter.errorCovPost, cv::Scalar::all(1));

std::cout << __LINE__ << std::endl;
            // Initialize the filter with the current position
            // The rest (speeds) is already initialised to 0 by default.
            filter.statePost(cv::Rect(0,0,1,NDIMS)) = firstMeasurement.reshape(1, NDIMS);

std::cout << __LINE__ << std::endl;
            //filter.predict();
            filteredTags[tagIt->first] = tagIt->second;
std::cout << __LINE__ << std::endl;
        }

        ++filterIt; //FIXME: iterator after inster
        ++tagIt;

    }

std::cout << __LINE__ << std::endl;
    while (filterIt != mFilters.end()) {
        filteredTags[filterIt->first] = filterIt->second.predict().col(0);
        ++filterIt;
    }

std::cout << __LINE__ << std::endl;
    return filteredTags;
}


template class FindOutdated<int>;
template class SimpleFilter<int, std::vector<cv::Point2f>>;
template class KalmanFilter<int, 2>;
template
    std::map<int, std::vector<cv::Point2f>>
    KalmanFilter<int, 2>::operator()(
        const std::map<int, std::vector<cv::Point2f>> &tags);

template class FindOutdated<std::string>;
template class SimpleFilter<std::string, cv::Matx44d>;
template class KalmanFilter<std::string, 2>;
template
    std::map<std::string, cv::Matx44d>
    KalmanFilter<std::string, 2>::operator()(
        const std::map<std::string, cv::Matx44d> &tags);

}
