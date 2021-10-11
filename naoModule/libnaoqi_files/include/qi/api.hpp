#pragma once
/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

/** @file
 *  @brief dll import/export and compiler message
 */

#ifndef _QI_API_HPP_
#define _QI_API_HPP_

#include <qi/macro.hpp>
#include <qi/config.hpp>

// qi_EXPORTS controls which symbols are exported when libqi
// is compiled as a SHARED lib.

// To set your own QI_API macro, adapt the following line:
// #define MYLIB_API QI_LIB_API(mylib)

#define QI_API QI_LIB_API(qi)

#define QI_API_LEVEL 2


#endif  // _QI_API_HPP_
