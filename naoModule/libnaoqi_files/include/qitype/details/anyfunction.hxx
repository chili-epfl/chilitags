#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_ANYFUNCTION_HXX_
#define _QITYPE_DETAILS_ANYFUNCTION_HXX_

#include <qitype/details/anyvalue.hpp>
#include <qitype/details/bindtype.hxx>

namespace qi
{
  inline CallableTypeInterface::CallableTypeInterface()
    : _resultType(0)
  {
  }

  inline TypeInterface* CallableTypeInterface::resultType()
  {
    return _resultType;
  }

  inline const std::vector<TypeInterface*>& CallableTypeInterface::argumentsType()
  {
    return _argumentsType;
  }

  inline AnyReference AnyFunction::operator()(const AnyReferenceVector& args)
  {
    return call(args);
  }

  inline AnyFunction::AnyFunction()
  : type(0), value(0)
  {}

  inline AnyFunction::AnyFunction(const AnyFunction& b)
  {
    type = b.type;
    value = type?type->clone(b.value):0;
    transform = b.transform;
  }

  inline AnyFunction::AnyFunction(FunctionTypeInterface* type, void* value)
    : type(type)
    , value(value)
  {
  }

  inline AnyFunction& AnyFunction::operator=(const AnyFunction& b)
  {
    this->~AnyFunction();
    type = b.type;
    value = type?type->clone(b.value):0;
    transform = b.transform;
    return *this;
  }

  inline AnyFunction::~AnyFunction()
  {
    if (type)
      type->destroy(value);
  }

  inline void AnyFunction::swap(AnyFunction& b)
  {
    std::swap(value, b.value);
    std::swap(type, b.type);
    std::swap(transform, b.transform);
  }

  inline AnyFunction::operator bool() const
  {
    return type != 0;
  }

  inline FunctionTypeInterface* AnyFunction::functionType() const
  {
    return type;
  }


} // namespace qi

namespace std
{
  template<> inline void swap(::qi::AnyFunction& a, ::qi::AnyFunction & b)
  {
    a.swap(b);
  }
}

#endif  // _QITYPE_DETAILS_ANYFUNCTION_HXX_
