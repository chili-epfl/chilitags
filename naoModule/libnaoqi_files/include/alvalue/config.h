/**
 * Author(s):
 *  - Cedric GESTES <gestes@aldebaran-robotics.com>
 *
 * Copyright (C) 2011 Aldebaran Robotics
 */

/** @file
 *  @brief dll import/export
 */

#pragma once
#ifndef _LIBALVALUE_ALVALUE_CONFIG_H_
#define _LIBALVALUE_ALVALUE_CONFIG_H_

// For shared library
#if defined _WIN32 || defined __CYGWIN__
#  define ALVALUE_EXPORT_API __declspec(dllexport)
#  if defined _WINDLL
#    define ALVALUE_IMPORT_API __declspec(dllimport)
#  else
#    define ALVALUE_IMPORT_API
#  endif
#elif __GNUC__ >= 4
#  define ALVALUE_EXPORT_API __attribute__ ((visibility("default")))
#  define ALVALUE_IMPORT_API __attribute__ ((visibility("default")))
#else
#  define ALVALUE_EXPORT_API
#  define ALVALUE_IMPORT_API
#endif

#ifdef alvalue_EXPORTS
# define ALVALUE_API ALVALUE_EXPORT_API
#elif defined(alvalue_IMPORTS)
# define ALVALUE_API ALVALUE_IMPORT_API
#else
# define ALVALUE_API
#endif

#endif  // _LIBALVALUE_ALVALUE_CONFIG_H_

