/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#pragma once
#ifndef _LIBALMATH_ALMATH_TYPES_ALPOSITION6D_H_
#define _LIBALMATH_ALMATH_TYPES_ALPOSITION6D_H_

#include <vector>

namespace AL {
  namespace Math {

    /// <summary>
    /// Create and play with a Position6D.
    ///
    /// A Position6D is just defined by x, y, z, wx, wy and wz.
    /// </summary>
    /// \ingroup Types
    struct Position6D {
      /// <summary> </summary>
      float x;
      /// <summary> </summary>
      float y;
      /// <summary> </summary>
      float z;
      /// <summary> </summary>
      float wx;
      /// <summary> </summary>
      float wy;
      /// <summary> </summary>
      float wz;

      /// <summary>
      /// Create a Position6D initialized with 0.0f.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         x \\
       *         y \\
       *         z \\
       *         wx \\
       *         wy \\
       *         wz
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         0.0 \\
       *         0.0 \\
       *         0.0 \\
       *         0.0 \\
       *         0.0 \\
       *         0.0
       *      \end{array}\right]\f$
       */
      /// </summary>
      Position6D();

      /// <summary>
      /// Create a Position6D initialized with the same float.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         x \\
       *         y \\
       *         z \\
       *         wx \\
       *         wy \\
       *         wz
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         pInit \\
       *         pInit \\
       *         pInit \\
       *         pInit \\
       *         pInit \\
       *         pInit
       *      \end{array}\right]\f$
       */
      /// </summary>
      /// <param name="pInit"> the float value for each member </param>
      /// </summary>
      explicit Position6D(float pInit);

