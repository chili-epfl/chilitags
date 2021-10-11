#pragma once
/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#ifndef _QI_QI_HPP_
#define _QI_QI_HPP_

#include <qi/api.hpp>
#include <locale>

namespace qi {

  QI_API QI_API_DEPRECATED void init(int& argc, char **& argv);
  QI_API QI_API_DEPRECATED int argc();
  QI_API QI_API_DEPRECATED const char** argv();
  QI_API QI_API_DEPRECATED const char *program();

  typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_type;
  QI_API const codecvt_type &unicodeFacet();
}

#endif  // _QI_QI_HPP_
