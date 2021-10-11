#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QIPYTHON_PYOBJECT_HPP_
#define _QIPYTHON_PYOBJECT_HPP_

#include <boost/python.hpp>
#include <qitype/anyobject.hpp>
#include <qipython/api.hpp>

namespace qi {
  namespace py {
    QIPYTHON_API boost::python::object makePyQiObject(qi::AnyObject obj, const std::string &name = std::string());
    QIPYTHON_API qi::AnyObject         makeQiAnyObject(boost::python::object obj);
    void export_pyobject();
  }
}


#endif  // _QIPYTHON_PYOBJECT_HPP_
