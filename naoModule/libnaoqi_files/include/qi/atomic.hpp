#pragma once
/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#ifndef _QI_ATOMIC_HPP_
#define _QI_ATOMIC_HPP_

#ifdef _MSC_VER
# include <windows.h>
# include <intrin.h>

extern "C" long __cdecl _InterlockedIncrement(long volatile *);
extern "C" long __cdecl _InterlockedDecrement(long volatile *);

# pragma intrinsic(_InterlockedIncrement)
# pragma intrinsic(_InterlockedDecrement)

#endif

#include <boost/static_assert.hpp>

#include <qi/config.hpp>
#include <qi/macro.hpp>

namespace qi
{
  inline long testAndSet(long* cond)
  {
#if defined __GNUC__
    return __sync_bool_compare_and_swap(cond, 0, 1);
#elif defined _MSC_VER
    return 1 - InterlockedCompareExchange(cond, 1, 0);
#else
  #error "Unknown platform, testAndSet not implemented"
#endif
  }

  /* /!\ WARNING
  * The 'volatile' is needed even though we use atomic compiler builtins.
  * Without the volatile, a thread doing
  *    while (!setIfEquals(1,1))
  * Is never unstuck by a thread doing
  *    setIfEquals(0,1)
  *
  * AtomicBase has public member so that it can be initialized at
  * static-initialization time (to make thread-safe static initialization inside
  * functions)
  */
  template <typename T>
  struct AtomicBase
  {
  public:


    /* prefix operators */
    inline T operator++();
    inline T operator--();
    inline AtomicBase<T>& operator=(T value);
    /** If value is \p testValue, replace it with \p setValue.
     * \return true if swap was performed
     */
    inline bool setIfEquals(T testValue, T setValue);

    inline T swap(T value);

    inline T operator*() const
    {
      return _value;
    }

  public:
    BOOST_STATIC_ASSERT_MSG(sizeof(T) == sizeof(int), "qi::Atomic is only supprted for int-like types");

    volatile
#ifdef _MSC_VER
    long
#else
    T
#endif
       _value;
  };

  template <typename T>
  class Atomic: public AtomicBase<T>
  {
  public:
    Atomic()
    {
      this->_value = 0;
    }

    Atomic(T value)
    {
      this->_value = value;
    }
  };
#ifdef __GNUC__
    template <typename T>
    inline T AtomicBase<T>::operator++()
    {
      return __sync_add_and_fetch(&_value, 1);
    }

    template <typename T>
    inline T AtomicBase<T>::operator--()
    {
      return __sync_sub_and_fetch(&_value, 1);
    }

    template <typename T>
    inline AtomicBase<T>& AtomicBase<T>::operator=(T value)
    {
      __sync_lock_test_and_set(&_value, value);
      return *this;
    }

    template <typename T>
    inline T AtomicBase<T>::swap(T value)
    {
      return __sync_lock_test_and_set(&_value, value);
    }
    template <typename T>
    inline bool AtomicBase<T>::setIfEquals(T testValue, T setValue)
    {
      return __sync_bool_compare_and_swap(&_value, testValue, setValue);
    }
#endif

#ifdef _MSC_VER

  template <>
  inline int AtomicBase<int>::operator++()
  {
    return _InterlockedIncrement(&_value);
  }

  template <>
  inline int AtomicBase<int>::operator--()
  {
    return _InterlockedDecrement(&_value);
  }

  template<>
  inline AtomicBase<int>& AtomicBase<int>::operator=(int value)
  {
    InterlockedExchange(&_value, value);
    return *this;
  }

  template<>
  inline int AtomicBase<int>::swap(int value)
  {
    return InterlockedExchange(&_value, value);
  }

  template <>
  inline bool AtomicBase<int>::setIfEquals(int testValue, int setValue)
  {
    return _InterlockedCompareExchange(&_value, setValue, testValue) == testValue;
  }

  template <>
  inline unsigned int AtomicBase<unsigned int>::operator++()
  {
    return _InterlockedIncrement(&_value);
  }

  template <>
  inline unsigned int AtomicBase<unsigned int>::operator--()
  {
    return _InterlockedDecrement(&_value);
  }

  template<>
  inline AtomicBase<unsigned int>& AtomicBase<unsigned int>::operator=(unsigned int value)
  {
    InterlockedExchange(&_value, value);
    return *this;
  }

  template<>
  inline unsigned int AtomicBase<unsigned int>::swap(unsigned int value)
  {
    return InterlockedExchange(&_value, value);
  }

  template <>
  inline bool AtomicBase<unsigned int>::setIfEquals(unsigned int testValue, unsigned int setValue)
  {
    return _InterlockedCompareExchange(&_value, setValue, testValue) == testValue;
  }
#endif

}

#define _QI_INSTANCIATE(_, a, elem) ::qi::details::newAndAssign(&elem);

/* The code below relies on the fact that initialisation of the qi::Atomic
* can happen at static initialization time, and that proper memory barriers
* are setup by its ++, swap and get operations.
 */
/** Accept a list of pointers (expected to be static function variables)
 *  and new them once in a thrad-safe manner.
 *  Implementation aims for minimal overhead when initialization is done.
 */
#define QI_THREADSAFE_NEW(...)  \
 QI_ONCE(QI_VAARGS_APPLY(_QI_INSTANCIATE, _, __VA_ARGS__);)

/// Execute code once, parallel calls are blocked until code finishes.
#define QI_ONCE(code) \
 static qi::AtomicBase<int> QI_UNIQ_DEF(atomic_guard_a) = {0}; \
 static qi::AtomicBase<int> QI_UNIQ_DEF(atomic_guard_b) = {0}; \
 while (!QI_UNIQ_DEF(atomic_guard_a).setIfEquals(1, 1))       \
 {                                                           \
   bool tok = QI_UNIQ_DEF(atomic_guard_b).setIfEquals(0,1);  \
   if (tok)                                                  \
   {                                                    \
     code;                                              \
     ++QI_UNIQ_DEF(atomic_guard_a);                     \
   }                                                    \
 }


#endif  // _QI_ATOMIC_HPP_
