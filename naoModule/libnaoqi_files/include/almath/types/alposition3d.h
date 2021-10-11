/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#pragma once
#ifndef _LIBALMATH_ALMATH_TYPES_ALPOSITION3D_H_
#define _LIBALMATH_ALMATH_TYPES_ALPOSITION3D_H_

#include <vector>

namespace AL {
  namespace Math {

    /// <summary>
    /// Create and play with a Position3D.
    ///
    /// A Position3D is just defined by x, y and z.
    /// </summary>
    /// \ingroup Types
    struct Position3D {
      /// <summary> </summary>
      float x;
      /// <summary> </summary>
      float y;
      /// <summary> </summary>
      float z;

      /// <summary>
      /// Create a Position3D initialize with 0.0f.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         x \\
       *         y \\
       *         z
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         0.0 \\
       *         0.0 \\
       *         0.0
       *      \end{array}\right]\f$
       */
      /// </summary>
      Position3D();

      /// <summary>
      /// Create a Position3D initialize with the same float.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         x \\
       *         y \\
       *         z
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         pInit \\
       *         pInit \\
       *         pInit
       *      \end{array}\right]\f$
       */
      /// </summary>
      /// <param name="pInit"> the float value for each member </param>
      /// </summary>
      explicit Position3D(float pInit);

