#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QIPYTHON_PYFUTURE_HPP_
#define _QIPYTHON_PYFUTURE_HPP_

#include <boost/python.hpp>
#include <qi/future.hpp>
#include <qitype/anyvalue.hpp>
#include <qipython/gil.hpp>
#include <qipython/api.hpp>
#include <boost/smart_ptr/enable_shared_from_this.hpp>

namespace qi {
  namespace py {

    class PyPromise;
    class PyThreadSafeObject;

    class PyFuture : public qi::Future<qi::AnyValue> {
    protected:
      PyFuture();
      PyFuture(const qi::Future<qi::AnyValue>& fut);
      friend class PyPromise;
      friend void pyFutureCb(const qi::Future<qi::AnyValue>& fut, const PyThreadSafeObject& callable);

    public:
      boost::python::object value(int msecs = qi::FutureTimeout_Infinite) const;
      std::string error(int msecs = qi::FutureTimeout_Infinite) const;
      void addCallback(const boost::python::object &callable);
      FutureState wait(int msecs) const;
      bool        hasError(int msecs) const;
      bool        hasValue(int msecs) const;
    };


    class PyPromise: public qi::Promise<qi::AnyValue> {
    public:
      PyPromise();
      PyPromise(const qi::Promise<qi::AnyValue> &ref);
      PyPromise(boost::python::object callable);
      void setValue(const boost::python::object &pyval);
      PyFuture future();
    };


    //convert from Future to PyFuture
    template <typename T>
    PyFuture toPyFuture(qi::Future<T> fut) {
      PyPromise gprom;
      qi::adaptFuture(fut, gprom);
      return gprom.future();
    }

    //convert from FutureSync to PyFuture
    template <typename T>
    PyFuture toPyFuture(qi::FutureSync<T> fut) {
      return toPyFuture(fut.async());
    }

    //async == true  => convert to PyFuture
    //async == false => convert to PyObject or throw on error
    template <typename T>
    boost::python::object toPyFutureAsync(qi::Future<T> fut, bool async) {
      if (async)
        return boost::python::object(toPyFuture(fut));
      {
        GILScopedUnlock _;
        fut.wait();
      }
      return qi::AnyReference::from(fut.value()).template to<boost::python::object>(); //throw on error
    }

    template <>
    inline boost::python::object toPyFutureAsync<void>(qi::Future<void> fut, bool async) {
      if (async)
        return boost::python::object(toPyFuture(fut));
      {
        GILScopedUnlock _;
        fut.value(); //wait for the result
      }
      return boost::python::object(); //throw on error
    }

    template <typename T>
    boost::python::object toPyFutureAsync(qi::FutureSync<T> fut, bool async) {
      return toPyFutureAsync(fut.async(), async);
    }

    void export_pyfuture();

  }
}


#endif  // _QIPYTHON_PYFUTURE_HPP_
