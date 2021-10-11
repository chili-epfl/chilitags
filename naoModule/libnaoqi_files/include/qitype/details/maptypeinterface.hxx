#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_TYPEMAP_HXX_
#define _QITYPE_DETAILS_TYPEMAP_HXX_

namespace qi
{
  // List container
template<typename M> class MapTypeInterfaceImpl:
public MapTypeInterface
{
public:
  typedef DefaultTypeImplMethods<M,
                               TypeByPointerPOD<M>
                               > MethodsImpl;
  MapTypeInterfaceImpl();
  virtual TypeInterface* elementType();
  virtual TypeInterface* keyType();
  virtual size_t size(void* storage);
  virtual AnyIterator begin(void* storage);
  virtual AnyIterator end(void* storage);
  virtual void insert(void** storage, void* keyStorage, void* valueStorage);
  virtual AnyReference element(void** storage, void* keyStorage, bool autoInsert);
  _QI_BOUNCE_TYPE_METHODS(MethodsImpl);
  TypeInterface* _keyType;
  TypeInterface* _elementType;
};

}

namespace qi {
template<typename M>
MapTypeInterfaceImpl<M>::MapTypeInterfaceImpl()
{
  this->_keyType = typeOf<typename M::key_type>();
  this->_elementType = typeOf<typename M::mapped_type>();
}


template<typename M> TypeInterface*
MapTypeInterfaceImpl<M>::elementType()
{
  return _elementType;
}

template<typename M> TypeInterface*
MapTypeInterfaceImpl<M>::keyType()
{
  return _keyType;
}

template<typename M> size_t
MapTypeInterfaceImpl<M>::size(void* storage)
{
  M* ptr = (M*)ptrFromStorage(&storage);
  return ptr->size();
}


template<typename M> AnyIterator
MapTypeInterfaceImpl<M>::begin(void* storage)
{
  M* ptr = (M*)ptrFromStorage(&storage);
  return TypeSimpleIteratorImpl<typename M::iterator>::make(ptr->begin());
}

template<typename M> AnyIterator
MapTypeInterfaceImpl<M>::end(void* storage)
{
  M* ptr = (M*)ptrFromStorage(&storage);
  return TypeSimpleIteratorImpl<typename M::iterator>::make(ptr->end());
}

template<typename M> void
MapTypeInterfaceImpl<M>::insert(void** storage, void* keyStorage, void* valueStorage)
{
  M* ptr = (M*) ptrFromStorage(storage);
  typename M::key_type& key = *(typename M::key_type*)_keyType->ptrFromStorage(&keyStorage);
  typename M::mapped_type& val = *(typename M::mapped_type*)_elementType->ptrFromStorage(&valueStorage);
  typename M::iterator it = ptr->find(key);
  if (it == ptr->end())
    ptr->insert(std::make_pair(key, val));
  else
    it->second = val;
}

template<typename M> AnyReference
MapTypeInterfaceImpl<M>::element(void** storage, void* keyStorage, bool autoInsert)
{
  //static TypeInterface* elemType = typeOf<typename M::mapped_type>();
  M* ptr = (M*) ptrFromStorage(storage);
  typename M::key_type* key = (typename M::key_type*)_keyType->ptrFromStorage(&keyStorage);
  typename M::iterator it = ptr->find(*key);
  if (it == ptr->end())
  {
    if (!autoInsert)
      return AnyReference();
    typename M::mapped_type& e = (*ptr)[*key];
    return AnyReference::from(e);
  }
  else
    return AnyReference::from(((typename M::mapped_type&)(it->second)));
}



template<typename K, typename V, typename C, typename A>
struct TypeImpl<std::map<K,V, C, A> >: public MapTypeInterfaceImpl<std::map<K, V,C,A> > {};

}
#endif  // _QITYPE_DETAILS_TYPEMAP_HXX_
