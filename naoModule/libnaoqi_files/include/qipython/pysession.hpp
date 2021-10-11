#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QIPYTHON_PYSESSION_HPP_
#define _QIPYTHON_PYSESSION_HPP_

#include <boost/python.hpp>
#include <qimessaging/session.hpp>
#include <qipython/api.hpp>

namespace qi {
  namespace py {
    QIPYTHON_API boost::python::object makePySession(const SessionPtr& ses);
    void export_pysession();
  }
}

#endif  // _QIPYTHON_PYSESSION_HPP_
