/**
 * @author Aldebaran-Robotics
 * Copyright (c) Aldebaran Robotics 2007 All Rights Reserved
 */

#pragma once
#ifndef _LIBALTHREAD_ALTHREAD_ALTHREADPOOL_H_
#define _LIBALTHREAD_ALTHREAD_ALTHREADPOOL_H_

#define POOL_INITIAL_THREAD   92
#define POOL_MAX_THREAD       184
#define POOL_UPDATE_CYCLE     800
#define POOL_UPDATE_THRESHOLD 500
#define POOL_UPDATE_OFFSET    0

#define AL_THREAD_POOL_STOP_KILL true
#define AL_THREAD_POOL_STOP_WAIT false


#include <queue>
#include <boost/shared_ptr.hpp>
#include <boost/smart_ptr/enable_shared_from_this.hpp>
#include <althread/alcriticalsectionread.h>
#include <althread/alcriticalsectionwrite.h>
#include <qi/os.hpp>
#include <ostream>

#ifdef _MSC_VER
  //provide struct timeval (from BSD netstack)
  #include <winsock2.h>
#else
  #include <sys/time.h>
#endif

namespace AL
{
class ALTask;
class ALThread;
class ALMonitor;
class ALMutex;
class ALMutexRW;
class ALCondition;

class ALThreadPool: public ::boost::enable_shared_from_this<ALThreadPool>
{
 public:
  typedef boost::shared_ptr<ALThreadPool>       Ptr;
  typedef boost::shared_ptr<const ALThreadPool> ConstPtr;
  typedef boost::weak_ptr<ALThreadPool>         WeakPtr;
  typedef boost::weak_ptr<const ALThreadPool>   WeakConstPtr;

  inline boost::shared_ptr<ALThreadPool> getThis() {
    return ::boost::enable_shared_from_this<ALThreadPool>::shared_from_this();
  }

  inline boost::shared_ptr<const ALThreadPool> getThis() const {
    return ::boost::enable_shared_from_this<ALThreadPool>::shared_from_this();
  }

  void init(int pInitialThread,
      int pMaxThread,
      int pUpdateCycle,
      int pUpdateThreshold,
      int pUpdateOffset);

  /**
   * \brief Constructor. Init the pool of thread, the queue of task and the monitor.
   *
   * The constructor init the queue of thread with pInitialThread threads. It also
   * init the monitor dans make the pool ready to get a task.
   *
   * @param pInitialThread initial number of thread (default is POOL_INITIAL_THREAD).
   * @param pMaxThread maximum number of thread (default is POOL_MAX_THREAD).
   * @param pUpdateCycle number of task between each thread pool adjustment
   *          (default is POOL_UPDATE_CYCLE)
   * @param pUpdateThreshold (in percent) threshold from which an adjustement is done
   *          (default is POOL_UPDATE_THRESHOLD, see monitor documentation)
   * @param pUpdateOffset number of thread created or destroyed at each adjustment.
   *          (default is POOL_UPDATE_OFFSET)
   */

  ALThreadPool (
    int pInitialThread    = POOL_INITIAL_THREAD,
    int pMaxThread        = POOL_MAX_THREAD,
    int pUpdateCycle      = POOL_UPDATE_CYCLE,
    int pUpdateThreshold  = POOL_UPDATE_THRESHOLD,
    int pUpdateOffset     = POOL_UPDATE_OFFSET);


  /**
   * Free all memory, destruct dependecies
   *
   * @param pKillProcess AL_THREAD_POOL_STOP_KILL (= true) if all working threads must be killed
   *          (default is AL_THREAD_POOL_STOP_WAIT (=false))
   */
  ~ALThreadPool();

  /**
   * Shutdown the process, wait or kill all working threads.
   *
   * If pKillProcess is set to AL_THREAD_POOL_STOP_KILL, all working threads are destroyed whereas
   * if it is not set or set to AL_THREAD_POOL_STOP_WAIT, it will wait termination of all threads
   * before deleting them. It also send back waiting tasks.
   * After the shutdown, ThreadPool is ready to be deleted. Any function call
   * behaviour is undefined.
   *
   * @param pKillProcess AL_THREAD_POOL_STOP_KILL (= true) if all working threads must be killed
   *          (default is AL_THREAD_POOL_STOP_WAIT (=false))
   */

  void shutdown(bool pKillProcess = AL_THREAD_POOL_STOP_WAIT);

  /**
   * Enqueue the task and launch the dispatch.
   *
   * @param pTask task to treat.
   * @return the unique ID of the task (maybe to enable pausing later?)
   */
  int enqueue(boost::shared_ptr<ALTask> pTask);

