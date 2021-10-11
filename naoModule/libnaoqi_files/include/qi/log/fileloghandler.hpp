#pragma once
/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#ifndef _QI_LOG_FILELOGHANDLER_HPP_
#define _QI_LOG_FILELOGHANDLER_HPP_

# include <boost/noncopyable.hpp>
# include <qi/log.hpp>

namespace qi {
  namespace log {
    class PrivateFileLogHandler;

    /// Log messages to a file.
    class QI_API FileLogHandler : private boost::noncopyable
    {
    public:
      /// \brief Initialize the file handler on the file. File is opened
      ///        directly on construction.
      explicit FileLogHandler(const std::string& filePath);

      /// Closes the file.
      virtual ~FileLogHandler();

      /// Writes a log message to the file.
      void log(const qi::LogLevel verb,
               const qi::os::timeval   date,
               const char              *category,
               const char              *msg,
               const char              *file,
               const char              *fct,
               const int               line);

    private:
      PrivateFileLogHandler* _p;
    }; // !FileLogHandler

  }; // !log
}; // !qi

#endif  // _QI_LOG_FILELOGHANDLER_HPP_
