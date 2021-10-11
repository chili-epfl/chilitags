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
#ifndef _LIBALTHREAD_ALTHREAD_CONFIG_H_
#define _LIBALTHREAD_ALTHREAD_CONFIG_H_

#include <qi/macro.hpp>

#ifdef althread_EXPORTS
# define ALTHREAD_API QI_EXPORT_API
#elif defined(althread_IMPORTS)
# define ALTHREAD_API QI_IMPORT_API
#else
# define ALTHREAD_API
#endif

#endif  // _LIBALTHREAD_ALTHREAD_CONFIG_H_

