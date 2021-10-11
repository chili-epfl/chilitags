/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#pragma once
#ifndef _LIBALMATH_ALMATH_TOOLS_ALDUBINSCURVE_H_
#define _LIBALMATH_ALMATH_TOOLS_ALDUBINSCURVE_H_

#include <almath/types/alpose2d.h>
#include <vector>

namespace AL {
  namespace Math {

    /// <summary> Get the dubins solutions. </summary>
    /// <param name="pTargetPose">   the target pose </param>
    /// <param name="pCircleRadius"> the circle radius </param>
    /// <returns> The dubins solution. </returns>
    /// \ingroup Tools
    std::vector<Pose2D> getDubinsSolutions(
      const Pose2D& pTargetPose,
      const float   pCircleRadius);

  }
}
#endif  // _LIBALMATH_ALMATH_TOOLS_ALDUBINSCURVE_H_
