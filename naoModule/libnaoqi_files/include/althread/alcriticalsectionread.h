/**
* @author Aldebaran Robotics
* Copyright (c) Aldebaran Robotics 2007, 2011 All Rights Reserved
*/

#pragma once
#ifndef _LIBALTHREAD_ALTHREAD_ALCRITICALSECTIONREAD_H_
#define _LIBALTHREAD_ALTHREAD_ALCRITICALSECTIONREAD_H_

#include <althread/config.h>
#include <boost/shared_ptr.hpp>

namespace AL
{
  class ALMutexRW;

  class ALTHREAD_API ALCriticalSectionRead
  {
  public:
    ALCriticalSectionRead(boost::shared_ptr<ALMutexRW> pMutex);
    ~ALCriticalSectionRead(void);

  private:
    boost::shared_ptr<ALMutexRW> fMutexSmartPtr;
  };
}

#endif  // _LIBALTHREAD_ALTHREAD_ALCRITICALSECTIONREAD_H_
