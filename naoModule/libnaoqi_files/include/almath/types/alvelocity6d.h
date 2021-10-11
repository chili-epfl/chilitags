/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#pragma once
#ifndef _LIBALMATH_ALMATH_TYPES_ALVELOCITY6D_H_
#define _LIBALMATH_ALMATH_TYPES_ALVELOCITY6D_H_

#include <vector>

namespace AL {
namespace Math {


/// <summary>
/// Create and play with a Velocity6D.
///
/// A Velocity6D is just defined by xd, yd, zd, wxd, wyd and wzd.
/// </summary>
/// \ingroup Types
struct Velocity6D {
  /// <summary> </summary>
  float xd;
  /// <summary> </summary>
  float yd;
  /// <summary> </summary>
  float zd;
  /// <summary> </summary>
  float wxd;
  /// <summary> </summary>
  float wyd;
  /// <summary> </summary>
  float wzd;

  /// <summary>
  /// Create a Velocity6D initialize with 0.0f.
  /**
   *
   * \f$ \left[\begin{array}{c}
   *         xd \\
   *         yd \\
   *         zd \\
   *         wxd \\
   *         wyd \\
   *         wzd
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
  Velocity6D();

  /// <summary>
  /// Create a Velocity6D initialize with the same float.
  /**
   *
   * \f$ \left[\begin{array}{c}
   *         xd \\
   *         yd \\
   *         zd \\
   *         wxd \\
   *         wyd \\
   *         wzd
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
  explicit Velocity6D(float pInit);

  /// <summary>
  /// Create a Velocity6D initialize with explicit value.
  /**
   *
   * \f$ \left[\begin{array}{c}
   *         xd \\
   *         yd \\
   *         zd \\
   *         wxd \\
   *         wyd \\
   *         wzd
   *      \end{array}\right] =
   *      \left[\begin{array}{c}
   *         pXd \\
   *         pYd \\
   *         pZd \\
   *         pWxd \\
   *         pWyd \\
   *         pWzd
   *      \end{array}\right]\f$
   */
  /// </summary>
  /// <param name="pXd"> the float value for xd </param>
  /// <param name="pYd"> the float value for yd </param>
  /// <param name="pZd"> the float value for zd </param>
  /// <param name="pWxd"> the float value for wxd </param>
  /// <param name="pWyd"> the float value for wyd </param>
  /// <param name="pWzd"> the float value for wzd </param>
  Velocity6D(
    float pXd,
    float pYd,
    float pZd,
    float pWxd,
    float pWyd,
    float pWzd);

