/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#pragma once
#ifndef _LIBALMATH_ALMATH_TYPES_ALROTATION_H_
#define _LIBALMATH_ALMATH_TYPES_ALROTATION_H_

#include <vector>

namespace AL {
  namespace Math {

  /// <summary>
  /// A 3*3 rotation matrix.
    /**
     *
     * \f$ \left[\begin{array}{ccc}
     *         r_1c_1 & r_1c_2 & r_1c_3 \\
     *         r_2c_1 & r_2c_2 & r_2c_3 \\
     *         r_3c_1 & r_3c_2 & r_3c_3
     *      \end{array}\right]\f$
     */
  /// </summary>
  /// <A HREF="http://en.wikipedia.org/wiki/Rotation_matrix">more information</A>
  /// \ingroup Types
    struct Rotation
    {
      /// <summary>
      /// row 1 column 1.
      /// </summary>
      float r1_c1;
      /// <summary>
      /// row 1 column 2.
      /// </summary>
      float r1_c2;
      /// <summary>
      /// row 1 column 3.
      /// </summary>
      float r1_c3;
      /// <summary>
      /// row 2 column 1.
      /// </summary>
      float r2_c1;
      /// <summary>
      /// row 2 column 2.
      /// </summary>
      float r2_c2;
      /// <summary>
      /// row 2 column 3.
      /// </summary>
      float r2_c3;
      /// <summary>
      /// row 3 column 1.
      /// </summary>
      float r3_c1;
      /// <summary>
      /// row 3 column 2.
      /// </summary>
      float r3_c2;
      /// <summary>
      /// row 3 column 3.
      /// </summary>
      float r3_c3;

      /// <summary>
      /// Create a Rotation initialized to identity.
      /**
       *
       * \f$ \left[\begin{array}{ccc}
       *         r_1c_1 & r_1c_2 & r_1c_3 \\
       *         r_2c_1 & r_2c_2 & r_2c_3 \\
       *         r_3c_1 & r_3c_2 & r_3c_3
       *      \end{array}\right] =
       *      \left[\begin{array}{ccc}
       *         1.0 & 0.0 & 0.0 \\
       *         0.0 & 1.0 & 0.0 \\
       *         0.0 & 0.0 & 1.0
       *      \end{array}\right]\f$
       */
      /// </summary>
      Rotation();

      /// <summary>
      /// Create a Rotation with an std::vector.
      /// </summary>
      /// <param name="pFloats">
      /// An std::vector<float> of size 9, 12 or 16 for respectively:
      ///
      /// For std::vector<float> of size 9
      ///
      /**
        *
        * \f$ \left[\begin{array}{cccc}
        * r_1c_1 & r_1c_2 & r_1c_3 \\
        * r_2c_1 & r_2c_2 & r_2c_3 \\
        * r_3c_1 & r_3c_2 & r_3c_3
        * \end{array}\right] =
        * \left[\begin{array}{cccc}
        * pFloats[0] & pFloats[1] & pFloats[2] \\
        * pFloats[3] & pFloats[4] & pFloats[5] \\
        * pFloats[6] & pFloats[7] & pFloats[8]
        * \end{array}\right]\f$
        *
        */
      ///
      /// For std::vector<float> of size 12 or 16:
      ///
      /** \f$
        *
        * \left[\begin{array}{cccc}
        * r_1c_1 & r_1c_2 & r_1c_3 \\
        * r_2c_1 & r_2c_2 & r_2c_3 \\
        * r_3c_1 & r_3c_2 & r_3c_3
        * \end{array}\right] =
        * \left[\begin{array}{cccc}
        * pFloats[0] & pFloats[1] & pFloats[2] \\
        * pFloats[4] & pFloats[5] & pFloats[6] \\
        * pFloats[8] & pFloats[9] & pFloats[10]
        * \end{array}\right]\f$
        */
      /// </param>
      Rotation (const std::vector<float>& pFloats);

      /// <summary>
      /// Overloading of operator *= for Rotation.
      /// </summary>
      /// <param name="pRot2"> the second Rotation </param>
      Rotation& operator*= (const Rotation& pRot2);

