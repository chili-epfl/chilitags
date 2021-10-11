#pragma once
/*
** Author(s):
**  - Cuche Herve <hcuche@aldebaran-robotics.com>
**
** Copyright (C) 2012 Aldebaran Robotics
*/

#ifndef _QI_TYPES_HPP_
#define _QI_TYPES_HPP_

// visual studio 2008 and lower version
# if defined(_MSC_VER) && (_MSC_VER <= 1500)
namespace qi
{
  typedef signed __int8     int8_t;
  typedef signed __int16    int16_t;
  typedef signed __int32    int32_t;
  typedef signed __int64    int64_t;

  typedef unsigned __int8   uint8_t;
  typedef unsigned __int16  uint16_t;
  typedef unsigned __int32  uint32_t;
  typedef unsigned __int64  uint64_t;
}
# else
#  include <stdint.h>
namespace qi
{
  typedef int8_t   int8_t;
  typedef int16_t  int16_t;
  typedef int32_t  int32_t;
  typedef int64_t  int64_t;

  typedef uint8_t  uint8_t;
  typedef uint16_t uint16_t;
  typedef uint32_t uint32_t;
  typedef uint64_t uint64_t;
}
# endif

#endif  // _QI_TYPES_HPP_
