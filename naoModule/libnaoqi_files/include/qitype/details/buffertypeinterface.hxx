#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_TYPEBUFFER_HXX_
#define _QITYPE_DETAILS_TYPEBUFFER_HXX_

#include <qi/buffer.hpp>

namespace qi
{
  class TypeBufferImpl: public RawTypeInterface
  {
  public:
    virtual std::pair<char*, size_t> get(void *storage)
    {
      Buffer* b = (Buffer*)Methods::ptrFromStorage(&storage);
      return std::make_pair(const_cast<char*>((const char*)b->data()), b->size());
    }
    virtual void set(void** storage, const char* ptr, size_t sz)
    {
      Buffer* b = (Buffer*)ptrFromStorage(storage);
      b->clear();
      b->write(ptr, sz);
    }
    typedef DefaultTypeImplMethods<Buffer, TypeByPointerPOD<Buffer> > Methods;
    _QI_BOUNCE_TYPE_METHODS(Methods);
  };

template<> class TypeImpl<Buffer>: public TypeBufferImpl {};
}

#endif  // _QITYPE_DETAILS_TYPEBUFFER_HXX_
