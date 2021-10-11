#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_GENERICOBJECTBUILDER_HXX_
#define _QITYPE_DETAILS_GENERICOBJECTBUILDER_HXX_

#include <qitype/dynamicobjectbuilder.hpp>
#include <qitype/metamethod.hpp>

namespace qi {

  template <typename FUNCTION_TYPE>
  unsigned int DynamicObjectBuilder::advertiseMethod(const std::string& name,
                                                     FUNCTION_TYPE function,
                                                     const std::string& desc,
                                                     MetaCallType threadingModel)
  {
    MetaMethodBuilder builder;
    AnyFunction f = AnyFunction::from(function).dropFirstArgument();
    builder.setName(name);
    builder.setSignature(f);
    builder.setDescription(desc);
    // throw on error
    return xAdvertiseMethod(builder, f, threadingModel);
  }

  template <typename OBJECT_TYPE, typename METHOD_TYPE>
  inline unsigned int DynamicObjectBuilder::advertiseMethod(const std::string& name,
                                                            OBJECT_TYPE object,
                                                            METHOD_TYPE method,
                                                            const std::string& desc,
                                                            MetaCallType threadingModel)
  {
    MetaMethodBuilder builder;
    AnyFunction f = AnyFunction::from(method, object).dropFirstArgument();
    builder.setName(name);
    builder.setSignature(f);
    builder.setDescription(desc);
    // throw on error
    return xAdvertiseMethod(builder, f, threadingModel);
  }

  template <typename FUNCTION_TYPE>
  inline unsigned int DynamicObjectBuilder::advertiseMethod(MetaMethodBuilder& builder,
                                                            FUNCTION_TYPE function,
                                                            MetaCallType threadingModel)
  {
    AnyFunction f = AnyFunction::from(function).dropFirstArgument();
    builder.setSignature(f);
    // throw on error
    return xAdvertiseMethod(builder, f, threadingModel);
  }

  template <typename OBJECT_TYPE, typename METHOD_TYPE>
  inline unsigned int DynamicObjectBuilder::advertiseMethod(MetaMethodBuilder& builder,
                                                            OBJECT_TYPE object,
                                                            METHOD_TYPE method,
                                                            MetaCallType threadingModel)
  {
    AnyFunction f = AnyFunction::from(method, object).dropFirstArgument();
    builder.setSignature(f);
    // throw on error
    return xAdvertiseMethod(builder, f, threadingModel);
  }

  #define gen(n, ATYPEDECL, ATYPES, ADECL, AUSE, comma) \
  QI_GEN_MAYBE_TEMPLATE_OPEN(comma) ATYPEDECL QI_GEN_MAYBE_TEMPLATE_CLOSE(comma) \
  inline unsigned int DynamicObjectBuilder::advertiseSignal(const std::string& s) \
  { \
    return advertiseSignalF<void(ATYPES)>(s); \
  }

  QI_GEN_RANGE(gen, 8)
  #undef gen

  template <typename T> unsigned int DynamicObjectBuilder::advertiseSignalF(const std::string& name)
  {
    return xAdvertiseSignal(name, detail::FunctionSignature<T>::signature());
  }

  template <typename T> unsigned int DynamicObjectBuilder::advertiseProperty(const std::string& name)
  {
    // we must end up with name event, get_name and set_name methods
    unsigned int isig = advertiseSignal<const T&>(name);
    isig = xAdvertiseProperty(name, typeOf<T>()->signature(), isig);
    return isig;
  }

  template<typename T> qi::AnyObject DynamicObjectBuilder::object(boost::shared_ptr<T> other)
  {
    DynamicObject* dobj = bareObject();
    qi::AnyObject ao = makeDynamicAnyObject(dobj, other);
    setManageable(dobj, ao.asGenericObject());
    return ao;
  }

  namespace detail
  {
    // create an object with a single method name fname bouncing to func
    template<typename T> AnyObject makeObject(const std::string& fname, T func)
    {
      DynamicObjectBuilder gob;
      gob.advertiseMethod(fname, func);
      return gob.object();
    }
  }
}
#endif  // _QITYPE_DETAILS_GENERICOBJECTBUILDER_HXX_
