/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#pragma once
#ifndef _LIBALMATH_ALMATH_TYPES_ALQUATERNION_H_
#define _LIBALMATH_ALMATH_TYPES_ALQUATERNION_H_

#include <vector>

namespace AL {
  namespace Math {

    /// <summary>
    /// Create and play with a Quaternion.
    ///
    /// A Quaternion is just defined by w, x, y and z.
    /// </summary>
    /// \ingroup Types
    struct Quaternion {
      /// <summary> </summary>
      float w;
      /// <summary> </summary>
      float x;
      /// <summary> </summary>
      float y;
      /// <summary> </summary>
      float z;

      /// <summary>
      /// Create a Quaternion initialize with 0.0f.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         w \\
       *         x \\
       *         y \\
       *         z
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         0.0 \\
       *         0.0 \\
       *         0.0 \\
       *         0.0
       *      \end{array}\right]\f$
       */
      /// </summary>
      Quaternion();

      /// <summary>
      /// Create a Quaternion initialize with explicit value.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         w \\
       *         x \\
       *         y \\
       *         z
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         pW \\
       *         pX \\
       *         pY \\
       *         pZ
       *      \end{array}\right]\f$
       */
      /// </summary>
      /// <param name="pW"> the float value for w </param>
      /// <param name="pX"> the float value for x </param>
      /// <param name="pY"> the float value for y </param>
      /// <param name="pZ"> the float value for z </param>
      Quaternion(
        float pW,
        float pX,
        float pY,
        float pZ);

      /// <summary>
      /// Create a Quaternion with an std::vector.
      /**
       *
       * \f$ \left[\begin{array}{c}
       *         w \\
       *         x \\
       *         y \\
       *         z
       *      \end{array}\right] =
       *      \left[\begin{array}{c}
       *         pFloats[0] \\
       *         pFloats[1] \\
       *         pFloats[2] \\
       *         pFloats[3]
       *      \end{array}\right]\f$
       */
      /// </summary>
      /// <param name="pFloats">
      /// An std::vector<float> of size 4 for respectively:
      /// w, x, y and z
      /// </param>
      Quaternion(const std::vector<float>& pFloats);

      /// <summary>
      /// Overloading of operator *= for Quaternion.
      /// </summary>
      /// <param name="pQua2"> the second Quaternion </param>
      Quaternion& operator*= (const Quaternion& pQua2);

      /// <summary>
      /// Overloading of operator * for Quaternion.
      /// </summary>
      /// <param name="pQua2"> the second Quaternion </param>
      inline Quaternion operator* (const Quaternion& pQua2) const
      {
        return Quaternion(
              w*pQua2.w - x*pQua2.x - y*pQua2.y - z*pQua2.z,
              w*pQua2.x + pQua2.w*x + y*pQua2.z - z*pQua2.y,
              w*pQua2.y + pQua2.w*y + z*pQua2.x - x*pQua2.z,
              w*pQua2.z + pQua2.w*z + x*pQua2.y - y*pQua2.x);
      }

      /// <summary>
      /// Overloading of operator == for Quaternion.
      /// </summary>
      /// <param name="pQua2"> the second Quaternion </param>
      bool operator== (const Quaternion& pQua2) const;

      /// <summary>
      /// Overloading of operator != for Quaternion.
      /// </summary>
      /// <param name="pQua2"> the second Quaternion </param>
      bool operator!= (const Quaternion& pQua2) const;

      /// <summary>
      /// Overloading of operator * for Quaternion.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      inline Quaternion operator* (float pVal) const
      {
        return Quaternion(w*pVal, x*pVal, y*pVal, z*pVal);
      }

      /// <summary>
      /// Overloading of operator / for Quaternion.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Quaternion operator/ (float pVal) const;

      /// <summary>
      /// Overloading of operator *= for Quaternion.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Quaternion& operator*= (float pVal);

      /// <summary>
      /// Overloading of operator /= for Quaternion.
      /// </summary>
      /// <param name="pVal"> the float factor </param>
      Quaternion& operator/= (float pVal);

      /// <summary>
      /// Check if the actual Quaternion is near the one
      /// give in argument.
      ///
      /// </summary>
      /// <param name="pQua2"> the second Quaternion </param>
      /// <param name="pEpsilon"> an optionnal epsilon distance </param>
      /// <returns>
      /// true if the distance between the two Quaternion is less than pEpsilon
      /// Check if |Qua1+Qua2| < epsilon or |Qua1-Qua2| < epsilon
      /// </returns>
      bool isNear(
        const Quaternion& pQua2,
        const float&      pEpsilon=0.0001f) const;

      /// <summary>
      /// Compute the norm of the actual Quaternion.
      ///
      /// \f$\sqrt{pQua.w^2+pQua.x^2+pQua.y^2+pQua.z^2}\f$
      /// </summary>
      /// <returns>
      /// the float norm of the Quaternion
      /// </returns>
      float norm() const;

