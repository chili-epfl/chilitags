#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_TYPESTRING_HXX_
#define _QITYPE_DETAILS_TYPESTRING_HXX_
#include <qi/os.hpp>
#include <qitype/details/structtypeinterface.hxx>

namespace qi
{
  inline std::string StringTypeInterface::getString(void* storage)
  {
    ManagedRawString raw = get(storage);
    std::string res(raw.first.first, raw.first.second);
    if (raw.second)
      raw.second(raw.first);
    return res;
  }

  inline void StringTypeInterface::set(void** storage, const std::string& val)
  {
    set(storage, val.c_str(), val.size());
  }

  class QITYPE_API StringTypeInterfaceImpl: public StringTypeInterface
  {
  public:
    typedef DefaultTypeImplMethods<std::string,
            TypeByPointerPOD<std::string>
              > Methods;
    virtual ManagedRawString get(void* storage)
    {
      std::string* ptr = (std::string*)Methods::ptrFromStorage(&storage);
      return ManagedRawString(RawString((char*)ptr->c_str(), ptr->size()),
          Deleter());
    }
    virtual void set(void** storage, const char* value, size_t sz)
    {
      std::string* ptr = (std::string*)Methods::ptrFromStorage(storage);
      ptr->assign(value, sz);
    }

    _QI_BOUNCE_TYPE_METHODS(Methods);
  };

  template<>
  class TypeImpl<std::string>: public StringTypeInterfaceImpl
  {};

  class QITYPE_API TypeCStringImpl: public StringTypeInterface
  {
  public:
    virtual ManagedRawString get(void* storage)
    {
      return ManagedRawString(RawString((char*)storage, strlen((char*)storage)),
          Deleter());
    }
    virtual void set(void** storage, const char* ptr, size_t sz)
    {
      *(char**)storage = qi::os::strdup(ptr);
    }
    virtual void* clone(void* src)
    {
      return qi::os::strdup((char*)src);
    }
    virtual void destroy(void* src)
    {
      free(src);
    }
    typedef DefaultTypeImplMethods<char*, TypeByValue<char*> > Methods;
    _QI_BOUNCE_TYPE_METHODS_NOCLONE(Methods);
  };

  template<>
  class TypeImpl<char*>: public TypeCStringImpl
  {};


  template<int I> class TypeImpl<char [I]>: public StringTypeInterface
  {
  public:
    virtual void* clone(void* src)
    {
      char* res = new char[I];
      memcpy(res, src, I);
      return res;
    }
    virtual void destroy(void* ptr)
    {
      delete[]  (char*)ptr;
    }
    virtual ManagedRawString get(void* storage)
    {
      return ManagedRawString(RawString((char*)storage, I-1),
          Deleter());
    }
    virtual void set(void** storage, const char* ptr, size_t sz)
    {
      qiLogCategory("qitype.typestring");
      // haha...no
      qiLogWarning() << "set on C array not implemented";
    }

    typedef  DefaultTypeImplMethods<char[I],
      TypeByPointerPOD<char[I]> > Methods;
      _QI_BOUNCE_TYPE_METHODS_NOCLONE(Methods);
  };

  /** Declare a Type for T of Kind string.
  *
  * T must be default-constructible, copy-constructible, and
  * provide a constructor accepting a string.
  * F must be a member function pointer, member object pointer, or free function
  * returning a const string&.
  */
  template<typename T, typename F> class TypeEquivalentString: public StringTypeInterface
  {
  public:
    TypeEquivalentString(F f): _getter(f) {}
    typedef DefaultTypeImplMethods<T, TypeByPointerPOD<T> > Impl;
    virtual void set(void** storage, const char* ptr, size_t sz)
    {
      T* inst = (T*)ptrFromStorage(storage);
      *inst = T(std::string(ptr, sz));
    }
    virtual ManagedRawString get(void* storage)
    {
      T* ptr = (T*)Impl::ptrFromStorage(&storage);
      void* str = detail::fieldStorage(ptr, _getter);
      const std::string& s = detail::fieldValue(ptr, _getter, &str);
      return ManagedRawString(RawString((char*)s.c_str(), s.size()),
          Deleter());
    }
    _QI_BOUNCE_TYPE_METHODS(Impl);
    F _getter;
  };

  template<typename T, typename F>
  StringTypeInterface* makeTypeEquivalentString(T*, F f)
  {
    return new TypeEquivalentString<T, F>(f);
  }
}

/** Register type \p type in the type system as string kind, using constructor
 * for setter, and function \p func for getter
 */
#define QI_EQUIVALENT_STRING_REGISTER(type, func) \
  static bool BOOST_PP_CAT(__qi_registration, __COUNTER__) \
    = qi::registerType(typeid(type),  qi::makeTypeEquivalentString((type*)0, func))

#endif  // _QITYPE_DETAILS_TYPESTRING_HXX_
