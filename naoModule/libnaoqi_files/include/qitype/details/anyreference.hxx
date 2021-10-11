#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_ANYREFERENCE_HXX_
#define _QITYPE_DETAILS_ANYREFERENCE_HXX_

#include <cmath>
#include <stdexcept>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <qi/atomic.hpp>
#include <qitype/details/typeinterface.hpp>

namespace qi {

  inline AutoAnyReference::AutoAnyReference()
  {
  }

  inline AutoAnyReference::AutoAnyReference(const AutoAnyReference& b)
  {
    _value = b._value;
    _type = b._type;
  }

  template<typename T>
  AutoAnyReference::AutoAnyReference(const T& ptr)
  {
    *(AnyReference*)this = AnyReference::from(ptr);
  }

//  inline
//  AnyReferenceBase& AnyReferenceBase::operator=(const AutoAnyReference& b)
//  {
//    update(b);
//    return *this;
//  }

  inline
  AnyReference AnyReferenceBase::clone() const
  {
    AnyReference res;
    res._type  = _type;
    res._value = _type ? res._type->clone(_value) : 0;
    return res;
  }

  inline qi::Signature AnyReferenceBase::signature(bool resolveDynamic) const
  {
    if (!_type)
      return qi::Signature();
    else
      return _type->signature(_value, resolveDynamic);
  }

  inline void AnyReferenceBase::destroy()
  {
    if (_type)
      _type->destroy(_value);
    _value = _type = 0;
  }

  inline AnyReferenceBase::AnyReferenceBase()
    : _type(0)
    , _value(0)
  {
  }

  inline AnyReferenceBase::AnyReferenceBase(TypeInterface* type)
    : _type(type)
    , _value(type->initializeStorage())
  {
  }

  template<typename T>
  AnyReference AnyReferenceBase::fromPtr(const T* ptr)
  {
    static TypeInterface* t = 0;
    if (!t)
      t = typeOf<typename boost::remove_const<T>::type>();
    void *value = t->initializeStorage(const_cast<void*>((const void*)ptr));
    return AnyReference(t, value);
  }

  template<typename T>
  AnyReference AnyReferenceBase::from(const T& ptr)
  {
    AnyReference ref;
    static TypeInterface* t = 0;
    QI_ONCE( t = typeOf<typename boost::remove_const<T>::type>());
    return AnyReference(t, t->initializeStorage(const_cast<void*>((const void*)&ptr)));
  }

  inline TypeKind AnyReferenceBase::kind() const
  {
    if (!_type)
      throw std::runtime_error("Can't take the kind of an invalid value");
    else
      return _type->kind();
  }


  // Kind -> handler Type (IntTypeInterface, ListTypeInterface...)  accessor

  class KindNotConvertible;

  template<TypeKind T> struct TypeOfKind
  {
    typedef KindNotConvertible type;
  };

#define TYPE_OF_KIND(k, t) template<> struct TypeOfKind<k> { typedef t type;}


  TYPE_OF_KIND(TypeKind_Int, IntTypeInterface);
  TYPE_OF_KIND(TypeKind_Float, FloatTypeInterface);
  TYPE_OF_KIND(TypeKind_String, StringTypeInterface);

#undef TYPE_OF_KIND


  // Type -> Kind  accessor

  namespace detail
  {
    struct Nothing {};
    template<TypeKind k> struct MakeKind
    {
      static const TypeKind value = k;
    };

    template<typename C, typename T, typename F> struct IfElse
    {
    };

    template<typename T, typename F> struct IfElse<boost::true_type, T, F>
    {
      typedef T type;
    };

    template<typename T, typename F> struct IfElse<boost::false_type, T, F>
    {
      typedef F type;
    };

  }

#define IF(cond, type) \
  public detail::IfElse<cond, typename detail::MakeKind<type>, detail::Nothing>::type

  template<typename T> struct KindOfType
      : IF(typename boost::is_integral<T>::type, TypeKind_Int)
  , IF(typename boost::is_floating_point<T>::type, TypeKind_Float)
  {
  };

#undef IF

  namespace detail {

    // Optimized AnyReferenceBase::as<T> for direct access to a subType getter
    template<typename T, TypeKind k>
    inline T valueAs(const AnyReferenceBase& v)
    {
      if (v.kind() == k)
        return static_cast<T>(
          static_cast<typename TypeOfKind<k>::type* const>(v.type())->get(v.rawValue()));
      // Fallback to default which will attempt a full conversion.
      return v.to<T>();
    }
  }

  template<typename T>
  inline T* AnyReferenceBase::ptr(bool check)
  {
    if (!_type || (check && typeOf<T>()->info() != _type->info()))
      return 0;
    else
      return (T*)_type->ptrFromStorage(&_value);
  }

