/**
* @author Aldebaran Robotics
* Copyright (c) Aldebaran Robotics 2007, 2011 All Rights Reserved
*/


#pragma once
#ifndef _LIBALTHREAD_ALTHREAD_ALMONITOR_H_
#define _LIBALTHREAD_ALTHREAD_ALMONITOR_H_

#include <boost/shared_ptr.hpp>
#include <althread/config.h>
#include <qi/os.hpp>

namespace AL
{
  class ALMutex;
  class ALThreadPool;
  class ALTask;

  class ALTHREAD_API ALMonitor
  {
  public:

    /**
    * \brief Constructor. Init cycle, threshold, offset and reference to pool.
    *
    * Intialize all variables : cycle, threshold (in seconds), offset and reference to the pool.
    */
    ALMonitor(int pUpdateCycle,
              int pUpdateThreshold,
              int pUdpateOffset,
              boost::shared_ptr<ALThreadPool> pThreadPool);

    /**
    * \brief Destructor. Nothing to do.
    *
    * Nothing to do.
    */
    ~ALMonitor();

    /**
    * \brief assimilate. Take a task, read datas and update stats.
    *
    * Assimilate take a task and read idle and execution time of the task. Adjust the
    * number of thread according to these stats.
    *
    * @param pTask task to study.
    */
    void assimilate(boost::shared_ptr<ALTask> pTask);

    /**
    * \brief adjustPool. Readjust the thread number according to its stats.
    *
    * This function will adjust the number of threads in the pool according to the
    * needs of the program. See the documentation to know which algorithm is used.
    */
    void adjustPool();

  private:

    //! Associated Thread Pool
    boost::shared_ptr<ALThreadPool> fThreadPool;

    //! Mutex for task assimilation
    boost::shared_ptr<ALMutex> fAssimilator;

    //! Number of cycle between each thread adjustment
    int fUpdateCycle;

    //! Threshold from which an update is done (in seconds of idle time)
    int fUpdateThreshold;

    //! Number of thread added or removed at each adjustment
    int fUpdateOffset;

    //! Counter of cycle
    int fCounterCycle;

    // int fTaskIdle; // WARNING: limits to 1h11
    qi::os::timeval fTaskIdle;

    int fThreadIdle;
  };
}  //namespace AL
#endif  // _LIBALTHREAD_ALTHREAD_ALMONITOR_H_
