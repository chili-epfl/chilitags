/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#pragma once
#ifndef ALDISPLACEMENT_H
#define ALDISPLACEMENT_H

#include <almath/types/alposition3d.h>
#include <almath/types/alquaternion.h>

namespace AL {
  namespace Math {

    /// <summary>
    /// Struct composed of a Position3D and a Quaternion
    /// </summary>
    struct Displacement
    {
      /// <summary> Translation of the Displacement </summary>
      Position3D P;
      /// <summary> Rotation of the Displacement </summary>
      Quaternion Q;

      /// <summary>
      /// Create a Displacement initialized with default values
      /// </summary>
      explicit Displacement();

      /// <summary>
      /// Create a Displacement with the given Position3D and Quaternion
      /// </summary>
      /// <param name="pos3d"> the pose of the created Displacement </param>
      /// <param name="quat">
      /// the rotation of the created Displacement - default: identity
      /// </param>
      Displacement(
        const Position3D& pos3d,
        const Quaternion& quat = Quaternion());

      /// <summary>
      /// Defining composition of Displacement with * sign
      /// </summary>
      /// <param name="pDisp"> the displacement that is composed with the
      /// current displacement </param>
      /// <returns>
      /// The composed Displacement
      /// </returns>
      Displacement& operator*=(const Displacement& pDisp);

      /// <summary>
      /// Define the binary operation of a composition of Displacements.
      /// </summary>
      /// <param name="pDisp"> second operand of the composition </param>
      /// <returns>
      /// The resulting Displacement
      /// </returns>
      Displacement operator*(const Displacement& pDisp);

      /// <summary>
      /// Check if the current Displacement is Near the one
      /// given in argument.
      /// </summary>
      /// <param name="pDisp2"> the second Displacement</param>
      /// <param name="pEpsilon"> an optional epsilon distance</param>
      /// <returns>
      /// true if the distance between the two Displacement is less than pEpsilon
      /// </returns>
      bool isNear(
        const Displacement&          pDisp2,
        const float                  pEpsilon=0.0001f) const;

    };

  }
}

#endif // ALDISPLACEMENT_H
