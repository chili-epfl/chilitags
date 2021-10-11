/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#pragma once
#ifndef _LIBALMATH_ALMATH_TOOLS_AVOIDFOOTCOLLISION_H_
#define _LIBALMATH_ALMATH_TOOLS_AVOIDFOOTCOLLISION_H_

#include <almath/types/alpose2d.h>
#include <almath/types/alposition2d.h>
#include <vector>

namespace AL
{
  namespace Math
  {
    /// <summary>
    /// Compute the best position(orientation) of the foot to avoid collision.
    /// </summary>
    /// <param name="pLFootBoundingBox">  vector<Position2D> of the left footBoundingBox.</param>
    /// <param name="pRFootBoundingBox">  vector<Position2D> of the right footBoundingBox.</param>
    /// <param name="pIsLeftSupport">     Bool true if left is the support leg. </param>
    /// <param name="pMove">              the desired and return Pose2D. </param>
    /// <returns>
    /// true if pMove is clamped.
    /// </returns>
    /// \ingroup Tools
    const bool avoidFootCollision(
        const std::vector<Position2D>&  pLFootBoundingBox,
        const std::vector<Position2D>&  pRFootBoundingBox,
        const bool&                     pIsLeftSupport,
        Pose2D&                         pMove);


    /// <summary>
    /// Clip foot move with ellipsoid function
    /// </summary>
    /// <param name="pMaxFootX">  float of the max step along x axis. </param>
    /// <param name="pMaxFootY">  float of the max step along y axis. </param>
    /// <param name="pMove">      the desired and return Pose2D. </param>
    /// <returns>
    /// true if pMove is clamped.
    /// </returns>
    /// \ingroup Tools
    const bool clipFootWithEllipse(
        const float&    pMaxFootX,
        const float&    pMaxFootY,
        Pose2D&         pMove);

    // <summary> Query if the box A and the box B are in collision. </summary>
    // <param name="pBoxA"> vector<Position2D> of the box A. </param>
    // <param name="pBoxB"> vector<Position2D> of the box B. </param>
    // <returns> true if box A and the box B are in collision. </returns>
    const bool areTwoBoxesInCollision(
      const std::vector<Position2D>&  pBoxA,
      const std::vector<Position2D>&  pBoxB);

    // <summary> Compute the box point due to a move. </summary>
    // <param name="pInitBox">  vector<Position2D> of the fixed box. </param>
    // <param name="pMove">      Pose2D the initial move. </param>
    // <param name> vector<Position2D> the new box. </returns>
    void computeBox(
      const std::vector<Position2D>&  pInitBox,
      const Pose2D&                   pMove,
      std::vector<Position2D>&        pMovedBox);

    // <summary> Compute the best orientation of the moving box without
    //  collsion with fixed box. </summary>
    // <param name="pFixesBox">  vector<Position2D> of the fixed box. </param>
    // <param name="pMovingBox"> vector<Position2D> of the moving box. </param>
    // <param name="pMove"> Pose2D of moving box respect to fix box. </param>
    // <returns> Pose2D, the best position. </returns>
    const void dichotomie(
      const std::vector<Position2D>&  pFixedBox,
      const std::vector<Position2D>&  pMovingBox,
      Pose2D&                         pMove);

    // <summary> Checks if segment A intersects segment B. </summary>
    // <param name="pA1"> first point of segment A. </param>
    // <param name="pA2"> second point of segment A. </param>
    // <param name="pB1"> first point of segment B. </param>
    // <param name="pB2"> second point of segment B. </param>
    // <param name="pC">  computed intersection point. </param>
    // <returns> true if the segments intersect in a single point (pC). </returns>
    bool intersectionSegment2D(
        const Position2D &pA1,
        const Position2D &pA2,
        const Position2D &pB1,
        const Position2D &pB2,
        Position2D       &pC);

  } // namespace Math
} // namespace AL

#endif  // _LIBALMATH_ALMATH_TOOLS_AVOIDFOOTCOLLISION_H_

