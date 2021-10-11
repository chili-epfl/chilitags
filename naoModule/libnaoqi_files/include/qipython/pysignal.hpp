#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QIPYTHON_PYSIGNAL_HPP_
#define _QIPYTHON_PYSIGNAL_HPP_

#include <boost/python.hpp>
#include <qitype/typeinterface.hpp>
#include <qitype/metasignal.hpp>
#include <qitype/anyobject.hpp>
#include <qipython/api.hpp>

namespace qi {
  class SignalBase;
  namespace py {
    QIPYTHON_API boost::python::object makePySignal(const std::string &signature = "m");
    QIPYTHON_API boost::python::object makePySignalFromBase(boost::shared_ptr<qi::SignalBase> sb);
    QIPYTHON_API boost::python::object makePyProxySignal(const qi::AnyObject &obj, const qi::MetaSignal &signal);
    QIPYTHON_API qi::SignalBase *getSignal(boost::python::object obj);
    void export_pysignal();
  }
}

#endif  // _QIPYTHON_PYSIGNAL_HPP_
