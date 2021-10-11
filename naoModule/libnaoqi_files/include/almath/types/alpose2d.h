/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#pragma once
#ifndef _LIBALMATH_ALMATH_TYPES_ALPOSE2D_H_
#define _LIBALMATH_ALMATH_TYPES_ALPOSE2D_H_

#include <vector>
#include <cmath>

namespace AL {
  namespace Math {

    /// <summary>
    /// A pose in a 2-dimentional space.
    ///
    /// On a plane a position is totally defined
    /// by the postions x,y and the rotation theta.
    /// </summary>
    /// \ingroup Types
    struct Pose2D {
      /// <summary> </summary>
      float x;
      /// <summary> </summary>
      float y;
      /// <summary> </summary>
      float theta;

      /// <summary>
      /// Create a Pose2D initialized with 0.0f.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         x \\
       *         y \\
       *         theta
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         0.0 \\
       *         0.0 \\
       *         0.0
       *      \end{array}\right]\f$
       */
      /// </summary>
      Pose2D();

      /// <summary>
      /// Create a Pose2D initialize with the same float.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         x \\
       *         y \\
       *         theta
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         pInit \\
       *         pInit \\
       *         pInit
       *      \end{array}\right]\f$
       */
      /// <param name="pInit"> the float value for each member </param>
      /// </summary>
      explicit Pose2D(float pInit);

