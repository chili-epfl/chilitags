/* -*- C++ -*-  */
/**
 * @author Cedric GESTES
 * Copyright (c) Aldebaran Robotics 2008 All Rights Reserved
 *
 */

#pragma once

#ifndef _LIB_RTTOOLS_RTTOOLS_RTPERIOD_H_
#define _LIB_RTTOOLS_RTTOOLS_RTPERIOD_H_

# include <time.h>
# include <rttools/time-winp.h>

/**
 * @brief this class allow to create periodic loop or thread
 * set the period, then before the loop call periodInit
 * and loop on periodWait
 */
class RtPeriod {
public:
  RtPeriod();


  void setPeriod(const signed long mSec);


  /**
   * init the period
   */
  void periodInit();

/**
 * wait for the end of the timeslice (interval)
 * if the timeslice is already elapsed, it doesnt wait and return a negative value
 * @return the delta between the current time and the time we wanted (microsec)
 *
 * 1) get the current time, verify that we dont missed the deadline
 * 2) if (waittime > 1000us) wait till the end of the timeslice (if needed)
 * 3) update values for the next time
 *
 * @param pAllowDrift If false, we hope to be woken at exact multiples
 *                    of mSec relative to the start
 */
  int periodWait(bool pAllowDrift = true);

protected:
  void computeStat();

protected:
  struct timespec       fNow;
  struct timespec       fNext;
  struct timespec       fInterval;
  int                   fUsedClock;

  ///stat
protected:
  signed long                fCurrentDiff;
  signed long                fCurrentWait;

  signed long                fMinDiff;
  signed long                fMinWait;

  signed long                fMaxDiff;
  signed long                fMaxWait;

  signed long                fAvgDiff;
  signed long                fAvgWait;

  unsigned long                fTickCount;

};


#endif  // _LIB_RTTOOLS_RTTOOLS_RTPERIOD_H_