      /// <summary>
      /// Overloading of operator * for Rotation.
      /// </summary>
      /// <param name="pRot2"> the second Rotation </param>
      Rotation operator* (const Rotation& pRot2) const;

      /// <summary>
      /// Overloading of operator == for Rotation.
      /// </summary>
      /// <param name="pRot2"> the second Rotation </param>
      bool operator==(const Rotation& pRot2) const;

      /// <summary>
      /// Overloading of operator != for Rotation.
      /// </summary>
      /// <param name="pRot2"> the second Rotation </param>
      bool operator!=(const Rotation& pRot2) const;

      /// <summary>
      /// Check if the actual Rotation is near the one
      /// give in argument.
      ///
      /// </summary>
      /// <param name="pRot2"> the second Rotation </param>
      /// <param name="pEpsilon"> an optionnal epsilon distance: default: 0.0001 </param>
      /// <returns>
      /// true if the distance between the two rotations is less than pEpsilon
      /// </returns>
      bool isNear(
        const Rotation& pRot2,
        const float&    pEpsilon=0.0001f) const;

      /// <summary>
      /// Normalize data, if needed, to have Rotation properties.
      ///
      /// </summary>
      void normalizeRotation(void);

      /// <summary>
      /// Check if the rotation is correct.
      /// The condition checks are:
      /// \f$R^t * R = I\f$
      /// and
      /// determinant(R) = 1.0
      ///
      /// </summary>
      /// <param name="pEpsilon"> an optionnal epsilon distance. Default: 0.0001 </param>
      /// <returns>
      /// true if the Rotation is correct
      /// </returns>
      bool isRotation(const float& pEpsilon=0.0001f) const;

      /// <summary>
      /// Compute the rotation transpose (inverse) of the actual Rotation:
      /// </summary>
      /// <returns>
      /// the Rotation transpose
      /// </returns>
      Rotation transpose() const;

      /// <summary>
      /// Compute the determinant of the Rotation:
      ///
      /** \f$pRot.r_1c_1*pRot.r_2c_2*pRot.r_3c_3 +
        * pRot.r_1c_2*pRot.r_2c_3*pRot.r_3c_1 +
        * pRot.r_1c_3*pRot.r_2c_1*pRot.r_3c_2 -
        * pRot.r_1c_1*pRot.r_2c_3*pRot.r_3c_2 -
        * pRot.r_1c_2*pRot.r_2c_1*pRot.r_3c_3 -
        * pRot.r_1c_3*pRot.r_2c_2*pRot.r_3c_1\f$
        */
      /// </summary>
      /// <returns>
      /// the float determinant of the Rotation
      /// </returns>
      float determinant() const;

      /// <summary>
      /// Creates a 3*3 Rotation Matrix from a normalized quaternion ( |a + bi + cj + dk| = 1).
      /// </summary>
      /// <param name="pA"> Coefficient a of the normalized quaternion </param>
      /// <param name="pB"> Coefficient b of the normalized quaternion </param>
      /// <param name="pC"> Coefficient c of the normalized quaternion </param>
      /// <param name="pD"> Coefficient d of the normalized quaternion </param>
      static Rotation fromQuaternion(
        const float pA,
        const float pB,
        const float pC,
        const float pD);


      /// <summary>
      /// Creates a 3*3 Rotation Matrix from a an angle and a normalized direction( |pX, pY, pZ| = 1).
      /// </summary>
      /// <param name="pAngle"> the float value of angle in radian </param>
      /// <param name="pX"> the X direction of the vector of the rotation </param>
      /// <param name="pY"> the Y direction of the vector of the rotation </param>
      /// <param name="pZ"> the Z direction of the vector of the rotation </param>
      static Rotation fromAngleDirection(
        const float pAngle,
        const float pX,
        const float pY,
        const float pZ);

      /// <summary>
      /// Create a Rotation initialized with explicit rotation around x axis.
      ///
      /** \f$ pRot = \left[\begin{array}{cccc}
        * 1.0 & 0.0 & 0.0 \\
        * 0.0 & cos(pRotX) & -sin(pRotX) \\
        * 0.0 & sin(pRotX) & cos(pRotX)
        * \end{array}\right]\f$
        */
      /// </summary>
      /// <param name="pRotX"> the float value for angle rotation in radian around x axis </param>
      static Rotation fromRotX(const float pRotX);

