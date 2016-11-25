/*******************************************************************************
*   Copyright 2013-2014 EPFL                                                   *
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

/**
 * @file Profiling.hpp
 * @brief Adds very simple cross-platform profiling capability
 * @author Ayberk Özgür
 * @date 2014-10-15
 */

#ifndef PROFILING_HPP
#define PROFILING_HPP

#include<ctime>

#ifdef ANDROID
#include<android/log.h>
#else
#include<cstdio>
#endif

namespace profiling{
    clock_t ticks;
}

//Call this to begin profiling
#define BEGIN_PROFILING profiling::ticks = clock();

//Call this to end profiling and print results
#ifdef ANDROID
#define END_PROFILING(BLOCK_NAME) profiling::ticks = clock() - profiling::ticks; __android_log_print(ANDROID_LOG_INFO, "CHILITAGS",  "%s took: %.2f ms", BLOCK_NAME, ((float)profiling::ticks)/CLOCKS_PER_SEC*1000.0f);
#else //Assuming desktop
#define END_PROFILING(BLOCK_NAME) profiling::ticks = clock() - profiling::ticks; printf("%s took: %.2f ms\n", BLOCK_NAME, ((float)profiling::ticks)/CLOCKS_PER_SEC*1000.0f);
#endif

#endif /* PROFILING_HPP */
