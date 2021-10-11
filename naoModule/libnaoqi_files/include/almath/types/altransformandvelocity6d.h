/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#pragma once
#ifndef _LIBALMATH_ALMATH_TYPES_ALTRANSFORMANDVELOCITY6D_H_
#define _LIBALMATH_ALMATH_TYPES_ALTRANSFORMANDVELOCITY6D_H_

#include<almath/types/altransform.h>
#include<almath/types/alvelocity6d.h>

namespace AL {
  namespace Math {

    /// <summary>
    /// Struct composed of a Transform and a Velocity6D
    /// </summary>
    struct TransformAndVelocity6D
    {
        /// <summary> </summary>
        AL::Math::Transform  T;
        /// <summary> </summary>
        AL::Math::Velocity6D V;

        TransformAndVelocity6D();

        /*! @brief Build a transform and velocity object.
         * @param[in] pT the given Transform.
         * @param[in] pV the given Velocity6D.*/
        TransformAndVelocity6D(
            const AL::Math::Transform& pT,
            const AL::Math::Velocity6D& pV);

        /// <summary>
        /// Check if the actual TransformAndVelocity6D is Near the one
        /// given in argument.
        ///
        /// </summary>
        /// <param name="pTV2"> the second TransformAndVelocity6D </param>
        /// <param name="pEpsilon"> an optionnal epsilon distance - default: 0.0001 </param>
        /// <returns>
        /// true if the distance between the two TransformAndVelocity6D is less than pEpsilon
        /// </returns>
        bool isNear(
            const TransformAndVelocity6D& pTV2,
            const float&                  pEpsilon=0.0001f) const;

    };

  }
}
#endif  // _LIBALMATH_ALMATH_TYPES_ALTRANSFORMANDVELOCITY6D_H_

