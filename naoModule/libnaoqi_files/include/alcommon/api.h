/*
 *  Copyright (C) 2011, 2012 Aldebaran Robotics
 */

#pragma once
#ifndef _ALCOMMON_API_HPP_
#define _ALCOMMON_API_HPP_

#include <qi/macro.hpp>

#ifdef alcommon_EXPORTS
# define ALCOMMON_API QI_EXPORT_API
#else
# define ALCOMMON_API QI_IMPORT_API
#endif

#define ALCOMMON_API_LEVEL 1

#endif  // _ALCOMMON_API_HPP_

