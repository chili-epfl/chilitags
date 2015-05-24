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

#ifndef Track_HPP
#define Track_HPP

#include <map>
#ifdef HAS_MULTITHREADING
#include <pthread.h>
#endif

#include <opencv2/core/core.hpp>

#include <chilitags.hpp>
#include "Refine.hpp"

namespace chilitags {

class Track
{
public:

Track();

//Both these methods are thread-safe
void update(TagCornerMap const& tags);
TagCornerMap operator()(cv::Mat const& inputImage);

protected:

Refine mRefine;

cv::Mat mPrevFrame;
TagCornerMap mFromTags;

#ifdef HAS_MULTITHREADING
pthread_mutex_t mInputLock;
#endif

};

}

#endif
