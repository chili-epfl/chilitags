/**
 * Author(s):
 *  - Cedric GESTES <gestes@aldebaran-robotics.com>
 *
 * Copyright (C) 2011, 2012 Aldebaran Robotics
 */

/** @file
 *  @brief dll import/export
 */

#pragma once
#ifndef _LIBALPROXIES_ALPROXIES_API_H_
#define _LIBALPROXIES_ALPROXIES_API_H_

#include <qi/macro.hpp>

#ifdef alproxies_EXPORTS
# define ALPROXIES_API QI_EXPORT_API
#else
# define ALPROXIES_API QI_IMPORT_API
#endif

#undef ALPROXIES_API
#define ALPROXIES_API


#endif  // _LIBALPROXIES_ALPROXIES_API_H_