      /// <summary>
      /// Create a Rotation initialized with explicit rotation around y axis.
      ///
      /** \f$ pT = \left[\begin{array}{cccc}
        * cos(pRotY) & 0.0 & sin(pRotY) \\
        * 0.0 & 1.0 & 0.0 \\
        * -sin(pRotY) & 0.0 & cos(pRotY)
        * \end{array}\right]\f$
        */
      /// </summary>
      /// <param name="pRotY"> the float value for angle rotation in radian around y axis </param>
      static Rotation fromRotY(const float pRotY);

      /// <summary>
      /// Create a Rotation initialized with explicit rotation around z axis.
      ///
      /** \f$ pT = \left[\begin{array}{cccc}
        * cos(pRotZ) & -sin(pRotZ) & 0.0 \\
        * sin(pRotZ) & cos(pRotZ) & 0.0 \\
        * 0.0 & 0.0 & 1.0
        * \end{array}\right]\f$
        */
      /// </summary>
      /// <param name="pRotZ"> the float value for angle rotation in radian around z axis </param>
      static Rotation fromRotZ(const float pRotZ);

      /// <summary>
      /// Create a Rotation initialized with euler angle.
      ///
      /// Rot = fromRotZ(pWZ)*fromRotY(pWY)*fromRotX(pWX)
      ///
      /// </summary>
      /// <param name="pWX"> the float value for euler angle x in radian </param>
      /// <param name="pWY"> the float value for euler angle y in radian </param>
      /// <param name="pWZ"> the float value for euler angle z in radian </param>
      static Rotation from3DRotation(
        const float& pWX,
        const float& pWY,
        const float& pWZ);

      /// <summary>
      /// Return the Rotation as a vector of float:
      ///
      /** \f$ \begin{array}{cccc}
        * [r_1c_1, & r_1c_2, & r_1c_3, \\
        * r_2c_1, & r_2c_2, & r_2c_3, \\
        * r_3c_1, & r_3c_2, & r_3c_3]
        * \end{array}\f$
        */
      /// </summary>
      void toVector(std::vector<float>& pReturnValue) const;
      std::vector<float> toVector(void) const;

    }; // end struct

    /// <summary>
    /// Compute the transpose rotation of
    /// the one given in argument:
    /// </summary>
    /// <param name="pRot"> the rotation matrix </param>
    /// <returns>
    /// the rotation transposed
    /// </returns>
        /// \ingroup Types
    Rotation transpose(const Rotation& pRot);


    /// <summary>
    /// Compute the determinant of the given Rotation:
    ///
    /** \f$pRot.r_1c_1*pRot.r_2c_2*pRot.r_3c_3 +
      * pRot.r_1c_2*pRot.r_2c_3*pRot.r_3c_1 +
      * pRot.r_1c_3*pRot.r_2c_1*pRot.r_3c_2 -
      * pRot.r_1c_1*pRot.r_2c_3*pRot.r_3c_2 -
      * pRot.r_1c_2*pRot.r_2c_1*pRot.r_3c_3 -
      * pRot.r_1c_3*pRot.r_2c_2*pRot.r_3c_1\f$
      */
    /// </summary>
    /// <param name="pRot"> the given Rotation </param>
    /// <returns>
    /// the float determinant of Rotation
    /// </returns>
    /// \ingroup Types
    float determinant(const Rotation& pRot);

    /// <summary>
    /// Normalize data, if needed, to have Rotation properties.
    ///
    /// </summary>
    /// <param name="pRot"> the given Rotation </param>
    /// \ingroup Types
    void normalizeRotation(Rotation& pRot);

    /// <summary>
    /// Creates a 3*3 Rotation Matrix from a normalized quaternion ( |a + bi + cj + dk| = 1).
    /// </summary>
    /// <param name="pA"> Coefficient a of the normalized quaternion </param>
    /// <param name="pB"> Coefficient b of the normalized quaternion </param>
    /// <param name="pC"> Coefficient c of the normalized quaternion </param>
    /// <param name="pD"> Coefficient d of the normalized quaternion </param>
    /// <returns>
    /// the Rotation matrix
    /// </returns>
    /// \ingroup Types
    Rotation rotationFromQuaternion(
      const float pA,
      const float pB,
      const float pC,
      const float pD);