      /// <summary>
      /// Create a Position6D initialized with explicit value.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         x \\
       *         y \\
       *         z \\
       *         wx \\
       *         wy \\
       *         wz
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         pX \\
       *         pY \\
       *         pZ \\
       *         pWx \\
       *         pWy \\
       *         pWz
       *      \end{array}\right]\f$
       */
      /// </summary>
      /// <param name="pX"> the float value for x </param>
      /// <param name="pY"> the float value for y </param>
      /// <param name="pZ"> the float value for z </param>
      /// <param name="pWx"> the float value for wx </param>
      /// <param name="pWy"> the float value for wy </param>
      /// <param name="pWz"> the float value for wz </param>
      Position6D(
        float pX,
        float pY,
        float pZ,
        float pWx,
        float pWy,
        float pWz);

      /// <summary>
      /// Create a Position6D with an std::vector.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         x \\
       *         y \\
       *         z \\
       *         wx \\
       *         wy \\
       *         wz
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         pFloats[0] \\
       *         pFloats[1] \\
       *         pFloats[2] \\
       *         pFloats[3] \\
       *         pFloats[4] \\
       *         pFloats[5]
       *      \end{array}\right]\f$
       */
      /// </summary>
      /// <param name="pFloats">
      /// An std::vector<float> of size 6 for respectively:
      /// x, y, z, wx, wy and wz
      /// </param>
      Position6D(const std::vector<float>& pFloats);

      /// <summary>
      /// Overloading of operator + for Position6D.
      /// </summary>
      /// <param name="pPos2"> the second Position6D </param>
      inline Position6D operator+ (const Position6D& pPos2) const
      {
        return Position6D(
              x + pPos2.x,
              y + pPos2.y,
              z + pPos2.z,
              wx + pPos2.wx,
              wy + pPos2.wy,
              wz + pPos2.wz);
      }

      /// <summary>
      /// Overloading of operator - for Position6D.
      /// </summary>
      /// <param name="pPos2"> the second Position6D </param>
      inline Position6D operator- (const Position6D& pPos2) const
      {
        return Position6D(
              x - pPos2.x,
              y - pPos2.y,
              z - pPos2.z,
              wx - pPos2.wx,
              wy - pPos2.wy,
              wz - pPos2.wz);
      }

      /// <summary>
      /// Overloading of operator + for Position6D.
      /// </summary>
      inline Position6D operator+ (void) const
      {
        return *this;
      }

      /// <summary>
      /// Overloading of operator - for Position6D.
      /// </summary>
      inline Position6D operator- () const
      {
        return Position6D(-x, -y, -z, -wx, -wy, -wz);
      }

      /// <summary>
      /// Overloading of operator += for Position6D.
      /// </summary>
      /// <param name="pPos2"> the second Position6D </param>
      Position6D& operator+= (const Position6D& pPos2);

      /// <summary>
      /// Overloading of operator -= for Position6D.
      /// </summary>
      /// <param name="pPos2"> the second Position6D </param>
      Position6D& operator-= (const Position6D& pPos2);

      /// <summary>
      /// Overloading of operator == for Position6D.
      /// </summary>
      /// <param name="pPos2"> the second Position6D </param>
      bool operator== (const Position6D& pPos2) const;

      /// <summary>
      /// Overloading of operator != for Position6D.
      /// </summary>
      /// <param name="pPos2"> the second Position6D </param>
      bool operator!= (const Position6D& pPos2) const;

      /// <summary>
      /// Overloading of operator * for Position6D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      inline Position6D operator* (float pVal) const
      {
        return Position6D(
              x * pVal,
              y * pVal,
              z * pVal,
              wx * pVal,
              wy * pVal,
              wz * pVal);
      }

      /// <summary>
      /// Overloading of operator / for Position6D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Position6D operator/ (float pVal) const;

      /// <summary>
      /// Overloading of operator *= for Position6D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Position6D& operator*= (float pVal);

      /// <summary>
      /// Overloading of operator /= for Position6D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Position6D& operator/= (float pVal);

      /// <summary>
      /// Check if the actual Position6D is near the one
      /// given in argument.
      ///
      /// </summary>
      /// <param name="pPos2"> the second Position6D </param>
      /// <param name="pEpsilon"> an optional epsilon distance </param>
      /// <returns>
      /// true if the difference of each float of the two Position6D is less
      /// than pEpsilon
      /// </returns>
      bool isNear(
        const Position6D& pPos2,
        const float&      pEpsilon=0.0001f) const;

      /// <summary>
      /// Compute the squared distance of translation part (x, y and z)
      /// between the actual Position6D and the one give in argument:
      ///
      /// \f$(pPos1.x-pPos2.x)^2+(pPos1.y-pPos2.y)^2+(pPos1.z-pPos2.z)^2\f$
      /// </summary>
      /// <param name="pPos2"> the second Position6D </param>
      /// <returns>
      /// the float squared distance between the two Position6D
      /// </returns>
      float distanceSquared(const Position6D& pPos2) const;

      /// <summary>
      /// Compute the distance of translation part (x, y and z) between the actual
      /// Position6D and the one give in argument:
      ///
      /// \f$\sqrt{(pPos1.x-pPos2.x)^2+(pPos1.y-pPos2.y)^2+(pPos1.z-pPos2.z)^2}\f$
      /// </summary>
      /// <param name="pPos2"> the second Position6D </param>
      /// <returns>
      /// the float distance between the two Position6D
      /// </returns>
      float distance(const Position6D& pPos2) const;

      /// <summary>
      /// Compute the norm of the actual Position6D:
      ///
      /// \f$\sqrt{pPos.x^2 + pPos.y^2 + pPos.z^2 + pPos.wx^2 + pPos.wy^2 + pPos.wz^2}\f$
      /// </summary>
      /// <returns>
      /// the float norm of the Position6D
      /// </returns>
      float norm() const;

      /// <summary>
      /// Return the Position6D as a vector of float [x, y, z, wx, wy, wz].
      /// </summary>
      void toVector (std::vector<float>& pReturnVector) const;
      std::vector<float> toVector (void) const;
    }; // end struct


    /// <summary>
    /// Compute the squared distance of translation part (x, y and z)
    /// between two Position6D:
    ///
    /// \f$(pPos1.x-pPos2.x)^2+(pPos1.y-pPos2.y)^2+(pPos1.z-pPos2.z)^2\f$
    /// </summary>
    /// <param name="pPos1"> the first Position6D </param>
    /// <param name="pPos2"> the second Position6D </param>
    /// <returns>
    /// the float squared distance between the two Position6D
    /// </returns>
    /// \ingroup Types
    float distanceSquared(
      const Position6D& pPos1,
      const Position6D& pPos2);


    /// <summary>
    /// Compute the distance of translation part (x, y and z) between two Position6D:
    ///
    /// \f$\sqrt{(pPos1.x-pPos2.x)^2+(pPos1.y-pPos2.y)^2+(pPos1.z-pPos2.z)^2}\f$
    /// </summary>
    /// <param name="pPos1"> the first Position6D </param>
    /// <param name="pPos2"> the second Position6D </param>
    /// <returns>
    /// the float distance between the two Position6D
    /// </returns>
    /// \ingroup Types
    float distance(
      const Position6D& pPos1,
      const Position6D& pPos2);

    /// <summary>
    /// Compute the norm of a Position6D:
    ///
    /// \f$\sqrt{pPos.x^2 + pPos.y^2 + pPos.z^2 + pPos.wx^2 + pPos.wy^2 + pPos.wz^2}\f$
    /// </summary>
    /// <param name="pPos"> the given Position6D </param>
    /// <returns>
    /// the float norm of the given Position6D
    /// </returns>
    /// \ingroup Types
    float norm(const Position6D& pPos);

    /// <summary>
    /// Normalize a Position6D:
    ///
    /// \f$pRes = \frac{pPos}{norm(pPos)} \f$
    /// </summary>
    /// <param name="pPos"> the given Position6D </param>
    /// <returns>
    /// the given Position6D normalized
    /// </returns>
    /// \ingroup Types
    Position6D normalize(const Position6D& pPos);

  } // end namespace math
} // end namespace al

#endif  // _LIBALMATH_ALMATH_TYPES_ALPOSITION6D_H_
