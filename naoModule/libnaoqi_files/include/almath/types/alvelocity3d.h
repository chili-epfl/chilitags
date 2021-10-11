/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#pragma once
#ifndef _LIBALMATH_ALMATH_TYPES_ALVELOCITY3D_H_
#define _LIBALMATH_ALMATH_TYPES_ALVELOCITY3D_H_

#include <vector>

namespace AL {
  namespace Math {

    /// <summary>
    /// Create and play with a Velocity3D.
    ///
    /// A Velocity3D is just defined by xd, yd and zd.
    /// </summary>
    /// \ingroup Types
    struct Velocity3D {
      /// <summary> </summary>
      float xd;
      /// <summary> </summary>
      float yd;
      /// <summary> </summary>
      float zd;

      /// <summary>
      /// Create a Velocity3D initialize with 0.0f.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         xd \\
       *         yd \\
       *         zd
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         0.0 \\
       *         0.0 \\
       *         0.0
       *      \end{array}\right]\f$
       */
      /// </summary>
      Velocity3D();

      /// <summary>
      /// Create a Velocity3D initialize with the same float.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         xd \\
       *         yd \\
       *         zd
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
      explicit Velocity3D(float pInit);

      /// <summary>
      /// Create a Velocity3D initialize with explicit value.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         xd \\
       *         yd \\
       *         zd
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         pXd \\
       *         pYd \\
       *         pZd
       *      \end{array}\right]\f$
       */
      /// </summary>
      /// <param name="pXd"> the float value for xd </param>
      /// <param name="pYd"> the float value for yd </param>
      /// <param name="pZd"> the float value for zd </param>
      Velocity3D(
        float pXd,
        float pYd,
        float pZd);

      /// <summary>
      /// Create a Velocity3D with an std::vector.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         xd \\
       *         yd \\
       *         zd
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
      /// xd, yd, zd
      /// </param>
      Velocity3D(const std::vector<float>& pFloats);

      /// <summary>
      /// Overloading of operator + for Velocity3D.
      /// </summary>
      /// <param name="pVel2"> the second Velocity3D </param>
      inline Velocity3D operator+ (const Velocity3D& pVel2) const
      {
        return Velocity3D(xd + pVel2.xd, yd + pVel2.yd, zd + pVel2.zd);
      }

      /// <summary>
      /// Overloading of operator - for Velocity3D.
      /// </summary>
      /// <param name="pVel2"> the second Velocity3D </param>
      inline Velocity3D operator- (const Velocity3D& pVel2) const
      {
        return Velocity3D(
              xd - pVel2.xd,
              yd - pVel2.yd,
              zd - pVel2.zd);
      }

      /// <summary>
      /// Overloading of operator + for Velocity3D.
      /// </summary>
      inline Velocity3D operator+ (void) const
      {
        return *this;
      }

      /// <summary>
      /// Overloading of operator - for Velocity3D.
      /// </summary>
      inline Velocity3D operator- () const
      {
        return Velocity3D(-xd, -yd, -zd);
      }

      /// <summary>
      /// Overloading of operator += for Velocity3D.
      /// </summary>
      /// <param name="pVel2"> the second Velocity3D </param>
      Velocity3D& operator+= (const Velocity3D& pVel2);

      /// <summary>
      /// Overloading of operator -= for Velocity3D.
      /// </summary>
      /// <param name="pVel2"> the second Velocity3D </param>
      Velocity3D& operator-= (const Velocity3D& pVel2);

      /// <summary>
      /// Overloading of operator == for Velocity3D.
      /// </summary>
      /// <param name="pVel2"> the second Velocity3D </param>
      bool operator== (const Velocity3D& pVel2) const;

      /// <summary>
      /// Overloading of operator != for Velocity3D.
      /// </summary>
      /// <param name="pVel2"> the second Velocity3D </param>
      bool operator!= (const Velocity3D& pVel2) const;

      /// <summary>
      /// Overloading of operator * for Velocity3D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      inline Velocity3D operator* (const float pVal) const
      {
        return Velocity3D(xd*pVal, yd*pVal, zd*pVal);
      }

      /// <summary>
      /// Overloading of operator / for Velocity3D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Velocity3D operator/ (const float pVal) const;

      /// <summary>
      /// Overloading of operator *= for Velocity3D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Velocity3D& operator*= (const float pVal);

      /// <summary>
      /// Overloading of operator /= for Velocity3D.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Velocity3D& operator/= (const float pVal);

      /// <summary>
      /// Check if the actual Velocity3D is Near the one
      /// given in argument.
      ///
      /// </summary>
      /// <param name="pVel2"> the second Velocity3D </param>
      /// <param name="pEpsilon"> an optional epsilon distance </param>
      /// <returns>
      /// true if the difference of each float of the two Velocity3D is less than pEpsilon
      /// </returns>
      bool isNear(
        const Velocity3D& pVel2,
        const float&      pEpsilon=0.0001f) const;


      /// <summary>
      /// Compute the norm of the actual Velocity3D:
      ///
      /// \f$\sqrt{pVel.xd^2 + pVel.yd^2 + pVel.zd^2}\f$
      /// </summary>
      /// <returns>
      /// the float norm of the Velocity3D
      /// </returns>
      float norm () const;

      /// <summary>
      /// Normalize the actual Velocity3D:
      ///
      /// \f$ result = \frac{pVel}{norm(pVel)} \f$
      /// </summary>
      /// <returns>
      /// the Velocity3D normalized
      /// </returns>
      Velocity3D normalize() const;

      /// <summary>
      /// Return the Velocity3D as a vector of float [xd, yd, zd].
      /// </summary>
      void toVector(std::vector<float>& pReturnValue) const;
      std::vector<float> toVector(void) const;
    };

    Velocity3D operator* (
      const float       pM,
      const Velocity3D& pVel1);

    /// <summary>
    /// Compute the norm of a Velocity3D:
    ///
    /// \f$\sqrt{pVel.xd^2 + pVel.yd^2 + pVel.zd^2}\f$
    /// </summary>
    /// <param name="pVel"> the given Velocity3D </param>
    /// <returns>
    /// the float norm of the given Velocity3D
    /// </returns>
    /// \ingroup Types
    float norm (const Velocity3D& pVel);

    /// <summary>
    /// Normalize a Velocity3D:
    ///
    /// \f$ pRes = \frac{pVel}{norm(pVel)} \f$
    /// </summary>
    /// <param name="pVel"> the given Velocity3D </param>
    /// <returns>
    /// the given Velocity3D normalized
    /// </returns>
    /// \ingroup Types
    Velocity3D normalize(const Velocity3D& pVel);

  } // end namespace Math
} // end namespace AL
#endif  // _LIBALMATH_ALMATH_TYPES_ALVELOCITY3D_H_
