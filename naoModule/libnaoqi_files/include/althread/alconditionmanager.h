/**
* @author Aldebaran Robotics
* Copyright (c) Aldebaran Robotics 2010, 2011 All Rights Reserved.
*
* ALConditionManager maintains a list of conditions and
* for each condition a list of those who are waiting for
* the condition.
*
* A call to addCondition adds a named condition.
* A call to waitForCondition waits for the condition to be triggered
* A call to triggerCondition releases all those who are waiting
*/


#pragma once
#ifndef _LIBALTHREAD_ALTHREAD_ALCONDITIONMANAGER_H_
#define _LIBALTHREAD_ALTHREAD_ALCONDITIONMANAGER_H_

#include <althread/config.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <map>

namespace AL
{
  class ALMutex;
  class ALCondition;

  class ALTHREAD_API ALConditionManager
  {

  public:
    ALConditionManager();

    virtual ~ALConditionManager();

    /**
    * Creates a condition for synchronization between threads
    * @param pConditionName The name of the new signal
    */
    void addCondition(const std::string &pConditionName);

    /**
    * Waits until the named condition is triggered
    * @pConditionName The name of the signal to wait for
    */
    void waitForCondition(const std::string &pConditionName);

    /**
    * Triggers the condition of all those who are waiting
    * @param pConditionName The name of the signal to trigger
    */
    void triggerCondition(const std::string &pConditionName);

  protected:
    typedef std::map<std::string, std::pair<boost::shared_ptr<ALCondition>, boost::shared_ptr<ALMutex> > >  TSynchronizerMap;
    typedef TSynchronizerMap::iterator ITSynchronizerMap;

    TSynchronizerMap fSynchonizer;
  };
}
#endif  // _LIBALTHREAD_ALTHREAD_ALCONDITIONMANAGER_H_
