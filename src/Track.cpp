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

#include "opencv2/video/tracking.hpp"

namespace chilitags{

Track::Track():
mRefine(),
mPrevFrame(),
mCurrentFrame(),
mFromTags()
{
}

void Track::update(const TagCornerMap &tags) {
    mFromTags = tags;
}

TagCornerMap chilitags::Track::operator()(cv::Mat const& grayscaleInputImage)
{

    //Swap current and previous frames and get new frame
    mCurrentFrame.copyTo(mPrevFrame);
    grayscaleInputImage.copyTo(mCurrentFrame);

    std::vector<uchar> status;
    std::vector<float> errors;

    TagCornerMap trackedTags;
    for (auto tag : mFromTags) {
        Quad result;

        static const float GROWTH_RATIO = 20.0f/10.0f;
        cv::Rect roi = growRoi(mCurrentFrame, cv::Mat_<cv::Point2f>(tag.second), GROWTH_RATIO);
        cv::Point2f roiOffset = roi.tl();
        for (int i : {0,1,2,3}) {
            tag.second(i,0) -= roiOffset.x;
            tag.second(i,1) -= roiOffset.y;
        }

        cv::calcOpticalFlowPyrLK(
            mPrevFrame(roi), mCurrentFrame(roi),
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
            trackedTags[tag.first] = mRefine(mCurrentFrame, result, 0.5f/10.0f);
        }
    }

    mFromTags = std::move(trackedTags);
    return mFromTags;
}

} /* namespace chilitags */
