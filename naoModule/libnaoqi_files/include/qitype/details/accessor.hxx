#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_ACCESSOR_HXX_
#define _QITYPE_DETAILS_ACCESSOR_HXX_

#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>

namespace qi
{
  /** Traits and functions to factor code taking any accessor as argument.
  * Supports member function, member object, and free-function
  */
  namespace detail
  {
    template<typename T, typename Void = void> struct Accessor
    {
      typedef boost::false_type is_accessor;
    };
    template<typename C, typename T> struct AccessorBase
    {
      typedef boost::true_type is_accessor;
      typedef typename boost::remove_const<T>::type value_type;
      typedef C class_type;
    };
    // we must explicitely check for is_member_object_pointer because T C::*
    // can match functions also even if it may not make sense
    template<typename C, typename T> struct Accessor<T C::*, typename boost::enable_if<typename boost::is_member_object_pointer<T C::*> >::type >
    : public AccessorBase<C, T>
    {
      typedef T C::* type;
      static T& access(C* instance, type acc)
      {
        return *instance.*acc;
      }
    };
    template<typename C, typename T> struct Accessor<T& (C::*)()>
    : public AccessorBase<C, T>
    {
      typedef T& (C::*type)();
      static T& access(C* instance, type acc)
      {
        return (*instance.*acc)();
      }
    };
    template<typename C, typename T> struct Accessor<T& (C::*)() const>
    : public AccessorBase<C, T>
    {
      typedef T& (C::*type)() const;
      static T& access(C* instance, type acc)
      {
        return (*instance.*acc)();
      }
    };
    template<typename C, typename T> struct Accessor<T& (*)(C*)>
    : public AccessorBase<C, T>
    {
      typedef T& (*type)(C*);
      static T& access(C* instance, type acc)
      {
        return acc(instance);
      }
    };
  }
}

#endif  // _QITYPE_DETAILS_ACCESSOR_HXX_


