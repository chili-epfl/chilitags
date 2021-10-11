/**
 * @author Aldebaran Robotics
 * Copyright (c) Aldebaran Robotics 2007, 2011, 2012 All Rights Reserved
 */

/** @file
 *  @brief
 */

#pragma once
#ifndef _LIBALCOMMON_ALCOMMON_ALMODULE_H_
#define _LIBALCOMMON_ALCOMMON_ALMODULE_H_

# include <alcommon/api.h>
# include <qi/macro.hpp>
# include <alcommon/almodulecore.h>
# include <boost/signal.hpp>

/// \brief NAOqi
namespace AL
{
  class ALBroker;
  class ALProxy;
  class ALValue;


  namespace detail
  {
    class ALProcessSignals
    {
    public:
      ALProcessSignals()  {}
      virtual ~ALProcessSignals() {}

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


  /**
   * \class ALModule almodule.h "alcommon/almodule.h"
   * \brief ALModule can be used as a base class for user modules to
   * help serve and advertise their methods.
   *
   * Each module advertises the methods that it wishes to make available
   * to clients participating in the network to a broker within the
   * same process.
   *
   * The broker then transparently handles directory services so that clients
   * need not know if the module that provides a service is in the
   * same process, on the same machine, or on the same tcp network.
   *
   * Within the same process, direct method calls are used to
   * provide optimal speed without having to change your method
   * signatures.
   *
   * Clients exist in a growing number of languages including c++,
   * Python, .Net, Java and Matlab.
   *
   * \ingroup Module
   */
  class ALModule: public ALModuleCore, public detail::ALProcessSignals
  {
    friend class baseModule;

  public:
    /**
     * \brief Create a module and link it to a broker.
     * \param pBroker Pointer to the broker
     * \return A pointer to the module
     * \throw ALError
     */
    template <class T>
    static boost::shared_ptr<T> createModule(boost::shared_ptr<ALBroker> pBroker)
    {
      boost::shared_ptr<T> module(new T(pBroker));
      module->initModule();
      try
      {
        // we call init on a ALModule::Ptr as init may be protected
        // init is a virtual method that can be reimplemented
        (boost::static_pointer_cast<ALModule>(module))->init();
      }
      catch(const ALError& e)
      {
        module->exit();
        throw(e);
      }
      return module;
    }

    /**
     * \brief Create a module and link it to a broker.
     * \param pBroker Pointer to the broker
     * \param p1 first parameter after pBroker for the module's constructor
     * \return A pointer to the module
     * \throw ALError
     */
    template <class T, typename P1>
    static boost::shared_ptr<T> createModule(boost::shared_ptr<ALBroker> pBroker, P1 p1)
    {
      boost::shared_ptr<T> module(new T(pBroker, p1));
      module->initModule();
      try
      {
        // we call init on a ALModule::Ptr as init may be protected
        // init is a virtual method that can be reimplemented
        (boost::static_pointer_cast<ALModule>(module))->init();
      }
      catch(const ALError& e)
      {
        module->exit();
        throw(e);
      }
      return module;
    }

    /**
     * \brief Creates an ALModule.
     *
     *        An ALModule has a name, and is registered in a broker,
     *        so that its methods can be called by other modules,
     *        via a proxy constructed with module's name.
     * \param pBroker Pointer to a broker
     * \param pName The name for the new module. This is used as the
     * prefix for all method calls e.g. MyModule.myMethod()
     */
    ALModule(boost::shared_ptr<ALBroker> pBroker, const std::string& pName);

    /** \brief Destructor */
    virtual ~ALModule();

    /**
     * \brief Called by the broker webpage to detail the module.
     * This can be overriden to provide information specific to
     * your module. The default is an empty page.
     * \return "<html><body></body></html>"
     */
    virtual std::string httpGet();

    /**
     * \brief Stops a module's method using the ID given returned
     * by a 'post' call. Module authors are encouraged to implement
     * this if they have long running methods that they wish to
     * allow users to interrupt.
     *
     * \warning Module has to overload stop method
     *          or an exception will be raised.
     * \param taskId The id of the method that was returned by 'post'
     */
    virtual void stop(const int &taskId);

    /**
     * \brief Check if the user call stop.
     * \param taskId The id of the method that was returned by 'post'
     * \return true if used call stop, false otherwise
     */
    bool isStopRequired(const int &taskId = -1);

    /**
     * \brief Waits until the end of a long running method using the ID that was
           returned from a method started with 'post'
     * \param taskId The id of the method that was returned by 'post'
     * \param timeout The wait timeout period in ms. If 0 wait indefinately.
     * \return true if the timeout period expired, false otherwise
     */
    bool wait(const int &taskId, const int &timeout);

    /**
     * \brief Determines if the method created with a 'post' is still running.
     * \param taskId The id of the method that was returned by 'post'
     * \return true if the method is still running, false otherwise
     */
    bool isRunning(const int &taskId);

    /**
     * \brief Return unique ID if method call.
     *
     * Useful to check for instance if user asked your method to stop.
     * First get ID with getMethodID, then call isRequireStop
     * \return Method's ID
     */
    int getMethodID(void);

    /**
     * \brief Check if the module is pcalled.
     * \return true if pcalled, false otherwise
     */
    bool isPCalled();


    /**
     * \brief Exit the module and unregister it.
     */
    virtual void exit();

    /**
     * \brief deprecated
     *
     *        Find the the right module corresponding to the task
     *        and call the stop method.
     *        Use ProxyModule.stop(...) for remote/local compatibility
     * \param pIDTask task's ID
     * \deprecated
     */
    QI_API_DEPRECATED void functionStop(int pIDTask);

    /**
     * \brief It will be called at every module creation, user can overload it.
     */
    virtual void init(void) {}
  };
}

#endif  // _LIBALCOMMON_ALCOMMON_ALMODULE_H_
