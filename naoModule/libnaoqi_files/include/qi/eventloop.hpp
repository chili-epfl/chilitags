#pragma once
/*
**  Copyright (C) 2012 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QI_EVENTLOOP_HPP_
#define _QI_EVENTLOOP_HPP_

#ifdef _MSC_VER
#  pragma warning( disable: 4503 ) // decorated name length
#endif

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include <qi/types.hpp>
#include <qi/api.hpp>

#ifdef _MSC_VER
#  pragma warning( push )
#  pragma warning( disable: 4251 )
#endif

namespace boost {
  namespace asio {
    class io_service;
}}

namespace qi
{
  template<typename T> class Future;

  class EventLoopPrivate;
  class QI_API EventLoop
  {
  public:
    /** Create a new eventLoop.
     * You must then call either start(), run() or startThreadPool() to start event processing.
    */
    EventLoop(const std::string& name = "eventloop");
    ~EventLoop();
    /// Return true if current thread is the event loop thread.
    bool isInEventLoopThread();
    /// Start in threaded mode
    void start(int nthreads = 0);
    /// Start in thread-pool mode: each asyncCall() will be run in parallel
    void startThreadPool(int minWorkers=-1, int maxWorkers=-1, int minIdleWorkers=-1, int maxIdleWorkers=-1);
    /// Wait for run thread to terminate
    void join();
    /// Ask main loop to terminate
    void stop();
    /// Run main loop in current thread.
    void run();
    /// Set callback to be called in case of a deadlock detection
    void setEmergencyCallback(boost::function<void()> cb);

    /// Set the maximum number of threads in the pool
    void setMaxThreads(unsigned int max);

    // Internal function
    void *nativeHandle();

    /// @{
    /** Call given function once after given delay in microseconds.
     * @return a canceleable future
     */

    template<typename R>
    Future<R> async(boost::function<R()> callback, uint64_t usDelay=0);
    Future<void> async(boost::function<void ()> callback, uint64_t usDelay=0);

    /// @}

    /// Similar to async() but without cancelation or notification
    void post(const boost::function<void ()>& callback, uint64_t usDelay=0);

    /** Monitor event loop to detect deadlocks.
     @param helper an other event loop used for monitoring
     @param maxUsDelay maximum expected delay between an async() and its execution
     @return a canceleable future. Invoke cancel() to terminate monitoring.
            In case an async() call does not execute in time, the
            future's error will be set.
    */
    Future<void> monitorEventLoop(EventLoop* helper, uint64_t maxUsDelay);

    EventLoopPrivate *_p;
    std::string       _name;
  };

  /// Return the global eventloop, created on demand on first call.
  QI_API EventLoop* getEventLoop();

  /// Start the eventloop with nthread threads. No-op if already started.
  QI_API void startEventLoop(int nthread);

  /// Return the io_service used by the global event loop
  QI_API boost::asio::io_service& getIoService();

  /// Compat
  /// Return a default event loop for network operations.
  QI_API QI_API_DEPRECATED EventLoop* getDefaultNetworkEventLoop();
  /// Return a default context for other uses.
  QI_API QI_API_DEPRECATED EventLoop* getDefaultObjectEventLoop();
  /// Return a default thread pool context
  QI_API QI_API_DEPRECATED EventLoop* getDefaultThreadPoolEventLoop();

  namespace detail {
    /* when throw this thread will stop a thread of the eventloop
     */
    class TerminateThread {
    };
  };
}

#ifdef _MSC_VER
#  pragma warning( pop )
#endif

#include <qi/details/eventloop.hxx>
#endif  // _QI_EVENTLOOP_HPP_
