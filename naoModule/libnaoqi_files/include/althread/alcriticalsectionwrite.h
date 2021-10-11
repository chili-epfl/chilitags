/**
* @author Aldebaran Robotics
* Copyright (c) Aldebaran Robotics 2007, 2011 All Rights Reserved
*/


#pragma once
#ifndef _LIBALTHREAD_ALTHREAD_ALCRITICALSECTIONWRITE_H_
#define _LIBALTHREAD_ALTHREAD_ALCRITICALSECTIONWRITE_H_

#include <althread/config.h>
#include <boost/shared_ptr.hpp>

namespace AL
{
  class ALMutexRW;

  class ALTHREAD_API ALCriticalSectionWrite
  {
  public:
    ALCriticalSectionWrite(boost::shared_ptr<ALMutexRW> pMutex);
    ~ALCriticalSectionWrite(void);

  private:
    boost::shared_ptr<ALMutexRW>   fMutexSmartPtr;
  };
}

#endif  // _LIBALTHREAD_ALTHREAD_ALCRITICALSECTIONWRITE_H_
