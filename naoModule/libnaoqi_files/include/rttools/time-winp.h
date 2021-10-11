/* -*- C++ -*-  */
/**
 * @author Cedric GESTES
 * Copyright (c) Aldebaran Robotics 2008, 2011 All Rights Reserved
 *
 * time.h => Windows Is Not Posix version
 */
#pragma once

#ifndef _LIB_RTTOOLS_RTTOOLS_TIME_WINP_H_
#define _LIB_RTTOOLS_RTTOOLS_TIME_WINP_H_

/**
 * missing function under windows and mac
 *
 * for windows: use QueryPerformanceCounter/QueryPerformanceFrequency to get precise time
 *
 */
# ifndef __linux__

#  include <qi/os.hpp>
#  include <rttools/rttime.h>

#  define CLOCK_MONOTONIC (0)
#  define CLOCK_REALTIME (0)
#  define CLOCK_PROCESS_CPUTIME_ID (0)
#  define CLOCK_THREAD_CPUTIME_ID (0)

#  define TIMER_ABSTIME (0)

inline int clock_getres(int clk, struct timespec *tm)
{
  return 0;
}

inline int clock_gettime(int clk, struct timespec *tm)
{
  struct qi::os::timeval tv;
  qi::os::gettimeofday(&tv);
  tm->tv_sec = tv.tv_sec;
  tm->tv_nsec = tv.tv_usec * 1000;
  return 0;
}

inline int clock_nanosleep(int clk, int flag, const struct timespec *tm, struct timespec *tm2)
{
  struct timespec t1;
  long diff;
  int diffms = 0;

  clock_gettime(0, &t1);

//  printf("T1: (%ld,%ld)\n", (&t1)->tv_sec, (&t1)->tv_nsec);
//  printf("T2: (%ld,%ld)\n", tm->tv_sec, tm->tv_nsec);
  diff = timespec_diff_ns(*tm, t1);
  diffms = diff / 1000 / 1000;
//printf("diff(%ld): %ld\n", diff, diffms);
  if (diffms > 0)
    qi::os::msleep(diffms);
  return 0;
}

# endif

/**
 * missing function under windows
 */
#ifdef _WIN32

inline int nanosleep(const struct timespec *tm, const struct timespec *tm2)
{
  qi::os::msleep(tm->tv_nsec / (1000000));
  return 0;
}
# endif

#endif  // _LIB_RTTOOLS_RTTOOLS_TIME_WINP_H_