  /// <summary>
  /// Create a Velocity6D with an std::vector.
  /**
   *
   * \f$ \left[\begin{array}{c}
   *         xd \\
   *         yd \\
   *         zd \\
   *         wxd \\
   *         wyd \\
   *         wzd
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
  ///
  /// xd, yd, zd, wxd, wyd and wzd
  /// </param>
  Velocity6D(const std::vector<float>& pFloats);

  /// <summary>
  /// Overloading of operator + for Velocity6D.
  /// </summary>
  /// <param name="pVel2"> the second Velocity6D </param>
  inline Velocity6D operator+ (const Velocity6D& pVel2) const
  {
    return Velocity6D(
          xd  + pVel2.xd,
          yd  + pVel2.yd,
          zd  + pVel2.zd,
          wxd + pVel2.wxd,
          wyd + pVel2.wyd,
          wzd + pVel2.wzd);
  }

  /// <summary>
  /// Overloading of operator - for Velocity6D.
  /// </summary>
  /// <param name="pVel2"> the second Velocity6D </param>
  inline Velocity6D operator- (const Velocity6D& pVel2) const
  {
    return Velocity6D(
          xd  - pVel2.xd,
          yd  - pVel2.yd,
          zd  - pVel2.zd,
          wxd - pVel2.wxd,
          wyd - pVel2.wyd,
          wzd - pVel2.wzd);
  }

  /// <summary>
  /// Overloading of operator + for Velocity6D.
  /// </summary>
  inline Velocity6D operator+ (void) const
  {
    return *this;
  }

  /// <summary>
  /// Overloading of operator - for Velocity6D.
  /// </summary>
  inline Velocity6D operator- () const
  {
    return Velocity6D(-xd, -yd, -zd, -wxd, -wyd, -wzd);
  }

  /// <summary>
  /// Overloading of operator * for Velocity6D.
  /// </summary>
  /// <param name="pVal"> the float factor. </param>
  inline Velocity6D operator* (const float pVal) const
  {
    return Velocity6D(
          xd*pVal,
          yd*pVal,
          zd*pVal,
          wxd*pVal,
          wyd*pVal,
          wzd*pVal);
  }

  /// <summary>
  /// Overloading of operator / for Velocity6D.
  /// </summary>
  /// <param name="pVal"> the float factor. </param>
  Velocity6D operator/ (const float pVal) const;

  /// <summary>
  /// Overloading of operator == for Velocity6D.
  /// </summary>
  /// <param name="pVel2"> the second Velocity6D. </param>
  bool operator== (const Velocity6D& pVel2) const;

  /// <summary>
  /// Overloading of operator != for Velocity6D.
  /// </summary>
  /// <param name="pVel2"> the second Velocity6D. </param>
  bool operator!= (const Velocity6D& pVel2) const;

  /// <summary>
  /// Overloading of operator *= for Velocity6D.
  /// </summary>
  /// <param name="pVal"> the float factor. </param>
  Velocity6D& operator*= (const float pVal);

  /// <summary>
  /// Overloading of operator /= for Velocity6D.
  /// </summary>
  /// <param name="pVal"> the float factor. </param>
  Velocity6D& operator/= (const float pVal);

  /// <summary>
  /// Check if the actual Velocity6D is Near the one
  /// given in argument.
  ///
  /// </summary>
  /// <param name="pVel2"> the second Velocity6D </param>
  /// <param name="pEpsilon"> an optional epsilon distance </param>
  /// <returns>
  /// true if the difference of each float of the two Velocity6D is less than pEpsilon
  /// </returns>
  bool isNear(
    const Velocity6D& pVel2,
    const float&      pEpsilon=0.0001f) const;

  /// <summary>
  /// Compute the norm of the actual Velocity6D:
  ///
  /// \f$\sqrt{xd^2 + yd^2 + zd^2 + wxd^2 + wyd^2 + wzd^2}\f$
  /// </summary>
  /// <returns>
  /// the float norm of the Velocity6D
  /// </returns>
  float norm() const;

  /// <summary>
  /// Normalize the actual Velocity6D:
  ///
  /// \f$ result = \frac{pVel}{norm(pVel)} \f$
  /// </summary>
  /// <returns>
  /// the Velocity6D normalized
  /// </returns>
  Velocity6D normalize() const;

  /// <summary>
  /// Return the Velocity6D as a vector of float [xd, yd, zd, wxd, wyd, wzd].
  /// </summary>
  void toVector(std::vector<float>& pReturnVector) const;
  std::vector<float> toVector(void) const;
}; // end struct

/// <summary>
/// Overloading of operator * for left Velocity6D.
/// </summary>
/// <param name="pVal"> the float factor. </param>
/// <param name="pVel"> the given Velocity6D. </param>
Velocity6D operator* (
  const float       pVal,
  const Velocity6D& pVel);

/// <summary>
/// Compute the norm of a Velocity6D:
///
/// \f$\sqrt{pVel.xd^2 + pVel.yd^2 + pVel.zd^2 + pVel.wxd^2 + pVel.wyd^2 + pVel.wzd^2}\f$
/// </summary>
/// <param name="pVel"> the given Velocity6D </param>
/// <returns>
/// the float norm of the given Velocity6D
/// </returns>
/// \ingroup Types
float norm(const Velocity6D& pVel);

/// <summary>
/// Normalize a Velocity6D:
///
/// \f$pRes = \frac{pVel}{norm(pVel)} \f$
/// </summary>
/// <param name="pVel"> the given Velocity6D </param>
/// <returns>
/// the given Velocity6D normalized
/// </returns>
/// \ingroup Types
Velocity6D normalize(const Velocity6D& pVel);

} // end namespace Math
} // end namespace AL
#endif  // _LIBALMATH_ALMATH_TYPES_ALVELOCITY6D_H_