  /**
   * \brief adjustThread. Allow the monitor ONLY to add or remove new threads.
   *
   * Add or remove pNbThread. If some threads must be removed and all are working,
   * the thread pool will wait for a thread to finish and kill it. The parameter
   * is given there if someone wants to make a dynamic adjustment of the update
   * offset.
   * If the new thread number is contained between 0 and max thread, the adjustment
   * is done, whereas nothing is done.
   *
   * @param pNbThread number of thread to add or remove.
   * @return true if the adjustment is done, false otherwise.
   */

  bool adjustThread(int pNbThread);

  /**
   * \brief taskEnded. Treat an ended task.
   *
   * Take the ended task and send it to the monitor. Then put its termination flag.
   * (maybe send a callback?)
   *
   * @param pTask ended task
   */
  void taskEnded(boost::shared_ptr<ALTask> pTask);


  /**
   * \brief getTask. Return a waiting task if any.
   *
   * Called by a free Thread, this function return a waiting task if there is one
   * or NULL in order to make the thread wait.
   *
   * @return a pointer to a task
   */
  boost::shared_ptr<ALTask> getTask();

  /**
   * \brief apoptosis. Tell a thread if it must kill itself.
   *
   * Thread scheduling implies creating threads when needed but also deleting threads
   * when they are no more needed. This function is called by a thread when its task
   * is finished in order to know if it must kill itself.
   *
   * @param pThread the thread calling the function
   *
   * @return true if the thread should kill itself.
   */
  bool apoptosis(boost::shared_ptr<ALThread> pThread);

  /**
   * \brief getNbThread. Return the current number of thread.
   *
   * This function is for diagnostic purpose.
   *
   * @return the number of thread
   */
  int getNbThread()
  {
      return fNbThread;
  }

  /**
   * \brief getNbTask waiting for a thread
   *
   * This function is for diagnostic purpose.
   *
   * @return the number of task
   */
  int getNbTask()
  {
      return fWaitingTasks.size();
  }


  /**
   * \brief computeSumThreadIdle. Compute the sum of idle time of each thread.
   *
   * WARNING: please don't call it too much often...
   *
   * @return a timeval containing the sum
   */
  qi::os::timeval computeSumThreadIdle(void);  // can't const because mutex use

  void resetSumThreadIdle(void);

  inline void increaseUsedThread()
  {
    ALCriticalSectionWrite sectionNbThread(fUsedThreadMutex);
    fUsedThread++;
  }

  inline void decreaseUsedThread()
  {
    ALCriticalSectionWrite sectionNbThread(fUsedThreadMutex);
    fUsedThread--;
  }

  inline int getUsedThread()
  {
    ALCriticalSectionRead sectionNbThread(fUsedThreadMutex);
    return fUsedThread;
  }

 private:

  /**
   * xIncreaseThread. Increase the number of thread. (same as adjustThread, but simpler, tested and working)
   *
   * @return true if the enlargement is done, false otherwise.
   */
  bool xIncreaseThread(void);

private:

    // ! Number of cycle between each thread adjustment
    int fUpdateCycle;

    // ! Threshold from which an update is done (in seconds of idle time)
    int fUpdateThreshold;

    // ! Number of thread added or removed at each adjustment
    int fUpdateOffset;

  // ! Array of threads
  std::vector <boost::shared_ptr<ALThread> > fThreadPool;

  // HACK we dont want to destroy remanining altask (thread are not killed when we call shutdown.. too lame
  std::vector <boost::shared_ptr<ALThread> > fThreadPoolRestHome;

  // ! Queue of tasks waiting to be executed
  std::queue<boost::shared_ptr<ALTask> > fWaitingTasks;

  // ! Number of threads
  int fNbThread;

  // ! Max number of threadsb
  int fMaxThread;

  // ! Monitor adjusting the pool parameters.
  boost::shared_ptr<ALMonitor> fMonitor;

  // ! Number of threads to be killed (to be removed)
  int fnbrSuperfluThreads;

  // ! fThreadPool Mutex
  const boost::shared_ptr<ALMutex>  fThreadPoolMutex;

  // ! fThreadPool Mutex
  boost::shared_ptr<ALMutexRW>      fUsedThreadMutex;


  // ! fWaitingTasks Mutex
  const boost::shared_ptr<ALMutex>      fWaitingTasksMutex;

  // ! global mutex for waiting
  const boost::shared_ptr<ALMutex>      fThreadWait;

  // ! global condition to wait
  const boost::shared_ptr<ALCondition>  fWaitForTask;

  int fUsedThread;
};
}

#endif  // _LIBALTHREAD_ALTHREAD_ALTHREADPOOL_H_
