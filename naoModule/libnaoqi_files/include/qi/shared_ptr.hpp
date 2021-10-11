#pragma once
/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#ifndef _QI_SHARED_PTR_HPP_
#define _QI_SHARED_PTR_HPP_

#include <qi/atomic.hpp>
#include <qi/log.hpp>

namespace qi
{
  /// Lightweight implementation of shared pointers.
  template <typename T>
  class SharedPtr
  {
  public:
    /// Initialization of the SharedPtr with the pointer it will manage.
    SharedPtr(T *ptr)
      : _ptr(ptr)
      , _refcount(new qi::Atomic<int>(1))
    {
    }

    /// \brief Destruct the shared pointer and the pointer if current SharedPtr
    ///        is the last one to hold the pointer.
    ~SharedPtr()
    {
      if (--(*_refcount) == 0)
      {
        delete _ptr;
        delete _refcount;
      }
    }

    /// Copy shared pointer.
    SharedPtr(const SharedPtr<T> &sp)
    {
      /*
       * Note that this line is racy.
       * If someone is deleting _refcount,
       * it cannot be used below.
       */
      if (++(*sp._refcount) != 1)
      {
        _ptr = sp._ptr;
        _refcount = sp._refcount;
      }
      else
      {

        _ptr = 0;
        _refcount = 0;
        qiLogDebug("qi.log.shared_ptr")
                  << "tried to copy a shared pointer targeted for deletion"
                  << std::endl;
      }
    }

    /// \brief Link current SharedPtr to a new pointer. If old pointer was
    ///        only held by the current SharedPtr, it is freed.
    SharedPtr& operator=(SharedPtr<T> &sp)
    {
      // release the current pointer
      if (--(*_refcount) == 0)
      {
        delete _ptr;
        delete _refcount;
      }
      if (++(*sp._refcount) != 1)
      {
        _ptr = sp._ptr;
        _refcount = sp._refcount;
      }
      else
      {
        qiLogDebug("qi.log.shared_ptr")
                  << "tried to copy a shared pointer targeted for deletion"
                  << std::endl;
      }
      return *this;
    }

    /// Value accessor.
    T &operator*() const
    {
      return *_ptr;
    }

    /// Pointer accessor.
    T *operator->() const
    {
      return _ptr;
    }

  private:
    T                *_ptr;
    qi::Atomic<int> *_refcount;
  };
}

#endif  // _QI_SHARED_PTR_HPP_
