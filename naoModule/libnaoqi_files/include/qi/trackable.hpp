#pragma once
/*
 * Copyright (c) 2013 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#ifndef _QI_TRACKABLE_HPP_
#define _QI_TRACKABLE_HPP_

#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/function.hpp>

#include <qi/log.hpp>

namespace qi
{

  /// Common base class to templates Trackable for compile-time detection.
  class TrackableBase {};

  /** Object tracking by blocking destruction while shared pointers are present.
  *
  * Inherit from Trackable to allow a form of tracking that blocks destruction
  * while shared pointers are held. This allows using your class without a
  * shared_ptr wrapper.
  *
  * @warning when inheriting from this class, you *must* invoke the destroy()
  * method from your destructor, before any operation that puts your object in
  * an invalid state.
  *
  * @warning since destroy() blocks until all shared pointers are destroyed,
  * deadlocks may occur if used improperly.
  *
  */
  template<typename T>
  class Trackable: public TrackableBase
  {
  public:
    Trackable(T* ptr);
    ~Trackable();

    /** @return a shared_ptr that will block destruction (call to destroy() until
    * it is released, or an empty shared_ptr if destroy was already called.
    */
    boost::shared_ptr<T> lock();

    /** @return a weak_ptr from this. While a shared_ptr exists from this weak_ptr,
    * a call to destroy will block()
    *
    */
    boost::weak_ptr<T>   weakPtr();

    /** Blocks until destroy() is called and all shared_ptr built from weak_ptr()
    *  are deleted.
    */
    void wait();
  protected:
    /** *Must* be called by parent class destructor, first thing.
    * Can block until lock holders terminate
    */
    void destroy();
  private:
    void _destroyed();

    boost::shared_ptr<T>      _ptr;
    boost::condition_variable _cond;
    boost::mutex              _mutex;
    bool                      _wasDestroyed;
  };

  class QI_API PointerLockException: public std::exception
  {
  public:
    virtual const char* what() const throw()
    {
      return "Pointer Lock failed";
    }
  };

#ifdef DOXYGEN
  /** Bind a set of arguments or placeholders to a function.
  *
  * Handles first function argument of kind boost::weak_ptr and qi::Trackable:
  * will try to lock and throw qi::PointerLockException in case of failure
  */
  template<typename RF, typename AF> boost::function<RF> bind(const AF& fun, ...);
#endif

  /** Wrap given function \p f with a tracking check on \p arg0, which must
  * be a weak pointer or a Trackable instance.
  * @return a function that, when called:
  *   - If lock can be acquired, calls \p f
  *   - Else throws qi::PointerLockException
  */
  template<typename F, typename ARG0>
  boost::function<F> track(const boost::function<F>& f, const ARG0& arg0);
  template<typename F, typename ARG0>
  boost::function<F> trackWithFallback(boost::function<void()> onFail,
      const boost::function<F>& f, const ARG0& arg0);
}

#include <qi/details/trackable.hxx>
#endif  // _QI_TRACKABLE_HPP_
