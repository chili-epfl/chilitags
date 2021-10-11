#pragma once
/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#ifndef _QI_LOG_CONSOLELOGHANDLER_HPP_
#define _QI_LOG_CONSOLELOGHANDLER_HPP_

# include <boost/noncopyable.hpp>
# include <qi/log.hpp>

namespace qi {
  namespace log {

    class PrivateConsoleLogHandler;

    /// Print colored logs to the console.
    class QI_API ConsoleLogHandler : private boost::noncopyable
    {
    public:
      /// Initialize everything the console log handler needs to print on the
      /// console with colors.
      ConsoleLogHandler();

      /// Unloads any data managed by ConsoleLogHandler. Destructor is not
      /// virtual.
      ~ConsoleLogHandler();

      /// Prints a log message on the console.
      void log(const qi::LogLevel verb,
               const qi::os::timeval   date,
               const char              *category,
               const char              *msg,
               const char              *file,
               const char              *fct,
               const int               line);

      void updateColor();


    protected:
      PrivateConsoleLogHandler* _p;
    };
  }
}


#endif  // _QI_LOG_CONSOLELOGHANDLER_HPP_
