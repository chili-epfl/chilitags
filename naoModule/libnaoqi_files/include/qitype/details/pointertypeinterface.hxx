#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_TYPEPOINTER_HXX_
#define _QITYPE_DETAILS_TYPEPOINTER_HXX_

#include <boost/shared_ptr.hpp>

namespace qi
{
  template<typename T> class PointerTypeInterfaceImpl: public PointerTypeInterface
  {
  public:
    TypeInterface* pointedType()
    {
      // Caching the result here is dangerous if T uses runtime factory.
      return typeOf<T>();
    }
    PointerKind pointerKind() { return Raw; }
    AnyReference dereference(void* storage)
    {
      // We are in DirectAccess mode, so storage is a T*.
      void* value = pointedType()->initializeStorage(storage);
      return AnyReference(pointedType(), value);
    }

    void setPointee(void** storage, void* pointer)
    {
      *storage = pointer;
    }

    typedef DefaultTypeImplMethods<T*,
                                     TypeByValue<T*>
                                     > TypeMethodsImpl;
    _QI_BOUNCE_TYPE_METHODS(TypeMethodsImpl);
  };

  template<typename T> class TypeImpl<T*>: public PointerTypeInterfaceImpl<T>{};

  template<typename T> class TypeSharedPointerImpl: public PointerTypeInterface
  {
  public:
    TypeInterface* pointedType()
    {
      return typeOf<typename T::element_type>();
    }
    PointerKind pointerKind() { return Shared; }
    AnyReference dereference(void* storage)
    {
      T* ptr = (T*)ptrFromStorage(&storage);
      void *value = pointedType()->initializeStorage(ptr->get());
      return AnyReference(pointedType(), value);
    }
    void setPointee(void** storage, void* pointer)
    {
      T* ptr = (T*)ptrFromStorage(storage);
      *ptr = T((typename T::element_type*)pointer);
    }
    typedef DefaultTypeImplMethods<T, TypeByPointerPOD<T> > Impl;
     _QI_BOUNCE_TYPE_METHODS(Impl);
  };

  template<typename T> class TypeImpl<boost::shared_ptr<T> >: public TypeSharedPointerImpl<boost::shared_ptr<T> >{};
}

#endif  // _QITYPE_DETAILS_TYPEPOINTER_HXX_
