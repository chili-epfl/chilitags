#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QIPYTHON_TRACE_HPP_
#define _QIPYTHON_TRACE_HPP_

#include <qipython/api.hpp>
#include <string>

namespace qi {
  namespace py {
    QIPYTHON_API std::string thread_traces();
  }
}

#endif  // _QIPYTHON_TRACE_HPP_
