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

#ifndef DETECT_HPP
#define DETECT_HPP

#include <map>

#ifdef HAS_MULTITHREADING
#include <pthread.h>
#endif

#include <opencv2/core/core.hpp>

#include "FindQuads.hpp"
#include "Decode.hpp"
#include "Refine.hpp"
#include "ReadBits.hpp"
#include "Track.hpp"

namespace chilitags {

class Detect {

public:

Detect();

void setMinInputWidth(int minWidth);

void setCornerRefinement(bool refineCorners);

void operator()(cv::Mat const& inputImage, TagCornerMap& tags);

#ifdef HAS_MULTITHREADING
void launchBackgroundThread(Track& track);

void shutdownBackgroundThread();
#endif

protected:

bool mRefineCorners;

FindQuads mFindQuads;
Refine mRefine;
ReadBits mReadBits;
Decode mDecode;

cv::Mat mFrame;
TagCornerMap mTags;

void doDetection(TagCornerMap& tags);

#ifdef HAS_MULTITHREADING
Track* mTrack;

pthread_t mBackgroundThread;

bool mBackgroundRunning;
bool mBackgroundShouldRun;
bool mNeedFrame;

pthread_cond_t mInputCond;
pthread_mutex_t mInputLock;

static void* dispatchRun(void* args);
void run();
#endif

};

} /* namespace chilitags */

#endif /* DETECT_HPP */
