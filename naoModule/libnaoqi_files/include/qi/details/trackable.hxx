#pragma once
/*
 * Copyright (c) 2013 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#ifndef _QI_DETAILS_TRACKABLE_HXX_
#define _QI_DETAILS_TRACKABLE_HXX_

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/function_types/result_type.hpp>

namespace qi
{
  template<typename T>
  inline Trackable<T>::Trackable(T* ptr)
  : _wasDestroyed(false)
  {
    _ptr = boost::shared_ptr<T>(ptr, boost::bind(&Trackable::_destroyed, _1));
  }

  template<typename T>
  inline void Trackable<T>::destroy()
  {
    _ptr.reset();
    wait();
  }

  template<typename T>
  inline void Trackable<T>::wait()
  {
    boost::mutex::scoped_lock lock(_mutex);
    while (!_wasDestroyed)
    {
      _cond.wait(lock);
    }
  }

  template<typename T>
  inline void Trackable<T>::_destroyed()
  {
    // unblock
    boost::mutex::scoped_lock lock(_mutex);
    _wasDestroyed = true;
    _cond.notify_all();
  }

  template<typename T>
  inline Trackable<T>::~Trackable()
  {
    // We expect destroy() to have been called from parent destructor, so from
    // this thread.
    if (!_wasDestroyed)
    {
      qiLogError("qi.Trackable") << "Trackable destroyed without calling destroy()";
      // do it to mitigate the effect, but it's too late
      destroy();
    }
  }

  template<typename T>
  inline boost::shared_ptr<T> Trackable<T>::lock()
  {
    return _ptr;
  }

  template<typename T>
  inline boost::weak_ptr<T> Trackable<T>::weakPtr()
  {
    return boost::weak_ptr<T>(_ptr);
  }

  namespace detail
  {
    // Functor that locks a weak ptr and make a call if successful
    // Generalize on shared_ptr and weak_ptr types in case we ever have
    // other types with their semantics
    template<typename WT, typename ST, typename F>
    class LockAndCall
    {
    public:
      typedef typename boost::function_types::result_type<F>::type Result;
      LockAndCall(const WT& arg, boost::function<F> func, boost::function<void()> onFail)
      : _wptr(arg)
      , _f(func)
      , _onFail(onFail)
      {}

#define genCall(n, ATYPEDECL, ATYPES, ADECL, AUSE, comma) \
     QI_GEN_MAYBE_TEMPLATE_OPEN(comma)                    \
     ATYPEDECL                                            \
     QI_GEN_MAYBE_TEMPLATE_CLOSE(comma)                   \
     Result operator()(ADECL) {                           \
       ST s = _wptr.lock();                               \
       if (s)                                             \
         return _f(AUSE);                                 \
       else                                               \
         if (_onFail)                                     \
           _onFail();                                     \
         else                                             \
           return Result();                               \
      }
      QI_GEN(genCall)
#undef genCall
      WT _wptr;
      boost::function<F> _f;
      boost::function<void()> _onFail;
    };

    template<typename T, bool IS_TRACKABLE> struct BindTransform
    {
      typedef const T& type;
      static type transform(const T& arg)
      {
        return arg;
      }
      template<typename F>
      static boost::function<F> wrap(const T& arg, boost::function<F> func, boost::function<void()> onFail)
      {
        return func;
      }
    };

    template<typename T> struct BindTransform<boost::weak_ptr<T>, false >
    {
      typedef T* type;
      static T* transform(const boost::weak_ptr<T>& arg)
      {
        // Note that we assume that lock if successful always return the same pointer
        // And that if lock fails once, it will fail forever from that point
        return arg.lock().get();
      }
      template<typename F>
      static boost::function<F> wrap(const boost::weak_ptr<T>& arg, boost::function<F> func, boost::function<void()> onFail)
      {
        return LockAndCall<boost::weak_ptr<T>, boost::shared_ptr<T>, F>(arg, func, onFail);
      }
    };

    template<typename T> struct BindTransform<T*, true>
    {
      typedef T* type;
      static T* transform(T* const & arg)
      {
        // Note that we assume that lock if successful always return the same pointer
        return arg;
      }
      template<typename F>
      static boost::function<F> wrap(T*const & arg, boost::function<F> func, boost::function<void()> onFail)
      {
        return LockAndCall<boost::weak_ptr<T>, boost::shared_ptr<T>, F>(arg->weakPtr(), func, onFail);
      }
    };

    inline void throwPointerLockException()
    {
      throw PointerLockException();
    }
  }

#ifndef DOXYGEN
  template<typename RF, typename AF>
  boost::function<RF> bind(const AF& fun)
  {
    return fun;
  }
#define genCall(n, ATYPEDECL, ATYPES, ADECL, AUSE, comma) \
  template<typename RF, typename AF, typename ARG0 comma ATYPEDECL>      \
  boost::function<RF> bind(const AF& fun, const ARG0& arg0 comma ADECL)  \
  {                                                                      \
    typedef typename detail::BindTransform<ARG0, boost::is_base_of<TrackableBase, typename boost::remove_pointer<ARG0>::type>::value> Transform;     \
    typename Transform::type transformed = Transform::transform(arg0);   \
    boost::function<RF> f = boost::bind(fun, transformed comma AUSE);    \
    return Transform::wrap(arg0, f, detail::throwPointerLockException);  \
  }                                                                      \
  template<typename RF, typename AF, typename ARG0 comma ATYPEDECL>      \
  boost::function<RF> bindWithFallback(const boost::function<void()> onFail, const AF& fun, const ARG0& arg0 comma ADECL)  \
  {                                                                      \
    typedef typename detail::BindTransform<ARG0, boost::is_base_of<TrackableBase, typename boost::remove_pointer<ARG0>::type>::value> Transform;     \
    typename Transform::type transformed = Transform::transform(arg0);   \
    boost::function<RF> f = boost::bind(fun, transformed comma AUSE);    \
    return Transform::wrap(arg0, f, onFail);  \
  }
  QI_GEN(genCall)
#undef genCall
#endif // DOXYGEN
  template<typename F, typename ARG0>
  boost::function<F> track(const boost::function<F>& f, const ARG0& arg0)
  {
    typedef typename detail::BindTransform<ARG0, boost::is_base_of<TrackableBase, typename boost::remove_pointer<ARG0>::type>::value> Transform;
    return Transform::wrap(arg0, f, detail::throwPointerLockException);
  }
  template<typename F, typename ARG0>
  boost::function<F> trackWithFallback(boost::function<void()> onFail,
      const boost::function<F>& f, const ARG0& arg0)
  {
    typedef typename detail::BindTransform<ARG0, boost::is_base_of<TrackableBase, typename boost::remove_pointer<ARG0>::type>::value> Transform;
    return Transform::wrap(arg0, f, onFail);
  }
}

#endif  // _QI_DETAILS_TRACKABLE_HXX_
