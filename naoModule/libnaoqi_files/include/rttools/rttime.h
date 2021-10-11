/* -*- C++ -*-  */
/**
 * @author Cedric GESTES, modifications Pierre-Emmanuel VIEL
 * Copyright (c) Aldebaran Robotics 2008 All Rights Reserved
 *
 */

#pragma once

#ifndef _LIB_RTTOOLS_RTTOOLS_RTTIME_H_
#define _LIB_RTTOOLS_RTTOOLS_RTTIME_H_

#include <time.h>
#include <pthread.h>

static const long gUsecPerSec = 1000000;
static const long gNsecPerSec = 1000000000;


/**
 * add two timespec
 */
inline struct timespec timespec_add(const struct timespec &ts, const struct timespec &ts2)
{
  struct timespec ret;

  ret.tv_sec = ts.tv_sec + ts2.tv_sec;
  ret.tv_nsec = ts.tv_nsec + ts2.tv_nsec;

  while (ret.tv_nsec >= gNsecPerSec) {
    ret.tv_nsec -= gNsecPerSec;
    ret.tv_sec++;
  }
  return ret;
}

/**
 * return the difference between t1 and t2 in nanosecond
 * t1: stop, t2: start
 */
inline long timespec_diff_ns(const struct timespec &t1, const struct timespec &t2)
{
  long diff;

  diff = (long)((long long)gNsecPerSec * (long long)(t1.tv_sec - t2.tv_sec));
  diff += t1.tv_nsec - t2.tv_nsec;
  return diff;
}

/**
 * return the difference between t1 and t2 in microsecond
 */
inline signed long timespec_diff_us(const struct timespec &t1, const struct timespec &t2)
{
  long diff;

  diff = (long)((long long)gUsecPerSec * (long long)(t1.tv_sec - t2.tv_sec));
  diff += ((long)((long long)(t1.tv_nsec - t2.tv_nsec)) / 1000);
  return diff;
}


/**
 * Encapsulation of the clock_gettime() function for precise time operations (nanoseconds).
 */
class RtTime {
public:
  /**
   * Default constructor.
   * @param clockType The type of clock used between 0:CLOCK_REALTIME 1:CLOCK_MONOTONIC 2:CLOCK_PROCESS_CPUTIME_ID 3:CLOCK_THREAD_CPUTIME_ID \n
   *                  If no argument is provided, 1 by default \n
   *                  If the requested clock level is not provided by the kernel, and if the use of a lower clock level isn't managed by it, constructor will decrease the level.
   */
  RtTime(const int clockType = 0);  // 0:CLOCK_REALTIME 1:CLOCK_MONOTONIC 2:CLOCK_PROCESS_CPUTIME_ID 3:CLOCK_THREAD_CPUTIME_ID

public:
  /**
   * Default start clock.
   */
  void          start();
  /**
   * Default stop clock.
   */
  void          stop();
  /**
   * User defined clock.
   * @param t The user defined timespec variable receiving the current time
   */
  void          getTime(timespec &t);  // allows users to use their own time variables (for more complex time profiling)

  /**
   * Difference between stop and start in ns.
   */
  unsigned long        diffNs();

  /**
   * Difference between stop and start in ns.
   */
  unsigned long        diffUs();

  /**
   * Difference between tstop and tstart in ns
   * Allows users to obtain time differences using their own time variables (for more complex time profiling)
   * @param tstart The user defined start time
   * @param tstop The user defined stop time
   */
  unsigned long        diffNs(const struct timespec &tstart, const struct timespec &tstop);

  /**
   * Difference between tstop and tstart in us
   * Allows users to obtain time differences using their own time variables (for more complex time profiling)
   * @param tstart The user defined start time
   * @param tstop The user defined stop time
   */
  unsigned long        diffUs(const struct timespec &tstart, const struct timespec &tstop);

  /**
   * Returns the type of clock accepted by the kernel, that might be different from the one asked in the constructor
   */
  unsigned long        getUsedClock();  // returns the clock mode accepted by the kernel that might be different from the one provided in the constructor

  signed long        absSleep(const timespec &tm)const;
  static signed long mSleep(const unsigned long sleepMs);
  static signed long uSleep(const unsigned long sleepUs);
  static signed long nSleep(const unsigned long sleepNs);

  static int    checkClock(int pClock);
  static int    getClock(const int clockType = 0);

private:
  unsigned long        fUsedClock;
  timespec      fDiffStart;
  timespec      fDiffStop;
};


/**
 * Prints the time spent executing of `f' ; also prints a message `m' before.
 */
# define RTDIFF(m, f)            \
  {                \
    RtTime rtm;              \
    rtm.start();            \
    f;                \
    rtm.stop();              \
    std::cout << m << " " << rtm.diffNs() << "ns" << std::endl;  \
  }

#endif  // _LIB_RTTOOLS_RTTOOLS_RTTIME_H_
