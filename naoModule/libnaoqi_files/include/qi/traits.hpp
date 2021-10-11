#pragma once
/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#ifndef  _LIBQI_TRAITS_HPP_
# define _LIBQI_TRAITS_HPP_

#include <boost/noncopyable.hpp>

namespace boost
{
  // forward-declare the trait to avoid an include
  template<typename T1, typename T2> struct is_base_of;
}
namespace qi
{
  /// Detect if a type is using boost::noncopyable or QI_DISALLOW_COPY_AND_ASSIGN
  template<typename T> struct IsClonable
  {
    typedef char yes[1];
    typedef char no[2];
    template <typename C>
    static no& test(typename C::_qi_not_clonable*);

    template <typename>
    static yes& test(...);

    static const bool value = sizeof(test<T>(0)) == sizeof(yes)
    && ! boost::is_base_of<boost::noncopyable, T>::value;
  };

  ///@return true if T inherits from boost::noncopyable or uses QI_DISALLOW_COPY_AND_ASSIGN
  template<typename T> bool isClonable()
  {
    return IsClonable<T>::value;
  }

  template<typename T> bool isClonable(T*)
  {
    return IsClonable<T>::value;
  }

  namespace details
  {
    template<typename T> void newAndAssign(T** ptr)
    {
      *ptr = new T();
    }
  }
}


#endif
