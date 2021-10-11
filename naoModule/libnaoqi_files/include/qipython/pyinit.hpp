#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QIPYTHON_PYINIT_HPP_
#define _QIPYTHON_PYINIT_HPP_

#include <qipython/api.hpp>

namespace qi {
  namespace py {
    /// Initialise Python and release the lock. This method is *not*
    /// threadsafe. Initialising multiple time is safe, but this must not be
    /// called if initialisation has already been done somewhere else.
    QIPYTHON_API void initialise();
    /// Deinitialise Python. This method is automatically called when
    /// qi::Application exits.
    QIPYTHON_API void uninitialise();
  }
}

#endif  // _QIPYTHON_PYINIT_HPP_
