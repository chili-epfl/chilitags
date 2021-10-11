#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QIPYTHON_GIL_HPP_
#define _QIPYTHON_GIL_HPP_

#include <qi/log.hpp>
#include <boost/python.hpp>

namespace qi {
  namespace py {

    //Acquire the GIL if needed
    //and setup the thread in the python world if needed
    //
    //Use that before calling python (even from an unknown thread)
    //Can be nested
    class GILScopedLock : private boost::noncopyable
    {
    public:
      GILScopedLock() {
        qiLogCategory("qi.py.gil");
        qiLogDebug() << "ScopedLockEnter(Begin)";
        _state = PyGILState_Ensure();
        qiLogDebug() << "ScopedLockEnter(End)";
      }

      ~GILScopedLock() {
        qiLogCategory("qi.py.gil");
        qiLogDebug() << "ScopedLockQuit(Begin)";
        PyGILState_Release(_state);
        qiLogDebug() << "ScopedLockQuit(End)";
      }

    private:
      PyGILState_STATE _state;
    };

    //Unlock the GIL, allow python to process other python threads
    //Use that while doing C++ computation (sleep, IO, whatever).
    //
    //This can be called from a thread not previously managed by python.
    //Can be nested
    class GILScopedUnlock : private boost::noncopyable
    {
    public:
      GILScopedUnlock()
      {
        qiLogCategory("qi.py.gil");
        qiLogDebug() << "ScopedUnlockEnter(Begin)";
        _save = PyEval_SaveThread();
        qiLogDebug() << "ScopedUnlockEnter(End)";
      }
      ~GILScopedUnlock()
      {
        qiLogCategory("qi.py.gil");
        qiLogDebug() << "ScopedUnlockQuit(Begin)";
        PyEval_RestoreThread(_save);
        qiLogDebug() << "ScopedUnlockQuit(End)";
      }

    private:
      // It is not allowed to call PyEval_SaveThread if the GIL is not owned,
      // so we ensure we have the gil before unlocking, this allows one to nest
      // multiple ScopedUnlock
      GILScopedLock _l;
      PyThreadState* _save;
    };
  }
}


#endif  // _QIPYTHON_GIL_HPP_
