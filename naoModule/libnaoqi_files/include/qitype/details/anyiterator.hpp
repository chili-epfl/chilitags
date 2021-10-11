#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_ANYITERATOR_HPP_
#define _QITYPE_DETAILS_ANYITERATOR_HPP_

#include <qitype/api.hpp>
#include <qitype/details/anyvalue.hpp>

namespace qi {

  /** AnyValue with Iterator kind, behaving as a STL-compatible iterator
   */
  class QITYPE_API AnyIterator: public AnyValue
  {
  public:
    typedef AnyReference              value_type;
    typedef AnyReference*             pointer;
    typedef AnyReference&             reference;
    typedef ptrdiff_t                 difference_type;
    typedef std::forward_iterator_tag iterator_category;

    AnyIterator();
    AnyIterator(const AnyReference& p);
    AnyIterator(const AnyValue& v);

    template<typename T>
    AnyIterator(const T& ref);

    /// Iterator pre-increment
    AnyIterator& operator++();
    /// Iterator post-increment
    AnyIterator operator++(int);
    /// Dereference
    AnyReference operator*();
  };

  QITYPE_API bool operator==(const AnyIterator& a, const AnyIterator& b);
  QITYPE_API bool operator!=(const AnyIterator& a, const AnyIterator& b);
}

#include <qitype/details/anyiterator.hxx>

#endif  // _QITYPE_DETAILS_ANYITERATOR_HPP_

