/* -*- C++ -*-  */
/**
 * @author Cedric GESTES
 * Copyright (c) Aldebaran Robotics 2008 All Rights Reserved
 *
 */

#pragma once

#ifndef _LIB_RTTOOLS_RTTOOLS_RTTHREAD_H_
#define _LIB_RTTOOLS_RTTOOLS_RTTHREAD_H_

# include <pthread.h>
# include <time.h>
# include <rttools/rtperiod.h>

class RtThread : public RtPeriod {
public:
  typedef void *(funcptr)(void *);

public:
  RtThread();
  virtual ~RtThread();

  /**
   * set the realtime capability of the thread
   * scheduler maybe:
   * SCHED_OTHER: system scheduler
   * SCHED_FIFO : execute the thread til a blocking function (or preemption by a higher priority function)
   * SCHED_RR   : same as FIFO, but dont execute for more than a timeslice (less agressive for the system)
   * rtprio have no impact when using SCHED_OTHER
   */
  int setRealtime(int scheduler, int rtprio);

  /**
   * Create the thread
   */
  int create();

  /**
   * Join the thread
   */
  int join();

  /**
   * cancel the thread
   */
  int cancel();



public:
  virtual void *execute() = 0;
  virtual void postExecute() {;}
  virtual void preExecute() {;}

protected:
  int                   fUsedClock;
  pthread_attr_t        fAttr;
  pthread_t             fThread;
};


#endif  // _LIB_RTTOOLS_RTTOOLS_RTTHREAD_H_
