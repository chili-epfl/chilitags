/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#pragma once
#ifndef _LIBALMATH_ALMATH_TYPES_ALAXISMASK_H_
#define _LIBALMATH_ALMATH_TYPES_ALAXISMASK_H_

#include <bitset>

namespace AL {
  namespace Math {

    /// <summary>
    /// Definition of an AXIS_MASK as a bit set.
    ///
    /// static const int AXIS_MASK_X    =  1 \n
    /// static const int AXIS_MASK_Y    =  2 \n
    /// static const int AXIS_MASK_XY   =  3 \n
    /// static const int AXIS_MASK_Z    =  4 \n
    /// static const int AXIS_MASK_WX   =  8 \n
    /// static const int AXIS_MASK_WY   = 16 \n
    /// static const int AXIS_MASK_WZ   = 32 \n
    /// static const int AXIS_MASK_WYWZ = 48 \n
    /// static const int AXIS_MASK_ALL  = 63 \n
    /// static const int AXIS_MASK_VEL  =  7 \n
    /// static const int AXIS_MASK_ROT  = 56 \n
    /// static const int AXIS_MASK_NONE =  0 \n
    /// </summary>
    /// \ingroup Types
    typedef std::bitset<6> AXIS_MASK;

    static const int AXIS_MASK_X    =  1;
    static const int AXIS_MASK_Y    =  2;
    static const int AXIS_MASK_XY   =  3;
    static const int AXIS_MASK_Z    =  4;
    static const int AXIS_MASK_WX   =  8;
    static const int AXIS_MASK_WY   = 16;
    static const int AXIS_MASK_WZ   = 32;
    static const int AXIS_MASK_WYWZ = 48;
    static const int AXIS_MASK_ALL  = 63;
    static const int AXIS_MASK_VEL  =  7;
    static const int AXIS_MASK_ROT  = 56;
    static const int AXIS_MASK_NONE =  0;

    /// <summary> Validates an AxisMask. </summary>
    /// <param name="pAxisMask"> An Axis Mask. </param>
    /// <returns> true if it succeeds, false if it fails. </returns>
    bool isAxisMask(const int pAxisMask);

  }
}
#endif  // _LIBALMATH_ALMATH_TYPES_ALAXISMASK_H_
