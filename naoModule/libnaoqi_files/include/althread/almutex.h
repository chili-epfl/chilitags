/**
* @author Aldebaran-robotics
* Copyright (c) Aldebaran Robotics 2007, 2011 All Rights Reserved
*/

#pragma once
#ifndef _LIBALTHREAD_ALTHREAD_ALMUTEX_H_
#define _LIBALTHREAD_ALTHREAD_ALMUTEX_H_

#include <althread/config.h>
#include <boost/shared_ptr.hpp>

namespace AL
{
  class ALTHREAD_API ALMutex
  {
    friend class ALCriticalSection;
    friend class ALCriticalTrueIfLocked;
    friend class ALCondition;

  public:
    static boost::shared_ptr<ALMutex> createALMutex();
    virtual ~ALMutex(void);

    void lock();
    void unlock();

  protected:
    ALMutex();

  private:
    //pthread_mutex_t*
    void *fMutex;
  };


  class ALTHREAD_API ALMutexRW
  {
    friend class ALCriticalSectionRead;
    friend class ALCriticalSectionWrite;

  public:
    static boost::shared_ptr<ALMutexRW> createALMutexRW();
    virtual ~ALMutexRW(void);

    void readLock();
    void writeLock();
    void unlock();

  protected:
    ALMutexRW();

  private:
    //pthread_rwlock_t
    void *fMutex;
  };


  class ALTHREAD_API ALCondition
  {
  public:
    static boost::shared_ptr<ALCondition> createALCondition();
    void wait(boost::shared_ptr<ALMutex> pMutex);
    void broadcast();
    void signal();
    virtual ~ALCondition(void);

  protected:
    ALCondition();

  private:
    //pthread_cond_t
    void *fCondition;
  };
}

#endif  // _LIBALTHREAD_ALTHREAD_ALMUTEX_H_
