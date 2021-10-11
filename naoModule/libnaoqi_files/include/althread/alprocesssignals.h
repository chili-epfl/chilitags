/**
* @author Aldebaran Robotics
* Copyright (c) Aldebaran Robotics 2007, 2011 All Rights Reserved.
*
*
* ALProcessSignals offers two signals: preProcess and postProcesss.
* Connected method pointers will be called in the host thread's context.
*
* Typically this is used as a base class of a class which does recurrent
* processing. Other classes can attach themselves to the preProcess or
* postProcess so that they can do small ammounts of work at a specific
* point of a processing loop. Please note that all attached workers
* will do their work in your context. If you are in a real time thread
* they will also be in a real time thread, and should respect the
* constraints that this implies.
*
* call preProcess
*   -> all connected methods are called
* ... do your work ...
* call postProcess
*   -> all connected methods are called
* ... possibly sleep until next time you want to work
*
* See althread/alconditionmanager.h for a sychronizer that is based
* on conditions rather than signals so that work takes place is other
* threads.
*/


#pragma once
#ifndef _LIBALTHREAD_ALTHREAD_ALPROCESSSIGNALS_H_
#define _LIBALTHREAD_ALTHREAD_ALPROCESSSIGNALS_H_

#include <althread/config.h>
#include <boost/signal.hpp>

namespace AL
{
  class ALProcessSignals
  {
  public :
    ALProcessSignals()  {}
    ~ALProcessSignals() {}

    typedef boost::signal<void ()>                     ProcessSignal;
    typedef boost::signal<void ()>::slot_function_type ProcessSignalSlot;
    typedef boost::signals::connect_position           ProcessSignalPosition;
    typedef boost::signals::connection                 ProcessSignalConnection;

    /**
     * Connect to the preProcess signal
     */
    inline ProcessSignalConnection atPreProcess(
        ProcessSignalSlot subscriber,
        ProcessSignalPosition pos = boost::signals::at_back)
    {
      return fPreProcess.connect(subscriber, pos);
    }

    /// Connect to the postProcess signal
    inline ProcessSignalConnection atPostProcess(
      ProcessSignalSlot subscriber,
      ProcessSignalPosition pos = boost::signals::at_back)
    {
      return fPostProcess.connect(subscriber, pos);
    }

    inline void removeAllPreProcess(void) {
      fPreProcess.disconnect_all_slots();
    }

    inline void removeAllPostProcess(void) {
      fPostProcess.disconnect_all_slots();
    }

    /// Trigger methods attached to preProcess
    inline void preProcess(void) {
      fPreProcess();
    }

    /// Trigger methods attached to postProcess
    inline void postProcess(void) {
      fPostProcess();
    }

  protected:
    ProcessSignal fPreProcess;
    ProcessSignal fPostProcess;
  };
}
#endif  // _LIBALTHREAD_ALTHREAD_ALPROCESSSIGNALS_H_
