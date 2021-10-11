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
#ifndef _LIBALEXTRACTOR_ALEXTRACTOR_CONFIG_H_
#define _LIBALEXTRACTOR_ALEXTRACTOR_CONFIG_H_

#include <qi/macro.hpp>

#ifdef alextractor_EXPORTS
# define ALEXTRACTOR_API QI_EXPORT_API
#elif defined(alextractor_IMPORTS)
# define ALEXTRACTOR_API QI_IMPORT_API
#else
# define ALEXTRACTOR_API
#endif

#endif  // _LIBALEXTRACTOR_ALEXTRACTOR_CONFIG_H_

