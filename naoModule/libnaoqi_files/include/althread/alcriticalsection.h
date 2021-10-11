/**
* @author Aldebaran-Robotics
* Copyright (c) Aldebaran Robotics 2007, 2011 All Rights Reserved
*/


#pragma once
#ifndef _LIBALTHREAD_ALTHREAD_ALCRITICALSECTION_H_
#define _LIBALTHREAD_ALTHREAD_ALCRITICALSECTION_H_

#include <althread/config.h>
#include <boost/shared_ptr.hpp>

namespace AL
{
  class ALMutex;

  class ALTHREAD_API ALCriticalSection
  {
  public:
    ALCriticalSection(boost::shared_ptr<ALMutex> mutex);
    ~ALCriticalSection(void);

    void forceUnlockNow(void);

  private:
    boost::shared_ptr<ALMutex>    fMutexSmartPtr;
  };
}

#endif  // _LIBALTHREAD_ALTHREAD_ALCRITICALSECTION_H_