      /// <summary>
      /// Create a Pose2D initialized with explicit value.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         x \\
       *         y \\
       *         theta
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         pX \\
       *         pY \\
       *         pTheta
       *      \end{array}\right]\f$
       */
      /// </summary>
      /// <param name="pX"> the float value for x </param>
      /// <param name="pY"> the float value for y </param>
      /// <param name="pTheta"> the float value for theta </param>
      explicit Pose2D(
        float pX,
        float pY,
        float pTheta);

      /// <summary>
      /// Create a Pose2D with an std::vector.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         x \\
       *         y \\
       *         theta
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
      ///
      /// x, y and theta
      /// </param>
      Pose2D(const std::vector<float>& pFloats);

      /// <summary>
      /// Create a Pose2D from polar coordinates.
      /// </summary>
      /// <param name = "pRadius"> the polar radius </param>
      /// <param name = "pAngle"> the polar angle in radians </param>
      /// <returns> the Pose2D extracted from the polar coordinates </returns>
      /// \ingroup Tools
      static Pose2D fromPolarCoordinates(const float pRadius, const float pAngle);

      /// <summary>
      /// Overloading of operator + for Pose2D.
      /// </summary>
      /// <param name="pPos2"> the second Pose2D </param>
      inline Pose2D operator+ (const Pose2D& pPos2) const
      {
        return Pose2D(x + pPos2.x, y + pPos2.y, theta + pPos2.theta);
      }

      /// <summary>
      /// Overloading of operator - for Pose2D.
      /// </summary>
      /// <param name="pPos2"> the second Pose2D </param>
      inline Pose2D operator- (const Pose2D& pPos2) const
      {
        return Pose2D(x - pPos2.x, y - pPos2.y, theta - pPos2.theta);
      }

      /// <summary>
      /// Overloading of operator + for Pose2D.
      /// </summary>
      inline Pose2D operator+ (void) const
      {
        return *this;
      }

      /// <summary>
      /// Overloading of operator - for Pose2D.
      /// </summary>
      inline Pose2D operator- () const
      {
        return Pose2D(-x, -y, -theta);
      }

      /// <summary>
      /// Overloading of operator += for Pose2D.
      /// </summary>
      /// <param name="pPos2"> the second Pose2D </param>
      Pose2D& operator+= (const Pose2D& pPos2);

      /// <summary>
      /// Overloading of operator -= for Pose2D.
      /// </summary>
      /// <param name="pPos2"> the second Pose2D </param>
      Pose2D& operator-= (const Pose2D& pPos2);

      /// <summary>
      /// Overloading of operator *= for Pose2D.
      /// </summary>
      /// <param name="pPos2"> the second Pose2D </param>
      Pose2D& operator*= (const Pose2D& pPos2);

      /// <summary>
      /// Overloading of operator * for Pose2D.
      /// </summary>
      /// <param name="pPos2"> the second Pose2D </param>
      inline Pose2D operator* (const Pose2D& pPos2) const
      {
        return Pose2D(
              x + std::cos(theta) * pPos2.x - std::sin(theta) * pPos2.y,
              y + std::sin(theta) * pPos2.x + std::cos(theta) * pPos2.y,
              theta + pPos2.theta);
      }

      /// <summary>
      /// Overloading of operator == for Pose2D.
      /// </summary>
      /// <param name="pPos2"> the second Pose2D </param>
      bool operator==(const Pose2D& pPos2) const;

      /// <summary>
      /// Overloading of operator != for Pose2D.
      /// </summary>
      /// <param name="pPos2"> the second Pose2D </param>
      bool operator!=(const Pose2D& pPos2) const;

      /// <summary>
      /// Overloading of operator * for Pose2D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      inline Pose2D operator* (float pVal) const
      {
        return Pose2D(x*pVal, y*pVal, theta*pVal);
      }

      /// <summary>
      /// Overloading of operator / for Pose2D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Pose2D operator/ (float pVal) const;

      /// <summary>
      /// Overloading of operator *= for Pose2D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Pose2D& operator*= (float pVal);

      /// <summary>
      /// Overloading of operator /= for Pose2D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Pose2D& operator/= (float pVal);

      /// <summary>
      /// Compute the squared distance between the actual
      /// Pose2D and the one give in argument.
      ///
      /// This avoids doing the sqrt needed for a true distance.
      ///
      /// \f$(pPos1.x-pPos2.x)^2+(pPos1.y-pPos2.y)^2\f$
      /// </summary>
      /// <param name="pPos2"> the second Pose2D </param>
      /// <returns>
      /// the float squared distance between the two Pose2D
      /// </returns>
      float distanceSquared(const Pose2D& pPos2) const;

      /// <summary>
      /// Compute the distance between the actual
      /// Pose2D and the one give in argument.
      ///
      /// \f$\sqrt{(pPos1.x-pPos2.x)^2+(pPos1.y-pPos2.y)^2}\f$
      /// </summary>
      /// <param name="pPos2"> the second Pose2D </param>
      /// <returns>
      /// the float distance between the two Pose2D
      /// </returns>
      float distance(const Pose2D& pPos2) const;

      /// <summary>
      /// Return the inverse of the Pose2D
      /// </summary>
      Pose2D inverse() const;

      /// <summary>
      /// Compute the Pose2D between the actual
      /// Pose2D and the one given in argument:
      ///
      /// result: inverse(pPos1)*pPos2
      ///
      /// </summary>
      /// <param name="pPos2"> the second Pose2D </param>
      Pose2D diff(const Pose2D& pPos2) const;

      /// <summary>
      /// Check if the actual Pose2D is near the one
      /// given in argument.
      ///
      /// </summary>
      /// <param name="pPos2"> the second Pose2D </param>
      /// <param name="pEpsilon"> an optionnal epsilon distance - default: 0.0001 </param>
      /// <returns>
      /// true if the distance between the two Pose2D is less than pEpsilon
      /// </returns>
      bool isNear(const Pose2D& pPos2,
                  const float&  pEpsilon=0.0001f) const;

      /// <summary>
      /// Return the Pose2D as a vector of float [x, y, theta].
      /// </summary>
      void toVector(std::vector<float>& pReturnVector) const;
      std::vector<float> toVector(void) const;

      /// <summary>
      /// Compute the norm of the current Pose2D.
      ///
      /// result: $$/sqrt(pose.x^{2} + pose.y^{2})$$
      ///
      /// </summary>
      inline float norm() const
      {
        return std::sqrt(x * x + y * y);
      }

      /// <summary>
      /// Normalize the current Pose2D position.
      ///
      /// \f$pRes = \frac{pPos}{norm(pPos)}\f$
      /// </summary>
      /// <returns>
      /// the Pose2D normalized
      /// </returns>
      Pose2D normalize() const;

      /// <summary>
      /// Returns the angle of the current Pose2D.
      ///
      /// result: $$/atan2(pose.y, pose.x)$$
      ///
      /// </summary>
      inline float getAngle(void) const
      {
        return std::atan2(y, x);
      }
    }; // end struct


    /// <summary>
    /// Compute the squared distance between two Pose2D.
    ///
    /// \f$(pPos1.x-pPos2.x)^2+(pPos1.y-pPos2.y)^2\f$
    /// </summary>
    /// <param name="pPos1"> the first Pose2D </param>
    /// <param name="pPos2"> the second Pose2D </param>
    /// <returns>
    /// the float squared distance between the two Pose2D
    /// </returns>
    /// \ingroup Types
    float distanceSquared(
      const Pose2D& pPos1,
      const Pose2D& pPos2);

    /// <summary>
    /// Compute the distance between two Pose2D.
    ///
    /// \f$\sqrt{(pPos1.x-pPos2.x)^2+(pPos1.y-pPos2.y)^2}\f$
    /// </summary>
    /// <param name="pPos1"> the first Pose2D </param>
    /// <param name="pPos2"> the second Pose2D </param>
    /// <returns>
    /// the float distance between the two Pose2D
    /// </returns>
    /// \ingroup Types
    float distance(
      const Pose2D& pPos1,
      const Pose2D& pPos2);

    /// <summary>
    /// Inverse the given Pose2D in place:
    ///
    /// </summary>
    /// <param name="pPos"> the given Pose2D </param>
    /// \ingroup Types
    void pose2dInvertInPlace(Pose2D& pPos);

    /// <summary>
    /// Alternative name for inverse: return the pose2d inverse of the given Pose2D.
    ///
    /// </summary>
    /// <param name="pPos"> the given Pose2D </param>
    /// \ingroup Types
    Pose2D pinv(const Pose2D& pPos);


    /// <summary>
    /// Compute the Pose2D between the actual Pose2D and the one give in argument result:
    ///
    /// inverse(pPos1)*pPos2
    ///
    /// </summary>
    /// <param name="pPos1"> the first Pose2D </param>
    /// <param name="pPos2"> the second Pose2D </param>
    /// <returns>
    /// the Pose2D
    /// </returns>
    /// \ingroup Types
    Pose2D pose2dDiff(
      const Pose2D& pPos1,
      const Pose2D& pPos2);

    /// <summary>
    /// Compute the inverse of a Pose2D.
    /// </summary>
    /// <param name="pPos"> the initial Pose2D </param>
    /// <returns> the inverse Pose2D </returns>
    /// \ingroup Types
    Pose2D pose2DInverse(const Pose2D& pPos);

    /// <summary>
    /// Compute the inverse of a Pose2D.
    /// </summary>
    /// <param name="pPos"> the initial Pose2D </param>
    /// <param name="pRes"> the inverse Pose2D </param>
    /// \ingroup Types
    void pose2DInverse(
      const Pose2D& pPos,
      Pose2D&       pRes);


  } // end namespace math
} // end namespace AL
#endif  // _LIBALMATH_ALMATH_TYPES_ALPOSE2D_H_
