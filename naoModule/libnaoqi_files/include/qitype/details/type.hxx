#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_TYPE_HXX_
#define _QITYPE_DETAILS_TYPE_HXX_

#include <qi/atomic.hpp>
#include <qi/types.hpp>
#include <cstring>
#include <map>
#include <vector>
#include <list>
#include <qitype/details/bindtype.hxx>
#include <boost/thread/mutex.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/is_member_pointer.hpp>

/* This file contains the default-provided Type specialisations
 *
 */


namespace qi  {

  namespace detail {

    // Try to get a nice error message for QI_NO_TYPE
    class ForbiddenInTypeSystem: public TypeImpl<int>
    {
    private:
      ForbiddenInTypeSystem();
    };

    template<typename T>
    inline void initializeType(TypeInterface* &tgt)
    {
      qiLogDebug("qitype.typeof") << "first typeOf request for unregistered type " << typeid(T).name();
      tgt = new TypeImpl<T>();
    }

    template<typename T>
    inline TypeInterface* typeOfBackend()
    {
      TypeInterface* result = getType(typeid(T));
      if (!result)
      {

        static TypeInterface* defaultResult = 0;
        QI_ONCE(initializeType<T>(defaultResult));
        result = defaultResult;
      }
      return result;
    }

    template<typename T>
    struct TypeOfAdapter
    {
      typedef T type;
    };

    template<typename T>
    struct TypeOfAdapter<T&>
    {
      typedef typename TypeOfAdapter<T>::type type;
    };

    template<typename T>
    struct TypeOfAdapter<const T>
    {
      typedef typename TypeOfAdapter<T>::type type;
    };

    template<typename T>
    struct TypeOfAdapter<T*>
    {
      typedef typename boost::add_pointer<typename boost::remove_const<typename TypeOfAdapter<T>::type>::type>::type type;
    };

  }

  template<typename T>
  TypeInterface* typeOf()
  {
    return detail::typeOfBackend<typename detail::TypeOfAdapter<T>::type>();
  }

  inline TypeKind TypeInterface::kind()
  {
    return TypeKind_Unknown;
  }

  namespace detail {

    // Bouncer to DefaultAccess or DirectAccess based on type size
    template<typename T>
    class TypeImplMethodsBySize
    {
    public:
      /* DISABLE. Inplace modification does not work with TypeByValue.
      * TODO: be able to switch between ByVal and ByPointer on the
      * same type.
      */
      typedef DefaultTypeImplMethods<T> type;
      /*
      typedef typename boost::mpl::if_c<
        sizeof(T) <= sizeof(void*),
        DefaultTypeImplMethods<T,
                        TypeByValue<T>
                        >,
        DefaultTypeImplMethods<T,
                        TypeByPointer<T>
                        >
                        >::type type;
      */
    };
  }

  // Provide a base class for all templated type impls
  class QITYPE_API TemplateTypeInterface: public TypeInterface
  {
  public:
    // Return erased template argument type
    virtual TypeInterface* templateArgument() = 0;
    // If this type is also an object, return it.
    virtual TypeInterface* next() { return 0;}
  };

  // To detect a templated type, make all the Type of its instanciations
  // inherit fro a single class
  template<template<typename> class T>
  class QITYPE_TEMPLATE_API TypeOfTemplate: public TemplateTypeInterface
  {};

  // Default Type for template type T instanciated with type I
  template<template<typename> class T, typename I>
  class QITYPE_TEMPLATE_API TypeOfTemplateDefaultImpl: public TypeOfTemplate<T>
  {
  public:
     virtual TypeInterface* templateArgument()
    {
      return typeOf<I>();
    }
    typedef DefaultTypeImplMethods<T<I> > Methods;
    _QI_BOUNCE_TYPE_METHODS(Methods);
  };

  template<template<typename> class T, typename I>
  class QITYPE_TEMPLATE_API TypeOfTemplateImpl: public TypeOfTemplateDefaultImpl<T, I>
  {};
}

#endif  // _QITYPE_DETAILS_TYPE_HXX_
