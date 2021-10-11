#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_ANYVALUE_HXX_
#define _QITYPE_DETAILS_ANYVALUE_HXX_

#include <cmath>

#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <qitype/details/anyiterator.hpp>
#include <qitype/details/anyreference.hpp>

namespace qi {

  template<>
  class TypeImpl<AnyValue>: public DynamicTypeInterface
  {
  public:
    virtual AnyReference get(void* storage)
    {
      AnyValue* ptr = (AnyValue*)ptrFromStorage(&storage);
      return ptr->asReference();
    }

    virtual void set(void** storage, AnyReference src)
    {
      AnyValue* val = (AnyValue*)ptrFromStorage(storage);
      val->reset(src, true, true);
    }

    // Default cloner will do just right since AnyValue is by-value.
    typedef DefaultTypeImplMethods<AnyValue, TypeByPointerPOD<AnyValue> > Methods;
    _QI_BOUNCE_TYPE_METHODS(Methods);
  };

  inline AnyValue
  AnyValue::makeTuple(const AnyReferenceVector& values)
  {
    return AnyValue(makeGenericTuple(values), false, true);
  }

  inline AnyValue
  AnyValue::makeTupleFromValue(const AutoAnyReference& v0,
                               const AutoAnyReference& v1,
                               const AutoAnyReference& v2,
                               const AutoAnyReference& v3,
                               const AutoAnyReference& v4,
                               const AutoAnyReference& v5,
                               const AutoAnyReference& v6,
                               const AutoAnyReference& v7,
                               const AutoAnyReference& v8,
                               const AutoAnyReference& v9)
  {
    const AnyReference* vect[10] = { &v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9 };
    AnyReferenceVector arv;

    for (unsigned int i = 0; i < 10; ++i) {
      if (!vect[i]->isValid())
        break;
      arv.push_back(*vect[i]);
    }
    return AnyValue(makeGenericTuple(arv), false, true);
  }


  template<typename T>
  AnyValue AnyValue::makeList(const AnyReferenceVector& values)
  {
    AnyValue res = make<std::vector<T> >();
    for (unsigned i=0; i<values.size(); ++i)
      res.append(values[i].to<T>());
    return res;
  }
  inline
  AnyValue AnyValue::makeGenericList(const AnyReferenceVector& values)
  {
    return makeList<AnyValue>(values);
  }
  template<typename K, typename V>
  AnyValue AnyValue::makeMap(const std::map<AnyReference, AnyReference>& values)
  {
    AnyValue res = make<std::map<K, V> >();
    std::map<AnyReference, AnyReference>::const_iterator it;
    for(it = values.begin(); it != values.end(); ++it)
      res.insert(it->first.to<K>(), it->second.to<V>());
    return res;
  }

  inline
  AnyValue AnyValue::makeGenericMap(const std::map<AnyReference, AnyReference>& values)
  {
    return makeMap<AnyValue, AnyValue>(values);
  }

  inline AnyValue::AnyValue()
  : _allocated(false)
  {}


  inline AnyValue::AnyValue(const AnyValue& b)
  : _allocated(false)
  {
    *this = b;
  }

  inline AnyValue::AnyValue(qi::TypeInterface *type)
    : AnyReferenceBase(type)
    , _allocated(true)
  {
  }

  inline AnyValue::AnyValue(const AnyReference& b, bool copy, bool free)
  : _allocated(false)
  {
    reset(b, copy, free);
  }

  inline AnyValue::AnyValue(const AutoAnyReference& b)
  : _allocated(false)
  {
    reset(b);
  }

  template<typename T>
  AnyValue AnyValue::make()
  {
    return AnyValue(AnyReference(typeOf<T>()), false, true);
  }

  inline void AnyValue::operator=(const AnyValue& b)
  {
    reset(b.asReference(), true, true);
  }

  inline void AnyValue::operator=(const AnyReference& b)
  {
    reset(b, true, true);
  }

  inline void AnyValue::reset(const AnyReference& b)
  {
    reset(b, true, true);
  }

  inline void AnyValue::reset(const AnyReference& b, bool copy, bool free)
  {
    reset();
    *(AnyReferenceBase*)this = b;
    _allocated = free;
    if (copy)
      *(AnyReferenceBase*)this = clone();
  }

  inline void AnyValue::reset()
  {
    if (_allocated)
      AnyReferenceBase::destroy();
    _type = 0;
    _value = 0;
  }

  inline void AnyValue::reset(qi::TypeInterface *ttype)
  {
    reset();
    _allocated = true;
    _type = ttype;
    _value = _type->initializeStorage();
  }

  inline AnyValue::~AnyValue()
  {
    reset();
  }

  inline void AnyValue::swap(AnyValue& b)
  {
    std::swap((::qi::AnyReference&)*this, (::qi::AnyReference&)b);
    std::swap(_allocated, b._allocated);
  }


  inline bool operator != (const AnyValue& a, const AnyValue& b)
  {
    return !(a==b);
  }



  /// FutureValueConverter implementation for AnyReference -> T
  /// that destroys the value
  template<>
  struct FutureValueConverterTakeAnyReference<AnyValue>
  {
    void operator()(const AnyReference& in, AnyValue& out)
    {
      out.reset(in, false, true);
    }
  };

  template <typename T1, typename T2>
  struct FutureValueConverter;

  template <typename T>
  struct FutureValueConverter<T, qi::AnyValue>
  {
    void operator()(const T& in, qi::AnyValue &out)
    {
      out = qi::AnyValue::from(in);
    }
  };

  template <>
  struct FutureValueConverter<void, qi::AnyValue>
  {
    void operator()(void *in, qi::AnyValue &out)
    {
      out = qi::AnyValue::make<void>();
    }
  };

  inline AnyReferenceVector asAnyReferenceVector(const AnyValueVector& vect) {
    AnyReferenceVector result;
    result.resize(vect.size());
    for (unsigned int i = 0; i < vect.size(); ++i) {
      result[i] = vect[i].asReference();
    }
    return result;
  }

}

namespace std
{
  inline void swap(::qi::AnyValue& a, ::qi::AnyValue& b)
  {
    a.swap(b);
  }
}


#endif  // _QITYPE_DETAILS_ANYVALUE_HXX_


