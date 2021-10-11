#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QIPYTHON_PYTHREADSAFEOBJECT_HPP_
#define _QIPYTHON_PYTHREADSAFEOBJECT_HPP_

#include <boost/python.hpp>

namespace qi {
  namespace py {

    // This class ensure boost::python::object are copied in a threadsafe
    // manner.
    // because PyObject inc/dec ref should be done with the GIL held.
    class PyThreadSafeObject {
    public:
      PyThreadSafeObject(const boost::python::object &obj)
      {
        GILScopedLock _lock;
        _obj = new boost::python::object(obj);
      }

      PyThreadSafeObject(const PyThreadSafeObject &rhs)
      {
        GILScopedLock _lock;
        _obj = new boost::python::object(*rhs._obj);
      }

      ~PyThreadSafeObject()
      {
        GILScopedLock _lock;
        delete _obj;
      }

      PyThreadSafeObject& operator=(const PyThreadSafeObject& rhs)
      {
        GILScopedLock _lock;
        *_obj = *rhs._obj;
        return *this;
      }

      // /!\ Should be called with the GIL locked
      boost::python::object &object()
      {
        return *_obj;
      }

      // /!\ Should be called with the GIL locked
      const boost::python::object &object() const
      {
        return *_obj;
      }

    private:
      boost::python::object* _obj;
    };

  }
}


#endif  // _QIPYTHON_PYTHREADSAFEOBJECT_HPP_
