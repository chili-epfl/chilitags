/**
* @author Aldebaran Robotics
* Copyright (c) Aldebaran Robotics 2007 All Rights Reserved
*/

#pragma once

#ifndef _LIB_ALPYTHONTOOLS_ALPYTHONTOOLS_ALPYTHON_H_
#define _LIB_ALPYTHONTOOLS_ALPYTHONTOOLS_ALPYTHON_H_

// dmerej 2009-21-01: this is an hack for preventing warnings about
// redefinitions in Python.h and stdsoap.h

// Should be fixed when we split alcommon
#undef HAVE_FTIME
#undef HAVE_TIMEGM
#undef _REENTRANT
#undef _XOPEN_SOURCE

#include "Python.h"

#endif
