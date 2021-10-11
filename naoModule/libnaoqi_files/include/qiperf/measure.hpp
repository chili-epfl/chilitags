/*
** Author(s):
** - Nicolas Cornu <ncornu@aldebaran-robotics.com>
**
** Copyright (C) 2013 Aldebaran Robotics
*/

#pragma once
#ifndef _QI_PERF_UTILS_HPP_
#define _QI_PERF_UTILS_HPP_

#include <qiperf/api.hpp>

namespace qi
{
  namespace measure
  {
    // Get the number of fd currently open. Works only for linux.
    QIPERF_API int getNumFD();
  }
}

#endif
