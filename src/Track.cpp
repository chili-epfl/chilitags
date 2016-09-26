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

#include "Track.hpp"
#include "GrowRoi.hpp"
#include "ScreenOut.hpp"

#include "opencv2/video/tracking.hpp"

namespace chilitags {

#ifdef HAS_MULTITHREADING
Track::Track() :
    mRefine(),
    mPrevFrame(),
    mFromTags(),
    mInputLock(PTHREAD_MUTEX_INITIALIZER)
#else
Track::Track() :
    mRefine(),
    mPrevFrame(),
    mFromTags()
#endif
{
}

void Track::update(TagCornerMap const& tags)
{
#ifdef HAS_MULTITHREADING
    pthread_mutex_lock(&mInputLock);
#endif

    auto targetIt = mFromTags.begin();
    for(const auto& tag : tags) {
        while(targetIt != mFromTags.end() && targetIt->first < tag.first)
            targetIt++;

        if(targetIt != mFromTags.end() && targetIt->first == tag.first)
            targetIt->second = tag.second;
        else
            targetIt = mFromTags.insert(targetIt, tag);
    }

#ifdef HAS_MULTITHREADING
    pthread_mutex_unlock(&mInputLock);
#endif
}

TagCornerMap Track::operator()(cv::Mat const& grayscaleInputImage)
{

    std::vector<uchar> status;
    std::vector<float> errors;

    //Do the tracking
#ifdef HAS_MULTITHREADING
    pthread_mutex_lock(&mInputLock);
#endif
    TagCornerMap trackedTags;
    Quad quad;
    for (auto tag : mFromTags) {
        Quad result;

        static const float GROWTH_RATIO = 20.0f/10.0f;
        cv::Rect roi = growRoi(grayscaleInputImage, cv::Mat_<cv::Point2f>(tag.second), GROWTH_RATIO);
        cv::Point2f roiOffset = roi.tl();
        for (int i : {0,1,2,3}) {
            tag.second(i,0) -= roiOffset.x;
            tag.second(i,1) -= roiOffset.y;
        }

        cv::calcOpticalFlowPyrLK(
            mPrevFrame(roi), grayscaleInputImage(roi),
            tag.second, result,
            status, errors,
            //TODO play with parameters (with tests)
            cv::Size(21,21), 3,
            cv::TermCriteria(cv::TermCriteria::COUNT+cv::TermCriteria::EPS, 30, 0.01f)
            );

        for (int i : {0,1,2,3}) {
            result(i,0) += roiOffset.x;
            result(i,1) += roiOffset.y;
        }

        if (cv::sum(cv::Mat(status))[0] == status.size()) {
            quad = mRefine(grayscaleInputImage, result, 0.5f/10.0f);
            if(ScreenOut::isConvex(quad))
                trackedTags[tag.first] = quad;
        }
    }

    mFromTags = std::move(trackedTags);
    TagCornerMap tagsCopy = mFromTags; //TODO: Try to get around this copy
#ifdef HAS_MULTITHREADING
    pthread_mutex_unlock(&mInputLock);
#endif

    //Swap current and previous frames
    grayscaleInputImage.copyTo(mPrevFrame);

    return tagsCopy;
}

} /* namespace chilitags */