    /// <summary>
    /// Creates a 3*3 Rotation Matrix from a an angle and a normalized direction( |pX, pY, pZ| = 1).
    /// </summary>
    /// <param name="pAngle"> the float value of angle in radian </param>
    /// <param name="pX"> the X direction of the vector of the rotation </param>
    /// <param name="pY"> the Y direction of the vector of the rotation </param>
    /// <param name="pZ"> the Z direction of the vector of the rotation </param>
    /// <returns>
    /// the Rotation matrix
    /// </returns>
    /// \ingroup Types
    Rotation rotationFromAngleDirection(
      const float pAngle,
      const float pX,
      const float pY,
      const float pZ);

    /// <summary>
    /// Apply Rotation to a 3D point.
    /// </summary>
    /// <param name="pRot"> the given rotation </param>
    /// <param name="pX"> the X position of the 3D point after rotation </param>
    /// <param name="pY"> the Y position of the 3D point after rotation </param>
    /// <param name="pZ"> the Z position of the 3D point after rotation </param>
    /// \ingroup Types
    void applyRotation(
      const AL::Math::Rotation& pRot,
      float&                    pX,
      float&                    pY,
      float&                    pZ);

    /// <summary>
    /// Create a Rotation initialized with explicit rotation around x axis.
    ///
    /** \f$ pRot = \left[\begin{array}{cccc}
      * 1.0 & 0.0 & 0.0 \\
      * 0.0 & cos(pRotX) & -sin(pRotX) \\
      * 0.0 & sin(pRotX) & cos(pRotX)
      * \end{array}\right]\f$
      */
    /// </summary>
    /// <param name="pRotX"> the float value for angle rotation in radian around x axis </param>
    /// <returns>
    /// the Rotation matrix
    /// </returns>
    /// \ingroup Types
    Rotation rotationFromRotX(const float pRotX);

    /// <summary>
    /// Create a Rotation initialized with explicit rotation around y axis.
    ///
    /** \f$ pT = \left[\begin{array}{cccc}
      * cos(pRotY) & 0.0 & sin(pRotY) \\
      * 0.0 & 1.0 & 0.0 \\
      * -sin(pRotY) & 0.0 & cos(pRotY)
      * \end{array}\right]\f$
      */
    /// </summary>
    /// <param name="pRotY"> the float value for angle rotation in radian around y axis </param>
    /// <returns>
    /// the Rotation matrix
    /// </returns>
    /// \ingroup Types
    Rotation rotationFromRotY(const float pRotY);

    /// <summary>
    /// Create a Rotation initialized with explicit rotation around z axis.
    ///
    /** \f$ pT = \left[\begin{array}{cccc}
      * cos(pRotZ) & -sin(pRotZ) & 0.0 \\
      * sin(pRotZ) & cos(pRotZ) & 0.0 \\
      * 0.0 & 0.0 & 1.0 \end{array}\right]\f$
      */
    /// </summary>
    /// <param name="pRotZ"> the float value for angle rotation in radian around z axis </param>
    /// <returns>
    /// the Rotation matrix
    /// </returns>
    /// \ingroup Types
    Rotation rotationFromRotZ(const float pRotZ);

    /// <summary>
    /// Create a Rotation initialized with euler angle.
    /// Rot = fromRotZ(pWZ)*fromRotY(pWY)*fromRotX(pWX)
    ///
    /// </summary>
    /// <param name="pWX"> the float value for euler angle x in radian </param>
    /// <param name="pWY"> the float value for euler angle y in radian </param>
    /// <param name="pWZ"> the float value for euler angle z in radian </param>
    /// <returns>
    /// the Rotation matrix
    /// </returns>
    /// \ingroup Types
    Rotation rotationFrom3DRotation(
      const float& pWX,
      const float& pWY,
      const float& pWZ);

  }
}
#endif  // _LIBALMATH_ALMATH_TYPES_ALROTATION_H_
