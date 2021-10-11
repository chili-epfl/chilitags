#pragma once
/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#ifndef _QI_LOG_TAILFILELOGHANDLER_HPP_
#define _QI_LOG_TAILFILELOGHANDLER_HPP_

# include <boost/noncopyable.hpp>
# include <qi/log.hpp>
# include <string>

namespace qi {
  namespace log {
    class PrivateTailFileLogHandler;

    /// Keeps at most 2 MiB of logs.
    class QI_API TailFileLogHandler : private boost::noncopyable
    {
    public:
      /// Initialize the tail file log handler. File is opened on construction.
      TailFileLogHandler(const std::string &filePath);
      /// Closes the file.
      virtual ~TailFileLogHandler();

      /// Writes the log message to the file.
      void log(const qi::LogLevel verb,
               const qi::os::timeval   date,
               const char              *category,
               const char              *msg,
               const char              *file,
               const char              *fct,
               const int               line);

    private:
      PrivateTailFileLogHandler* _p;
    }; // !TailFileLogHandler

  }; // !log
}; // !qi

#endif  // _QI_LOG_TAILFILELOGHANDLER_HPP_