      /// <summary>
      /// Normalize the actual Quaterion.
      ///
      /// \f$result = \frac{pQua}{norm(pQua)}\f$
      /// </summary>
      /// <returns>
      /// the Quaternion normalized
      /// </returns>
      Quaternion normalize() const;

      /// <summary>
      /// Compute the quaternion inverse of the actual Quaternion
      ///
      /// </summary>
      /// <returns>
      /// the Quaternion inverse
      /// </returns>
      Quaternion inverse() const;

      /// <summary>
      /// Create a Quaternion initialized with explicit angle and axis rotation.
      ///
      /// </summary>
      /// <param name="pAngle"> the float value for angle in radian around axis rotation </param>
      /// <param name="pAxisX"> the float value for x value of axis rotation </param>
      /// <param name="pAxisY"> the float value for y value of axis rotation </param>
      /// <param name="pAxisZ"> the float value for z value of axis rotation </param>
      static Quaternion fromAngleAndAxisRotation(
        const float pAngle,
        const float pAxisX,
        const float pAxisY,
        const float pAxisZ);

      /// <summary>
      /// Return the Quaternion as a vector of float [w, x, y, z].
      /// </summary>
      void toVector(std::vector<float>& pReturnVector) const;
      std::vector<float> toVector(void) const;
    };

    /// <summary>
    /// Compute the norm of a Quaternion:
    ///
    /// \f$\sqrt{pQua.w^2+pQua.x^2+pQua.y^2+pQua.z^2}\f$
    /// </summary>
    /// <param name="pQua"> the given Quaternion </param>
    /// <returns>
    /// the float norm of the given Quaternion
    /// </returns>
    /// \ingroup Types
    float norm(const Quaternion& pQua);

    /// <summary>
    /// Normalize a Quaternion:
    ///
    /// \f$pRes = \frac{pQua}{norm(pQua)}\f$
    /// </summary>
    /// <param name="pQua"> the given Quaternion </param>
    /// <returns>
    /// the given Quaternion normalized
    /// </returns>
    /// \ingroup Types
    Quaternion normalize(const Quaternion& pQua);


    /// <summary>
    /// Return the quaternion inverse of the given Quaternion:
    ///
    /// </summary>
    /// <param name="pQua"> the given Quaternion </param>
    /// <param name="pQuaOut"> the inverse of the given Quaternion </param>
    /// \ingroup Types
    void quaternionInverse(
      const Quaternion& pQua,
      Quaternion&       pQuaOut);

    /// <summary>
    /// Return the quaternion inverse of the given Quaternion
    ///
    /// </summary>
    /// <param name="pQua"> the given Quaternion </param>
    /// <returns>
    /// the Quaternion inverse
    /// </returns>
    /// \ingroup Types
    Quaternion quaternionInverse(const Quaternion& pQua);


    /// <summary>
    /// Create a Quaternion initialized with explicit angle and axis rotation.
    ///
    /// </summary>
    /// <param name="pAngle"> the float value for angle in radian around axis rotation </param>
    /// <param name="pAxisX"> the float value for x value of axis rotation </param>
    /// <param name="pAxisY"> the float value for y value of axis rotation </param>
    /// <param name="pAxisZ"> the float value for z value of axis rotation </param>
    /// <returns>
    /// the Quaternion
    /// </returns>
    /// \ingroup Types
    Quaternion quaternionFromAngleAndAxisRotation(
      const float pAngle,
      const float pAxisX,
      const float pAxisY,
      const float pAxisZ);


    /// <summary>
    /// Compute angle and axis rotation from a Quaternion.
    ///
    /// </summary>
    /// <param name="pQuaternion"> the given quaternion </param>
    /// <param name="pAngle"> the computed float value for angle in radian around axis rotation </param>
    /// <param name="pAxisX"> the computed float value for x value of axis rotation </param>
    /// <param name="pAxisY"> the computed float value for y value of axis rotation </param>
    /// <param name="pAxisZ"> the computed float value for z value of axis rotation </param>
    /// \ingroup Types
    void angleAndAxisRotationFromQuaternion(
      const Quaternion& pQuaternion,
      float& pAngle,
      float& pAxisX,
      float& pAxisY,
      float& pAxisZ);

    /// <summary>
    /// Compute angle and axis rotation from a Quaternion.
    ///
    /// </summary>
    /// <param name="pQuaternion"> the given quaternion </param>
    /// <returns>
    /// a vector containing angle, axisX, axisY, axisZ.
    /// </returns>
    /// \ingroup Types
    std::vector<float> angleAndAxisRotationFromQuaternion(
      const Quaternion& pQuaternion);


  } // end namespace math
} // end namespace al
#endif  // _LIBALMATH_ALMATH_TYPES_ALQUATERNION_H_
