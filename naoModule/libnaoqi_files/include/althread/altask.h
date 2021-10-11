/**
* @author Aldebaran-Robotics
* Copyright (c) Aldebaran Robotics 2007, 2011 All Rights Reserved
*/


#pragma once
#ifndef _LIBALTHREAD_ALTHREAD_ALTASK_H_
#define _LIBALTHREAD_ALTHREAD_ALTASK_H_

#include <string>
#include <qi/os.hpp>
#include <althread/config.h>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace AL
{
  class ALThread;

  class ALTHREAD_API ALTask
  {
  public:

    /**
     * Indicates the state of the task, it is either IDLE, RUNNING or ENDED
     */
    typedef enum { IDLE, RUNNING, ENDED } ALTPState;

    /**
     * Constructor. User defined. Must stock in private fields run parameters.
     *
     * Defined by users. If a user wants to access to some parameters during execution,
     * he should stock them as private fields.
     */
    ALTask();

    /**
     * Users may define their own destructors while constructing their class.
     */
    virtual ~ALTask();

    /**
     * Instruction to run in the thread. parameters should be private members of the
     * class. User should use privete members to get the result too.
     */
    virtual void run() = 0;

    virtual void exitTask() {}

    /**
     * @brief Set the name of the task.
     * @param name the name of the task.
     */
    void setTaskName(const std::string& pName);

  private:
    /**
    * setCreationTime
    */
    void setCreationTime();

    /**
    * setExecutionTime
    * Execution task time
    */
    void setExecutionTime();

    /**
    * setEndTime
    * End task time
    */
    void setEndTime();

  public :
    /**
    * Thread affectation
    */
    void setThread(boost::shared_ptr<ALThread> pThread);

    /**
    * set state machine
    */
    void setState(ALTPState pState)
    {
      fState = pState;
    }

    /**
     * Get the name of the task.
     * @return name the name of the task.
     */
    virtual const std::string& getTaskName () const;

    /**
    * getIdleTime
    * return IdleTime in usec.
    */
    int getIdleTime();

    /**
    * getExecutionTime
    * return execution time in usec.
    */
    int getExecutionTime();


    /**
    * getThread
    * return ALThread.
    */
    boost::weak_ptr<ALThread> getThread() {
      return fThread;
    }

    /**
    * getState
    * return machine state
    */
    ALTPState getState() {
      return fState;
    }

    void waitForEndOfTask();

    std::string toString() const;

    /**
    * fAutoDelete
    * Tell if the task must be deleted after the treatment
    */
    bool fAutoDelete;

  private:
    std::string fName;
    struct qi::os::timeval fCreationTime;
    struct qi::os::timeval fExecutionTime;
    struct qi::os::timeval fEndTime;

    // State of the task : IDLE / RUNNING / ENDED
    volatile ALTPState fState;

  protected:
    // Thread treating this task
    boost::weak_ptr<ALThread> fThread;
  };
}  // namespace AL
#endif  // _LIBALTHREAD_ALTHREAD_ALTASK_H_
