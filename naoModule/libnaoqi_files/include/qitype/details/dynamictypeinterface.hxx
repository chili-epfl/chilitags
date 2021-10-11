#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_TYPEDYNAMIC_HXX_
#define _QITYPE_DETAILS_TYPEDYNAMIC_HXX_

#include <boost/any.hpp>

namespace qi {
  //any
  template<>
  class TypeImpl<boost::any>: public DynamicTypeInterface
  {
  public:
    AnyReference get(void* storage)
    {
      qiLogVerbose("qitype.impl") << "get on boost::any not implemented";
      return AnyReference();
    };

    void set(void** storage, AnyReference source)
    {
      qiLogVerbose("qitype.impl") << "set on boost::any not implemented";
    }

    typedef DefaultTypeImplMethods<boost::any, TypeByPointerPOD<boost::any> > Methods;
    _QI_BOUNCE_TYPE_METHODS(Methods);
  };
}

#endif  // _QITYPE_DETAILS_TYPEDYNAMIC_HXX_