      /// <summary>
      /// Create a Position3D initialize with explicit value.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         x \\
       *         y \\
       *         z
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         pX \\
       *         pY \\
       *         pZ
       *      \end{array}\right]\f$
       */
      /// </summary>
      /// <param name="pX"> the float value for x </param>
      /// <param name="pY"> the float value for y </param>
      /// <param name="pZ"> the float value for z </param>
      Position3D(
        float pX,
        float pY,
        float pZ);

      /// <summary>
      /// Create a Position3D with an std::vector.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         x \\
       *         y \\
       *         z
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
      /// x, y and z
      /// </param>
      Position3D (const std::vector<float>& pFloats);

      /// <summary>
      /// Overloading of operator + for Position3D.
      /// </summary>
      /// <param name="pPos2"> the second Position3D </param>
      inline Position3D operator+ (const Position3D& pPos2) const
      {
        return Position3D(x + pPos2.x, y + pPos2.y, z + pPos2.z);
      }

      /// <summary>
      /// Overloading of operator - for Position3D.
      /// </summary>
      /// <param name="pPos2"> the second Position3D </param>
      inline Position3D operator- (const Position3D& pPos2) const
      {
        return Position3D(x - pPos2.x, y - pPos2.y, z - pPos2.z);
      }

      /// <summary>
      /// Overloading of operator + for Position3D.
      /// </summary>
      inline Position3D operator+ (void) const
      {
        return *this;
      }

      /// <summary>
      /// Overloading of operator - for Position3D.
      /// </summary>
      inline Position3D operator- () const
      {
        return Position3D(-x, -y, -z);
      }

      /// <summary>
      /// Overloading of operator += for Position3D.
      /// </summary>
      /// <param name="pPos2"> the second Position3D </param>
      Position3D& operator+= (const Position3D& pPos2);

      /// <summary>
      /// Overloading of operator -= for Position3D.
      /// </summary>
      /// <param name="pPos2"> the second Position3D </param>
      Position3D& operator-= (const Position3D& pPos2);

      /// <summary>
      /// Overloading of operator == for Position3D.
      /// </summary>
      /// <param name="pPos2"> the second Position3D </param>
      bool operator== (const Position3D& pPos2) const;

      /// <summary>
      /// Overloading of operator != for Position3D.
      /// </summary>
      /// <param name="pPos2"> the second Position3D </param>
      bool operator!= (const Position3D& pPos2) const;

      /// <summary>
      /// Overloading of operator * for Position3D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Position3D operator* (float pVal) const;

      /// <summary>
      /// Overloading of operator / for Position3D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Position3D operator/ (float pVal) const;

      /// <summary>
      /// Overloading of operator *= for Position3D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Position3D& operator*= (float pVal);

      /// <summary>
      /// Overloading of operator /= for Position3D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Position3D& operator/= (float pVal);

      /// <summary>
      /// Compute the squared distance between the actual
      /// Position3D and the one given in argument.
      ///
      /// \f$(pPos1.x-pPos2.x)^2+(pPos1.y-pPos2.y)^2+(pPos1.z-pPos2.z)^2\f$
      /// </summary>
      /// <param name="pPos2"> the second Position3D </param>
      /// <returns>
      /// the float squared distance between the two Position3D
      /// </returns>
      float distanceSquared(const Position3D& pPos2) const;

      /// <summary>
      /// Compute the distance between the actual
      /// Position3D and the one given in argument.
      ///
      /// \f$\sqrt{(pPos1.x-pPos2.x)^2+(pPos1.y-pPos2.y)^2+(pPos1.z-pPos2.z)^2}\f$
      /// </summary>
      /// <param name="pPos2"> the second Position3D </param>
      /// <returns>
      /// the float distance between the two Position3D
      /// </returns>
      float distance(const Position3D& pPos2) const;

      /// <summary>
      /// Check if the actual Position3D is near the one
      /// give in argument.
      ///
      /// </summary>
      /// <param name="pPos2"> the second Position3D </param>
      /// <param name="pEpsilon"> an optionnal epsilon distance </param>
      /// <returns>
      /// true if the distance between the two Position3D is less than pEpsilon
      /// </returns>
      bool isNear(
        const Position3D& pPos2,
        const float&      pEpsilon=0.0001f) const;

      /// <summary>
      /// Compute the norm of the actual Position3D.
      ///
      /// \f$\sqrt{pPos.x^2+pPos.y^2+pPos.z^2}\f$
      /// </summary>
      /// <returns>
      /// the float norm of the Position3D
      /// </returns>
      float norm() const;

      /// <summary>
      /// Normalize the actual Position3D.
      ///
      /// \f$result = \frac{pPos}{norm(pPos)}\f$
      /// </summary>
      /// <returns>
      /// the Position3D normalized
      /// </returns>
      Position3D normalize() const;

      /// <summary>
      /// Compute the dot Product between the actual
      /// Position3D and the one give in argument.
      ///
      /// \f$result = (pPos1.x*pPos2.x + pPos1.y*pPos2.y + pPos1.z*pPos2.z)\f$
      /// </summary>
      /// <param name="pPos2"> the second Position3D </param>
      /// <returns>
      /// the float dot product between the two Position3D
      /// </returns>
      float dotProduct(const Position3D& pPos2) const;

      /// <summary>
      /// Compute the cross Product between the actual
      /// Position3D and the one give in argument.
      ///
      /// \f$pRes.x = pPos1.y*pPos2.z - pPos1.z*pPos2.y\f$\n
      /// \f$pRes.y = pPos1.z*pPos2.x - pPos1.x*pPos2.z\f$\n
      /// \f$pRes.z = pPos1.x*pPos2.y - pPos1.y*pPos2.x\f$\n
      /// </summary>
      /// <param name="pPos2"> the second Position3D </param>
      /// <returns>
      /// the Position3D cross product between the two Position3D
      /// </returns>
      Position3D crossProduct(const Position3D& pPos2) const;

      /// <summary>
      /// Return the Position3D as a vector of float [x, y, z].
      /// </summary>
      void toVector(std::vector<float>& pReturnVector) const;
      std::vector<float> toVector(void) const;
    };

    /// <summary>
    /// Compute the squared distance between two Position3D:
    ///
    /// \f$(pPos1.x-pPos2.x)^2+(pPos1.y-pPos2.y)^2+(pPos1.z-pPos2.z)^2\f$
    /// </summary>
    /// <param name="pPos1"> the first Position3D </param>
    /// <param name="pPos2"> the second Position3D </param>
    /// <returns>
    /// the float squared distance between the two Position3D
    /// </returns>
    /// \ingroup Types
    float distanceSquared(
      const Position3D& pPos1,
      const Position3D& pPos2);

    /// <summary>
    /// Compute the distance between two Position3D:
    ///
    /// \f$\sqrt{(pPos1.x-pPos2.x)^2+(pPos1.y-pPos2.y)^2+(pPos1.z-pPos2.z)^2}\f$
    /// </summary>
    /// <param name="pPos1"> the first Position3D </param>
    /// <param name="pPos2"> the second Position3D </param>
    /// <returns>
    /// the float distance between the two Position3D
    /// </returns>
    /// \ingroup Types
    float distance(
      const Position3D& pPos1,
      const Position3D& pPos2);

    /// <summary>
    /// Compute the norm of a Position3D:
    ///
    /// \f$\sqrt{pPos.x^2+pPos.y^2+pPos.z^2}\f$
    /// </summary>
    /// <param name="pPos"> the given Position3D </param>
    /// <returns>
    /// the float norm of the given Position3D
    /// </returns>
    /// \ingroup Types
    float norm(const Position3D& pPos);

    /// <summary>
    /// Normalize a Position3D:
    ///
    /// \f$pRes = \frac{pPos}{norm(pPos)}\f$
    /// </summary>
    /// <param name="pPos"> the given Position3D </param>
    /// <returns>
    /// the given Position3D normalized
    /// </returns>
    /// \ingroup Types
    Position3D normalize(const Position3D& pPos);

    /// <summary>
    /// Compute the dot Product between two Position3D:
    ///
    /// \f$pRes = (pPos1.x*pPos2.x + pPos1.y*pPos2.y + pPos1.z*pPos2.z)\f$
    /// </summary>
    /// <param name="pPos1"> the first Position3D </param>
    /// <param name="pPos2"> the second Position3D </param>
    /// <returns>
    /// the float dot product between the two Position3D
    /// </returns>
    float dotProduct(
      const Position3D& pPos1,
      const Position3D& pPos2);

    /// <summary>
    /// Compute the cross Product between two Position3D:
    ///
    /// \f$pRes.x = pPos1.y*pPos2.z - pPos1.z*pPos2.y\f$\n
    /// \f$pRes.y = pPos1.z*pPos2.x - pPos1.x*pPos2.z\f$\n
    /// \f$pRes.z = pPos1.x*pPos2.y - pPos1.y*pPos2.x\f$\n
    /// </summary>
    /// <param name="pPos1"> the first Position3D </param>
    /// <param name="pPos2"> the second Position3D </param>
    /// <returns>
    /// the Position3D cross product between the two Position3D
    /// </returns>
    Position3D crossProduct(
      const Position3D& pPos1,
      const Position3D& pPos2);

    /// <summary>
    /// Compute the cross Product between two Position3D:
    ///
    /// \f$pRes.x = pPos1.y*pPos2.z - pPos1.z*pPos2.y\f$\n
    /// \f$pRes.y = pPos1.z*pPos2.x - pPos1.x*pPos2.z\f$\n
    /// \f$pRes.z = pPos1.x*pPos2.y - pPos1.y*pPos2.x\f$\n
    /// </summary>
    /// <param name="pPos1"> the first Position3D </param>
    /// <param name="pPos2"> the second Position3D </param>
    /// <param name="pRes"> the Position3D cross product between the two Position3D </param>
    void crossProduct(
      const Position3D& pPos1,
      const Position3D& pPos2,
      Position3D&       pRes);

  } // end namespace math
} // end namespace al
#endif  // _LIBALMATH_ALMATH_TYPES_ALPOSITION3D_H_
