#pragma once
/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

/** @file qi/log.hpp
 *  @brief Convenient log macro
 */


#ifndef _QI_LOG_HPP_
#define _QI_LOG_HPP_

# include <string>
# include <iostream>
# include <sstream>
# include <cstdarg>
# include <cstdio>

#include <boost/format.hpp>
#include <boost/function/function_fwd.hpp>

#include <qi/os.hpp>


#  define qiLogCategory(Cat)                                             \
  static ::qi::log::CategoryType _QI_LOG_CATEGORY_GET() QI_ATTR_UNUSED = \
    ::qi::log::addCategory(Cat)



#if defined(NO_QI_DEBUG) || defined(NDEBUG)
# define qiLogDebug(...) ::qi::log::detail::qiFalse() && false < qi::log::detail::NullStream().self()
# define qiLogDebugF(Msg, ...)
#else
# define qiLogDebug(...)   _QI_LOG_MESSAGE_STREAM(LogLevel_Debug,   Debug ,  __VA_ARGS__)
# define qiLogDebugF(Msg, ...)   _QI_LOG_MESSAGE(LogLevel_Debug,   _QI_LOG_FORMAT(Msg, __VA_ARGS__))
#endif

#if defined(NO_QI_VERBOSE)
# define qiLogVerbose(...) ::qi::log::detail::qiFalse() && false < qi::log::detail::NullStream().self()
# define qiLogVerboseF(Msg, ...)
#else
# define qiLogVerbose(...) _QI_LOG_MESSAGE_STREAM(LogLevel_Verbose, Verbose, __VA_ARGS__)
# define qiLogVerboseF(Msg, ...)   _QI_LOG_MESSAGE(LogLevel_Verbose,   _QI_LOG_FORMAT(Msg, __VA_ARGS__))
#endif

#if defined(NO_QI_INFO)
# define qiLogInfo(...) ::qi::log::detail::qiFalse() && false < qi::log::detail::NullStream().self()
# define qiLogInfoF(Msg, ...)
#else
# define qiLogInfo(...)    _QI_LOG_MESSAGE_STREAM(LogLevel_Info,    Info,    __VA_ARGS__)
# define qiLogInfoF(Msg, ...)   _QI_LOG_MESSAGE(LogLevel_Info,   _QI_LOG_FORMAT(Msg, __VA_ARGS__))
#endif

#if defined(NO_QI_WARNING)
# define qiLogWarning(...) ::qi::log::detail::qiFalse() && false < qi::log::detail::NullStream().self()
# define qiLogWarningF(Msg, ...)
#else
# define qiLogWarning(...) _QI_LOG_MESSAGE_STREAM(LogLevel_Warning, Warning, __VA_ARGS__)
# define qiLogWarningF(Msg, ...)   _QI_LOG_MESSAGE(LogLevel_Warning,   _QI_LOG_FORMAT(Msg, __VA_ARGS__))
#endif

#if defined(NO_QI_ERROR)
# define qiLogError(...)   ::qi::log::detail::qiFalse() && false < qi::log::detail::NullStream().self()
# define qiLogErrorF(Msg, ...)
#else
# define qiLogError(...)   _QI_LOG_MESSAGE_STREAM(LogLevel_Error,   Error,   __VA_ARGS__)
# define qiLogErrorF(Msg, ...)   _QI_LOG_MESSAGE(LogLevel_Error,   _QI_LOG_FORMAT(Msg, __VA_ARGS__))
#endif

#if defined(NO_QI_FATAL)
# define qiLogFatal(...)  ::qi::log::detail::qiFalse() && false < qi::log::detail::NullStream().self()
# define qiLogFatalF(Msg, ...)
#else
# define qiLogFatal(...)   _QI_LOG_MESSAGE_STREAM(LogLevel_Fatal,   Fatal,   __VA_ARGS__)
# define qiLogFatalF(Msg, ...)   _QI_LOG_MESSAGE(LogLevel_Fatal,   _QI_LOG_FORMAT(Msg, __VA_ARGS__))
#endif

namespace qi {

  enum LogLevel {
    LogLevel_Silent = 0,
    LogLevel_Fatal,
    LogLevel_Error,
    LogLevel_Warning,
    LogLevel_Info,
    LogLevel_Verbose,
    LogLevel_Debug
  };

  enum LogColor {
    LogColor_Never,
    LogColor_Auto,
    LogColor_Always,
  };

  enum LogContextAttr {
    LogContextAttr_None           = 0,
    LogContextAttr_Verbosity      = 1 << 0,
    LogContextAttr_ShortVerbosity = 1 << 1,
    LogContextAttr_Date           = 1 << 2,
    LogContextAttr_Tid            = 1 << 3,
    LogContextAttr_Category       = 1 << 4,
    LogContextAttr_File           = 1 << 5,
    LogContextAttr_Function       = 1 << 6,
    LogContextAttr_Return         = 1 << 7
  };