  template<typename T>
  inline T& AnyReferenceBase::as()
  {
    T* p = ptr<T>(true);
    if (!p)
      throw std::runtime_error("Type mismatch");
    return *p;
  }

  template<typename T>
  inline T AnyReferenceBase::to(const T&) const
  {
    return to<T>();
  }

  namespace detail
  {
    QI_NORETURN QITYPE_API void throwConversionFailure(TypeInterface* from, TypeInterface* to);
  }

  template<typename T>
  inline T AnyReferenceBase::to() const
  {
    TypeInterface* targetType = typeOf<T>();
    std::pair<AnyReference, bool> conv = convert(targetType);
    if (!conv.first._type)
    {
      detail::throwConversionFailure(_type, targetType);
    }
    T result = *conv.first.ptr<T>(false);
    if (conv.second)
      conv.first.destroy();
    return result;
  }

  template<>
  inline void AnyReferenceBase::to<void>() const
  {
    return;
  }

  inline bool    AnyReferenceBase::isValid() const {
    return _type != 0;
  }

  inline bool    AnyReferenceBase::isValue() const {
    return _type != 0 && _type->info() != typeOf<void>()->info();
  }

  inline int64_t AnyReferenceBase::toInt() const
  {
    return detail::valueAs<int64_t, TypeKind_Int>(*this);
  }

  inline uint64_t AnyReferenceBase::toUInt() const
  {
    return detail::valueAs<uint64_t, TypeKind_Int>(*this);
  }

  inline float AnyReferenceBase::toFloat() const
  {
    return detail::valueAs<float, TypeKind_Float>(*this);
  }

  inline double AnyReferenceBase::toDouble() const
  {
    return detail::valueAs<double, TypeKind_Float>(*this);
  }


  inline std::string AnyReferenceBase::toString() const
  {
    return to<std::string>();
  }

  template<typename T>
  std::vector<T>
  AnyReferenceBase::toList() const
  {
    return to<std::vector<T> >();
  }

  template<typename K, typename V>
  std::map<K, V>
  AnyReferenceBase::toMap() const
  {
    return to<std::map<K, V> >();
  }


  inline AnyReferenceVector
  AnyReferenceBase::asListValuePtr()
  {
    return asTupleValuePtr();
  }


  namespace detail
  {
    /** This class can be used to convert the return value of an arbitrary function
  * into a AnyReference. It handles functions returning void.
  *
  *  Usage:
  *    ValueCopy val;
  *    val(), functionCall(arg);
  *
  *  in val(), parenthesis are useful to avoid compiler warning "val not used" when handling void.
  */
    class AnyReferenceCopy: public AnyReference
    {
    public:
      AnyReferenceCopy &operator()() { return *this; }
    };

    template<typename T> void operator,(AnyReferenceCopy& g, const T& any)
    {
      *(AnyReference*)&g = AnyReference::from(any).clone();
    }
  }

  template<typename T>
  void AnyReferenceBase::set(const T& v)
  {
    update(AnyReferenceBase::from(v));
   }

  inline void AnyReferenceBase::setFloat(float v)
  {
    setDouble(static_cast<double>(v));
  }

  template<typename E, typename K>
  E& AnyReferenceBase::element(const K& key)
  {
    return (*this)[key].template as<E>();
  }

  template<typename K>
  AnyReference AnyReferenceBase::operator[](const K& key)
  {
    return _element(AnyReferenceBase::from(key), true);
  }

  template<typename T>
  void AnyReferenceBase::append(const T& element)
  {
    _append(AnyReference::from(element));
  }

  template<typename K, typename V>
  void AnyReferenceBase::insert(const K& key, const V& val)
  {
    _insert(AnyReference::from(key), AnyReference::from(val));
  }

  template<typename K>
  AnyReference AnyReferenceBase::find(const K& key)
  {
    return _element(AnyReference::from(key), false);
  }

  inline bool operator != (const AnyReference& a, const AnyReference& b)
  {
    return !(a==b);
  }

  /// FutureValueConverter implementation for AnyReference -> T
  /// that destroys the value
  template <typename T>
  struct FutureValueConverterTakeAnyReference
  {
    void operator()(const AnyReference& in, T& out)
    {
      try {
        out = in.to<T>();
      }
      catch (const std::exception& e)
      {
        const_cast<AnyReference&>(in).destroy();
        throw e;
      }
      const_cast<AnyReference&>(in).destroy();
    }
  };

}

#endif  // _QITYPE_DETAILS_ANYREFERENCE_HXX_

