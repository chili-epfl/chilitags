#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_TYPELIST_HXX_
#define _QITYPE_DETAILS_TYPELIST_HXX_

#include <qi/atomic.hpp>

#include <qitype/details/anyreference.hpp>
#include <qitype/details/anyiterator.hpp>
#include <qitype/anyfunction.hpp>

namespace qi
{
  // List container
template<typename T, typename H = ListTypeInterface>
class ListTypeInterfaceImpl: public H
{
public:
  typedef DefaultTypeImplMethods<T, TypeByPointerPOD<T> > MethodsImpl;
  ListTypeInterfaceImpl();
  virtual size_t size(void* storage);
  virtual TypeInterface* elementType();
  virtual AnyIterator begin(void* storage);
  virtual AnyIterator end(void* storage);
  virtual void pushBack(void** storage, void* valueStorage);
  _QI_BOUNCE_TYPE_METHODS(MethodsImpl);
  TypeInterface* _elementType;
};

// Type impl for any class that behaves as a forward iterator (++, *, ==)
template<typename T>
class TypeSimpleIteratorImpl: public IteratorTypeInterface
{
public:
  typedef T Storage;
  virtual AnyReference dereference(void* storage)
  {
    T* ptr = (T*)ptrFromStorage(&storage);
    return AnyReference::from(*(*ptr));
  }
  virtual void next(void** storage)
  {
    T* ptr = (T*)ptrFromStorage(storage);
    ++(*ptr);
  }
  virtual bool equals(void* s1, void* s2)
  {
    T* p1 = (T*)ptrFromStorage(&s1);
    T* p2 = (T*)ptrFromStorage(&s2);
    return *p1 == *p2;
  }
  typedef DefaultTypeImplMethods<Storage, TypeByPointerPOD<T> > TypeImpl;
  _QI_BOUNCE_TYPE_METHODS(TypeImpl);
  static AnyIterator make(const T& val)
  {
    static TypeSimpleIteratorImpl<T>* type = 0;
    QI_THREADSAFE_NEW(type);
    return AnyValue(AnyReference(type, type->initializeStorage(const_cast<void*>((const void*)&val))));
  }
};


template<typename T, typename H>
ListTypeInterfaceImpl<T, H>::ListTypeInterfaceImpl()
{
  _elementType = typeOf<typename T::value_type>();
}

template<typename T, typename H> TypeInterface*
ListTypeInterfaceImpl<T, H>::elementType()
{
  return _elementType;
}

template<typename T, typename H>
AnyIterator ListTypeInterfaceImpl<T, H>::begin(void* storage)
{
  T* ptr = (T*)ptrFromStorage(&storage);
  return TypeSimpleIteratorImpl<typename T::iterator>::make(ptr->begin());
}

template<typename T, typename H>
AnyIterator ListTypeInterfaceImpl<T, H>::end(void* storage)
{
  T* ptr = (T*)ptrFromStorage(&storage);
  return TypeSimpleIteratorImpl<typename T::iterator>::make(ptr->end());
}
namespace detail
{
  template<typename T, typename E>
  void pushBack(T& container, E* element)
  {
    container.push_back(*element);
  }
  template<typename CE, typename E>
  void pushBack(std::set<CE>& container, E* element)
  {
    container.insert(*element);
  }
}
template<typename T, typename H>
void ListTypeInterfaceImpl<T, H>::pushBack(void **storage, void* valueStorage)
{
  T* ptr = (T*) ptrFromStorage(storage);
  detail::pushBack(*ptr, (typename T::value_type*)_elementType->ptrFromStorage(&valueStorage));
}

template<typename T, typename H>
size_t ListTypeInterfaceImpl<T, H>::size(void* storage)
{
  T* ptr = (T*) ptrFromStorage(&storage);
  return ptr->size();
}

// There is no way to register a template container type :(
template<typename T> struct TypeImpl<std::vector<T> >: public ListTypeInterfaceImpl<std::vector<T> > {};
template<typename T> struct TypeImpl<std::list<T> >: public ListTypeInterfaceImpl<std::list<T> > {};
template<typename T> struct TypeImpl<std::set<T> >: public ListTypeInterfaceImpl<std::set<T> > {};


// varargs container
template<typename T>
class VarArgsTypeInterfaceImpl: public ListTypeInterfaceImpl<typename T::VectorType, VarArgsTypeInterface>
{
public:
  typedef ListTypeInterfaceImpl<typename T::VectorType, VarArgsTypeInterface> BaseClass;

  typedef DefaultTypeImplMethods<T, TypeByPointerPOD<T> > MethodsImpl;
  VarArgsTypeInterfaceImpl() {}

  _QI_BOUNCE_TYPE_METHODS(MethodsImpl);

  void* adaptStorage(void** storage) {
    T* ptr = (T*) ptrFromStorage(storage);
    //return ptr
    typename T::VectorType& v = ptr->args();
    return &v;
  }

  virtual size_t size(void* storage) {
    return BaseClass::size(adaptStorage(&storage));
  }
  virtual AnyIterator begin(void* storage) {
    return BaseClass::begin(adaptStorage(&storage));
  }
  virtual AnyIterator end(void* storage) {
    return BaseClass::end(adaptStorage(&storage));
  }
  virtual void pushBack(void** storage, void* valueStorage) {
    void* vstor = adaptStorage(storage);
    BaseClass::pushBack(&vstor, valueStorage);
  }

  //ListTypeInterface* _list;
};


template<typename T> struct TypeImpl<qi::VarArguments<T> >: public VarArgsTypeInterfaceImpl<qi::VarArguments<T> > {};


}

#endif  // _QITYPE_DETAILS_TYPELIST_HXX_