  typedef int LogContext;

  namespace log {

    //deprecated 1.22
    QI_API_DEPRECATED static const qi::LogLevel silent = LogLevel_Silent;
    QI_API_DEPRECATED static const qi::LogLevel fatal = LogLevel_Fatal;
    QI_API_DEPRECATED static const qi::LogLevel error = LogLevel_Error;
    QI_API_DEPRECATED static const qi::LogLevel warning = LogLevel_Warning;
    QI_API_DEPRECATED static const qi::LogLevel info = LogLevel_Info;
    QI_API_DEPRECATED static const qi::LogLevel verbose = LogLevel_Verbose;
    QI_API_DEPRECATED static const qi::LogLevel debug = LogLevel_Debug;

    //deprecated 1.22
    QI_API_DEPRECATED typedef qi::LogLevel LogLevel;
  }
}

namespace qi {
  namespace log {
    namespace detail {
      struct Category;
    }

    typedef unsigned int      SubscriberId;
    typedef detail::Category* CategoryType;

    //Deprecated 1.22
    QI_API_DEPRECATED typedef unsigned int Subscriber;

    typedef boost::function7<void,
                             const qi::LogLevel,
                             const qi::os::timeval,
                             const char*,
                             const char*,
                             const char*,
                             const char*,
                             int> logFuncHandler;

    QI_API void init(qi::LogLevel   verb = qi::LogLevel_Info,
                     qi::LogContext context = qi::LogContextAttr_ShortVerbosity | qi::LogContextAttr_Tid | qi::LogContextAttr_Category,
                     bool           synchronous = true);

    QI_API void destroy();

    QI_API void log(const qi::LogLevel verb,
                    const char*        category,
                    const char*        msg,
                    const char*        file = "",
                    const char*        fct = "",
                    const int          line = 0);

    QI_API void log(const qi::LogLevel verb,
                    CategoryType       category,
                    const std::string& msg,
                    const char*        file = "",
                    const char*        fct = "",
                    const int          line = 0);


    QI_API const char* logLevelToString(const qi::LogLevel verb, bool verbose = true);

    QI_API qi::LogLevel stringToLogLevel(const char* verb);

    QI_API qi::LogLevel verbosity(SubscriberId sub = 0);

    /// @return the list of existing categories
    QI_API std::vector<std::string> categories();

    /** Parse and execute a set of verbosity rules
    *  Colon separated of rules.
    *  Each rule can be:
    *    - (+)?CAT    : enable category CAT
    *    - -CAT       : disable category CAT
    *    - CAT=level  : set category CAT to level
    *
    * Each category can include a '*' for globbing.
    */
    QI_API void setVerbosity(const std::string& rules, SubscriberId sub = 0);
    QI_API void setVerbosity(const qi::LogLevel lv, SubscriberId sub = 0);


    /// Add/get a category
    QI_API CategoryType addCategory(const std::string& name);
    /// Set \param cat to current verbosity level. Globbing is supported.
    QI_API void enableCategory(const std::string& cat, SubscriberId sub = 0);
    /// Set \param cat to silent log level. Globbing is supported.
    QI_API void disableCategory(const std::string& cat, SubscriberId sub = 0);
    /// Set per-subscriber \param cat to level \param level. Globbing is supported.
    QI_API void setCategory(const std::string& cat, qi::LogLevel level, SubscriberId sub = 0);


    /// \return true if given combination of category and level is enabled.
    QI_API bool isVisible(CategoryType category, qi::LogLevel level);
    /// \return true if given combination of category and level is enabled.
    QI_API bool isVisible(const std::string& category, qi::LogLevel level);

    QI_API void setContext(int ctx);

    QI_API int context();

    QI_API void setColor(LogColor color);

    QI_API LogColor color();

    /** Set logs synchronicity
     *
     * When setting to async, this function must be called after main has
     * started.
     */
    QI_API void setSynchronousLog(bool sync);

    QI_API SubscriberId addLogHandler(const std::string& name,
                                    qi::log::logFuncHandler fct,
                                    qi::LogLevel defaultLevel = LogLevel_Info);

    QI_API void removeLogHandler(const std::string& name);

    QI_API void flush();


   #include <qi/details/warn_push_ignore_deprecated.hpp>
    // Deprecated 1.22
    QI_API_DEPRECATED inline void setVerbosity(SubscriberId sub, const qi::log::LogLevel lv) { setVerbosity((qi::LogLevel)lv, sub); }
    // Deprecated 1.22
    QI_API_DEPRECATED inline void setCategory(SubscriberId sub, const std::string& cat, qi::log::LogLevel level) { setCategory(cat, (qi::LogLevel)level, sub); }
   #include <qi/details/warn_pop_ignore_deprecated.hpp>

  }
}

#include <qi/details/log.hxx>


#endif  // _QI_LOG_HPP_
