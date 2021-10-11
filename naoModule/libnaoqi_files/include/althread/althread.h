/**
 * @author Aldebaran-Robotics
 * Copyright (c) Aldebaran Robotics 2007, 2011 All Rights Reserved
 */

#pragma once
#ifndef _LIBALTHREAD_ALTHREAD_ALTHREAD_H_
#define _LIBALTHREAD_ALTHREAD_ALTHREAD_H_

#include <pthread.h>
#include <boost/shared_ptr.hpp>
#include <boost/smart_ptr/enable_shared_from_this.hpp>
#include <alerror/alerror.h>
#include <althread/althreadpool.h>
#include <qi/os.hpp>
#include <althread/config.h>

namespace AL
{
  ALTHREAD_API void * _AL_Thread_Pool_Atom(void * pALThread);

  class ALMutex;
  class ALMutexRW;
  class ALCondition;

  class ALTHREAD_API ALThread: public ::boost::enable_shared_from_this<ALThread>
  {
    friend void * _AL_Thread_Pool_Atom(void * pALThread);

  public:
    typedef boost::shared_ptr<ALThread>       Ptr;
    typedef boost::shared_ptr<const ALThread> ConstPtr;
    typedef boost::weak_ptr<ALThread>         WeakPtr;
    typedef boost::weak_ptr<const ALThread>   WeakConstPtr;

    inline boost::shared_ptr<ALThread> getThis() {
      return ::boost::enable_shared_from_this<ALThread>::shared_from_this();
    }

    inline boost::shared_ptr<const ALThread> getThis() const {
      return ::boost::enable_shared_from_this<ALThread>::shared_from_this();
    }

    /**
     * \brief Constructor. Enqueue the thread in the thread pool.
     *
     * Create the structure and enqueue the thread into the thread pool.
     * Store the unique ID of the thread for its future destruction.
     *
     * @param pThreadPool the thread pool managing this thread.
     * @param pID unique ID of the thread
     * @param pThreadWait mutex blocking a task when it has nothing to do
     * @param pWaitForTask cond associated to the mutex
     */
    ALThread(boost::shared_ptr<ALThreadPool> pThreadPool,
       int pID,
       boost::shared_ptr<ALMutex> pThreadWait,
       boost::shared_ptr<ALCondition> pWaitForTask
       );

    /**
     * Do nothing.
     */
    ~ALThread();

    /**
     * Create and launch the pthread
     * @return pthread_create error code
     */
    int launch();

    /**
     * Give a new task to the thread.
     * @return true if a task is assigned.
     */
    bool getTask();

    /**
     * Start the new task.
     */
    void runTask();

     /**
     * \brief setStackSize. set default thread stack size
     */
    static void setStackSize(int pStackSize);

     /**
     * \brief setThreadName. set the name of the calling thread (as visible in
     * debuggers)
     */
    static void setThreadName(const char* pName);

    /**
     * \brief apoptosis. Asks the pool for dying.
     *
     * Thread scheduling implies creating threads when needed but also deleting threads
     * when they are no more needed. This function asks the pool thread if the thread
     * is still needed or not.
     *
     * @return true if the thread should kill itself.
     */
    bool apoptosis();

    /**
     * \brief setID. Set a new ID to the thread
     *
     * Since a thread ID is its position in the pool, it can be moved and this ID can
     * change. This function, called ONLY by the thread pool, is here for this purpose
     *
     * @param pID new ID
     */
    void setID(int pID)
    {
      fID = pID;
    }

    /**
     * Return the ThreadID
     * @return Thread ID
     */
    pthread_t getThreadID()
    {
      return fThreadID;
    }

    /**
     * Return the ID of the thread
     * @return ID
     */
    int getID()
    {
      return fID;
    }

    struct qi::os::timeval GetIdleSum(void) const
    {
      return fIdleSum;
    }

    void ResetIdleSum(void)
    {
      fIdleSum.tv_sec = 0;
      fIdleSum.tv_usec = 0;
    }

    protected:
    // Mutex to stop execution of thread if no task
    boost::shared_ptr<ALMutex>      fThreadWait;
    // Blocking condition
    boost::shared_ptr<ALCondition>  fWaitForTask;
    // Task Mutex
    boost::shared_ptr<ALMutexRW>    fTaskMutex;

    public:
      inline boost::shared_ptr<ALThreadPool> getThreadPool(void)
      {
          boost::shared_ptr<ALThreadPool> returnPtr = fThreadPool.lock();
          // it can be possible that the task has to thread pool, but this function should never be called when it's the case.
          // indeed the thread pool set the task to kill itself when that's the case, and therefore it should exit the thread.
          return returnPtr;
      }

      /**
       * This thread has been ask to kill its pthread. You just have to wake it up now !
       */
      void killThread();

  private :
    // last time of beginning of an idle period
    struct qi::os::timeval fIdleDate;

    // Thread Idle Time (in usec)
    // int fIdleTime; // limited to duration shorter than 1h11 !!!!!
    struct qi::os::timeval fIdleSum;

    // Unique ID of the thread.
    int fID;

    // Unique ID of the pthread
    pthread_t fThreadID;

    // Parent Thread Pool
    boost::weak_ptr<ALThreadPool> fThreadPool;

    bool fKillThread;

    // Current task
    boost::shared_ptr<ALTask> fTask;    // not owned (set to NULL if no task)
  };
}
#endif  // _LIBALTHREAD_ALTHREAD_ALTHREAD_H_
