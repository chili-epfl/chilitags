/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#pragma once
#ifndef _LIBALMATH_ALMATH_TYPES_ALROTATION3D_H_
#define _LIBALMATH_ALMATH_TYPES_ALROTATION3D_H_

#include <vector>

namespace AL {
  namespace Math {

  /// <summary>
  /// A Rotation3D give 3 composed angles in radians.
  /// </summary>
  /// \ingroup Types
    struct Rotation3D {
      /// <summary> </summary>
      float wx;
      /// <summary> </summary>
      float wy;
      /// <summary> </summary>
      float wz;

      /// <summary>
      /// Create a Rotation3D initialized with 0.0f.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         wx \\
       *         wy \\
       *         wz
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         0.0 \\
       *         0.0 \\
       *         0.0
       *      \end{array}\right]\f$
       */
      /// </summary>
      Rotation3D();

      /// <summary>
      /// Create a Rotation3D initialized with the same float.
      /// </summary>
      /// <param name="pInit"> the float value for each member </param>
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         wx \\
       *         wy \\
       *         wz
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         pInit \\
       *         pInit \\
       *         pInit
       *      \end{array}\right]\f$
       */
      /// </summary>
      explicit Rotation3D(float pInit);

      /// <summary>
      /// Create a Rotation3D initialized with explicit value.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         wx \\
       *         wy \\
       *         wz
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         pWx \\
       *         pWy \\
       *         pWz
       *      \end{array}\right]\f$
       */
      /// </summary>
      /// <param name="pWx"> the float value for wx </param>
      /// <param name="pWy"> the float value for wy </param>
      /// <param name="pWz"> the float value for wz </param>
      Rotation3D(
        float pWx,
        float pWy,
        float pWz);

      /// <summary>
      /// Create a Rotation3D with an std::vector.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         wx \\
       *         wy \\
       *         wz
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         pFloats[0] \\
       *         pFloats[1] \\
       *         pFloats[2]
       *      \end{array}\right]\f$
       */
      /// </summary>
      /// <param name="pFloats">
      /// An std::vector<float> of size 3 for respectively:
      /// wx, wy and wz
      /// </param>
      Rotation3D (const std::vector<float>& pFloats);

      /// <summary>
      /// Overloading of operator + for Rotation3D.
      /// </summary>
      /// <param name="pRot2"> the second Rotation3D </param>
      inline Rotation3D operator+ (const Rotation3D& pRot2) const
      {
        return Rotation3D(
              wx + pRot2.wx,
              wy + pRot2.wy,
              wz + pRot2.wz);
      }

      /// <summary>
      /// Overloading of operator - for Rotation3D.
      /// </summary>
      /// <param name="pRot2"> the second Rotation3D </param>
      inline Rotation3D operator- (const Rotation3D& pRot2) const
      {
        return Rotation3D(
              wx - pRot2.wx,
              wy - pRot2.wy,
              wz - pRot2.wz);
      }

      /// <summary>
      /// Overloading of operator += for Rotation3D.
      /// </summary>
      /// <param name="pRot2"> the second Rotation3D </param>
      Rotation3D& operator+= (const Rotation3D& pRot2);

      /// <summary>
      /// Overloading of operator -= for Rotation3D.
      /// </summary>
      /// <param name="pRot2"> the second Rotation3D </param>
      Rotation3D& operator-= (const Rotation3D& pRot2);

      /// <summary>
      /// Overloading of operator == for Rotation3D.
      /// </summary>
      /// <param name="pRot2"> the second Rotation3D </param>
      bool operator== (const Rotation3D& pRot2) const;

      /// <summary>
      /// Overloading of operator != for Rotation3D.
      /// </summary>
      /// <param name="pRot2"> the second Rotation3D </param>
      bool operator!= (const Rotation3D& pRot2) const;

      /// <summary>
      /// Overloading of operator * for Rotation3D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      inline Rotation3D operator* (const float pVal) const
      {
        return Rotation3D(wx*pVal, wy*pVal, wz*pVal);
      }

      /// <summary>
      /// Overloading of operator / for Rotation3D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Rotation3D operator/ (const float pVal) const;

      /// <summary>
      /// Overloading of operator *= for Rotation3D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Rotation3D& operator*= (const float pVal);

      /// <summary>
      /// Overloading of operator /= for Rotation3D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Rotation3D& operator/= (const float pVal);

      /// <summary>
      /// Check if the actual Rotation3D is near the one
      /// given in argument.
      ///
      /// </summary>
      /// <param name="pRot2"> the second Rotation3D </param>
      /// <param name="pEpsilon"> an optional epsilon distance </param>
      /// <returns>
      /// true if the difference of each float of the two Rotation3D is less than pEpsilon
      /// </returns>
      bool isNear(
        const Rotation3D& pRot2,
        const float&      pEpsilon=0.0001f) const;

      /// <summary>
      /// Compute the norm of the actual Position6D:
      ///
      /// \f$\sqrt{pRot.wx^2 + pRot.wy^2 + pRot.wz^2}\f$
      /// </summary>
      /// <returns>
      /// the float norm of the Position6D
      /// </returns>
      float norm() const;

      /// <summary>
      /// Return the Rotation3D as a vector of float [wx, wy, wz].
      /// </summary>
      void toVector(std::vector<float>& pReturnVector) const;
      std::vector<float> toVector(void) const;
    };

    /// <summary>
    /// Compute the norm of a Rotation3D:
    ///
    /// \f$\sqrt{pRot.wx^2 + pRot.wy^2 + pRot.wz^2}\f$
    /// </summary>
    /// <param name="pRot"> the given Rotation3D </param>
    /// <returns>
    /// the float norm of the given Rotation3D
    /// </returns>
    /// \ingroup Types
    float norm(const Rotation3D& pRot);

  } // end namespace Math
} // end namespace AL
#endif  // _LIBALMATH_ALMATH_TYPES_ALROTATION3D_H_
