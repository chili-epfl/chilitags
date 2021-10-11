#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_HASLESS_HXX_
#define _QITYPE_DETAILS_HASLESS_HXX_

#include <boost/type_traits/has_less.hpp>

namespace qi {
  namespace detail {

    template<typename T>
    struct HasLessGuard;

    // boost::has_less gives true for a vector<F> even if has_less<F> gives false
    template<typename T>
    struct HasLess
    {
      static const bool value = boost::has_less<T, T>::value;
    };

    template<typename T>
    struct HasLess<std::vector<T> >
    {
      static const bool value = HasLessGuard<T>::value;
    };

    template<typename T>
    struct HasLess<std::list<T> >
    {
      static const bool value = HasLessGuard<T>::value;
    };

    template<typename K, typename V>
    struct HasLess<std::map<K, V> >
    {
      static const bool value = HasLessGuard<K>::value
        && HasLessGuard<V>::value;
    };

    template<typename A, typename B>
    struct HasLess<std::pair<A, B> >
    {
      static const bool value = HasLessGuard<A>::value
        && HasLessGuard<B>::value;
    };

    //boost::has_less fails for member function pointer, gard
    template<typename T, bool v>
    struct HasLessSwitch
    {};

    template<typename T>
    struct HasLessSwitch<T, false>
    {
      static const bool value = false;
    };

    template<typename T> struct HasLessSwitch<T, true>
    {
      static const bool value = HasLess<T>::value;
    };

    template<typename T>
    struct HasLessGuard
    {
      static const bool switchVal =
          boost::is_member_function_pointer<T>::value
          || boost::is_function<T>::value
          || boost::is_function<typename boost::remove_pointer<T>::type>::value
          || boost::is_member_pointer<T>::value;
      static const bool value = HasLessSwitch<T, !switchVal>::value;

    };


    template<typename T, bool b>
    struct LessHelper
    {};

    template<typename T>
    struct LessHelper<T, true>
    {
      bool operator()(T* a, T* b) { return *a<*b;}
    };

    template<typename T>
    struct LessHelper<T, false>
    {
      bool operator()(T*a, T*b) { return a<b;}
    };

    template<typename T>
    struct Less: public LessHelper<T, HasLessGuard<T>::value>
    {};
  }
}

#endif  // _QITYPE_DETAILS_HASLESS_HXX_
