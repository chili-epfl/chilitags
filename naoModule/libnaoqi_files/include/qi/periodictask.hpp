#pragma once
/*
* Copyright (c) Aldebaran Robotics 2013 All Rights Reserved
*/
#ifndef _QI_PERIODICTASK_HPP_
#define _QI_PERIODICTASK_HPP_

#include <string>

#include <boost/function.hpp>
#include <boost/utility.hpp>

#include <qi/atomic.hpp>
#include <qi/future.hpp>
#include <qi/stats.hpp>
#include <qi/trackable.hpp>

namespace qi
{
  struct PeriodicTaskPrivate;
  /** Control a task executed periodically and asynchronously.
  */
  class QI_API PeriodicTask: public boost::noncopyable
  {
  public:
    typedef boost::function<void()> Callback;

    PeriodicTask();

    ~PeriodicTask();

    /// @{
    /** One of the setCallback() functions below must be called before
    *   any other operation. Once set the callback cannot be changed.
    *   If the callback throws, async task will be stopped
    */
    void setCallback(const Callback& cb);
#ifdef DOXYGEN
    template<typename T, typename ARG0> PeriodicTask& setCallback(const T& callable, ARG0 tracked, ...);
#else
    #define genCall(n, ATYPEDECL, ATYPES, ADECL, AUSE, comma) \
    template<typename AF, typename ARG0 comma ATYPEDECL>      \
    inline void setCallback(const AF& fun, const ARG0& arg0 comma ADECL)  \
    {                                                                    \
      setCallback(::qi::bind<void()>(fun, arg0 comma AUSE));             \
    }
    QI_GEN(genCall)
#undef genCall
#endif

    /** Set the call interval in microseconds.
     *  This call will wait until next callback invocation to apply the change.
     *  Use:
     *  task.stop();
     *  task.setUsPeriod()
     *  task.start()
     *  to apply the change immediately.
     */
    void setUsPeriod(qi::int64_t usPeriod);

    /** Start the periodic task at specified period. No effect if already running.
     * @param immediate if true, first schedule of the task will happen with no delay.
     * @warning concurrent calls to start() and stop() will result in undefined behavior.
     */
    void start(bool immediate = true);

    /** Trigger a started periodic task to run right now.
     * Does nothing if the periodic task just ran, is running, starting,
     * stopping or stopped.
     */
    void trigger();

    /** Stop the periodic task. When this function returns, the callback will
    * not be called anymore.
    * Can be called from within the callback function.
    * @warning concurrent calls to start() and stop() will result in undefined behavior.
    */
    void stop();

    /** Request for periodic task to stop asynchronously.
    * Can be safely called from within the callback.
    */
    void asyncStop();

    /** If argument is true, call interval will take into account call duration
    * to maintain the period.
    */
    void compensateCallbackTime(bool compensate);

    /// Set name for debugging and tracking purpose
    void setName(const std::string& name);

    /// @return true if task is running
    bool isRunning() const;

    /** @return whether state is stopping or stopped
     * Can be called from within the callback to know if stop() or asyncStop()
     * was called.
    */
    bool isStopping() const;
  private:
    boost::shared_ptr<PeriodicTaskPrivate> _p;
  };

}
#endif
