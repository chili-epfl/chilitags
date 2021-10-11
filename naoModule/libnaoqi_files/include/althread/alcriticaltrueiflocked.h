/**
* @author Aldebaran Robotics
* Copyright (c) Aldebaran Robotics 2007, 2011 All Rights Reserved
*/

#pragma once
#ifndef _LIBALTHREAD_ALTHREAD_ALCRITICALTRUEIFLOCKED_H_
#define _LIBALTHREAD_ALTHREAD_ALCRITICALTRUEIFLOCKED_H_

#include <althread/config.h>
#include <boost/shared_ptr.hpp>

namespace AL
{
  class ALMutex;

  class ALTHREAD_API ALCriticalTrueIfLocked
  {
  public:
    ALCriticalTrueIfLocked(boost::shared_ptr<ALMutex> mutex, bool &alreadyLocked);
    ~ALCriticalTrueIfLocked(void);

    void forceUnlockNow(void);

  private:
    void *fMutex;
    bool  fAlreadyLocked;
  };
}

#endif  // _LIBALTHREAD_ALTHREAD_ALCRITICALTRUEIFLOCKED_H_
