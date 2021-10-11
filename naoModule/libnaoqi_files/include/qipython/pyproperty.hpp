#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QIPYTHON_PYPROPERTY_HPP_
#define _QIPYTHON_PYPROPERTY_HPP_

#include <boost/python.hpp>
#include <qitype/metaproperty.hpp>
#include <qitype/anyobject.hpp>
#include <qipython/api.hpp>

namespace qi {
  class PropertyBase;
  namespace py {
    QIPYTHON_API boost::python::object makePyProperty(const std::string &signature);
    QIPYTHON_API qi::PropertyBase *getProperty(boost::python::object obj);
    QIPYTHON_API boost::python::object makePyProxyProperty(const qi::AnyObject &obj, const qi::MetaProperty &prop);
    void export_pyproperty();
  }
}

#endif  // _QIPYTHON_PYPROPERTY_HPP_
