/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#pragma once
#ifndef _LIBALMATH_ALMATH_TYPES_ALTRANSFORM_H_
#define _LIBALMATH_ALMATH_TYPES_ALTRANSFORM_H_

#include <vector>

namespace AL {
  namespace Math {
    /// <summary>
    /// A homogenous transformation matrix.
    ///
    /// </summary>
    /// <A HREF="http://en.wikipedia.org/wiki/Transformation_matrix">more information</A>
    /// \ingroup Types
    struct  Transform {

      /** \cond PRIVATE */
      float r1_c1, r1_c2, r1_c3, r1_c4;
      float r2_c1, r2_c2, r2_c3, r2_c4;
      float r3_c1, r3_c2, r3_c3, r3_c4;
      /** \endcond */

      /// <summary>
      /// Create a Transform initialized to identity.
      /**
       *
       * \f$ \left[\begin{array}{cccc}
       *         r_1c_1 & r_1c_2 & r_1c_3 & r_1c_4 \\
       *         r_2c_1 & r_2c_2 & r_2c_3 & r_2c_4 \\
       *         r_3c_1 & r_3c_2 & r_3c_3 & r_3c_4 \\
       *         0.0 & 0.0 & 0.0 & 1.0
       *      \end{array}\right] =
       *      \left[\begin{array}{cccc}
       *         1.0 & 0.0 & 0.0 & 0.0 \\
       *         0.0 & 1.0 & 0.0 & 0.0 \\
       *         0.0 & 0.0 & 1.0 & 0.0 \\
       *         0.0 & 0.0 & 0.0 & 1.0
       *      \end{array}\right]\f$
       */
      /// </summary>
      Transform();

      /// <summary>
      /// Create a Transform with an std::vector.
      /// </summary>
      /// <param name="pFloats">
      /// An std::vector<float> of size 12 or 16 for respectively:
      ///
      /**
       *
       * \f$ \left[\begin{array}{cccc}
       *         r_1c_1 & r_1c_2 & r_1c_3 & r_1c_4 \\
       *         r_2c_1 & r_2c_2 & r_2c_3 & r_2c_4 \\
       *         r_3c_1 & r_3c_2 & r_3c_3 & r_3c_4 \\
       *         0.0 & 0.0 & 0.0 & 1.0
       *      \end{array}\right] =
       *      \left[\begin{array}{cccc}
       *         pFloats[00] & pFloats[01] & pFloats[02] & pFloats[03] \\
       *         pFloats[04] & pFloats[05] & pFloats[06] & pFloats[07] \\
       *         pFloats[08] & pFloats[09] & pFloats[10] & pFloats[11] \\
       *         0.0 & 0.0 & 0.0 & 1.0
       *      \end{array}\right]\f$
       */
      explicit Transform(const std::vector<float>& pFloats);

      /// <summary>
      /// Create a Transform initialized with explicit value for translation
      /// part. Rotation part is set to identity.
      /**
       *
       * \f$ \left[\begin{array}{cccc}
       *         r_1c_1 & r_1c_2 & r_1c_3 & r_1c_4 \\
       *         r_2c_1 & r_2c_2 & r_2c_3 & r_2c_4 \\
       *         r_3c_1 & r_3c_2 & r_3c_3 & r_3c_4 \\
       *         0.0 & 0.0 & 0.0 & 1.0
       *      \end{array}\right] =
       *      \left[\begin{array}{cccc}
       *         1.0 & 0.0 & 0.0 & pPosX \\
       *         0.0 & 1.0 & 0.0 & pPosY \\
       *         0.0 & 0.0 & 1.0 & pPosZ \\
       *         0.0 & 0.0 & 0.0 & 1.0
       *      \end{array}\right]\f$
       */
      /// </summary>
      /// <param name="pPosX"> the float value for translation x </param>
      /// <param name="pPosY"> the float value for translation y </param>
      /// <param name="pPosZ"> the float value for translation z </param>
      Transform(
        const float& pPosX,
        const float& pPosY,
        const float& pPosZ);

      /// <summary>
      /// Overloading of operator *= for Transform.
      /// </summary>
      /// <param name="pT2"> the second Transform </param>
      Transform& operator*= (const Transform& pT2);

      /// <summary>
      /// Overloading of operator * for Transform.
      /// </summary>
      /// <param name="pT2"> the second Transform </param>
      Transform operator* (const Transform& pT2) const;

      /// <summary>
      /// Overloading of operator == for Transform.
      /// </summary>
      /// <param name="pT2"> the second Transform </param>
      bool operator==(const Transform& pT2) const;

      /// <summary>
      /// Overloading of operator != for Transform.
      /// </summary>
      /// <param name="pT2"> the second Transform </param>
      bool operator!=(const Transform& pT2) const;

      /// <summary>
      /// Check if the actual Transform is near the one
      /// given in argument.
      ///
      /// </summary>
      /// <param name="pT2"> the second Transform </param>
      /// <param name="pEpsilon"> an optionnal epsilon distance: Default: 0.0001 </param>
      /// <returns>
      /// true if the distance between the two Transform is less than pEpsilon
      /// </returns>
      bool isNear(
        const Transform& pT2,
        const float&     pEpsilon=0.0001f) const;

      /// <summary>
      /// Check if the rotation part is correct.
      /// The condition checks are:
      /// \f$R^t * R = I\f$
      /// and
      /// determinant(R) = 1.0
      ///
      /// </summary>
      /// <param name="pEpsilon"> an optionnal epsilon distance. Default: 0.0001 </param>
      /// <returns>
      /// true if the Transform is correct
      /// </returns>
      bool isTransform(
          const float& pEpsilon=0.0001f) const;

      /// <summary>
      /// Normalize data, if needed, to have transform properties.
      ///
      /// </summary>
      void normalizeTransform(void);

      /// <summary>
      /// Compute the norm translation part of the actual Transform:
      ///
      /// \f$\sqrt{pT.r_1c_4^2+pT.r_2c_4^2+pT.r_3c_4^2}\f$
      /// </summary>
      /// <returns>
      /// the float norm of the Transform
      /// </returns>
      float norm() const;

      /// <summary>
      /// Compute the determinant of rotation part of the actual Transform:
      ///
      /**
      * \f$pT.r_1c_1*pT.r_2c_2*pT.r_3c_3 + pT.r_1c_2*pT.r_2c_3*pT.r_3c_1 +
      *  pT.r_1c_3*pT.r_2c_1*pT.r_3c_2 - pT.r_1c_1*pT.r_2c_3*pT.r_3c_2 -
      *  pT.r_1c_2*pT.r_2c_1*pT.r_3c_3 - pT.r_1c_3*pT.r_2c_2*pT.r_3c_1\f$
      */
      /// </summary>
      /// <returns>
      /// the float determinant of rotation Transform part
      /// </returns>
      float determinant() const;

      /// <summary>
      /// Compute the transform inverse of the actual Transform:
      ///
      /**
        * \f$ pT = \left[\begin{array}{cc}R & r \\
        *  0_{31} & 1 \end{array}\right]\f$
        */
      ///
      /** \f$ pTOut = \left[\begin{array}{cc}
        * R^t & (-R^t*r) \\
        * 0_{31} & 1
        * \end{array}\right]\f$
        */
      ///
      /// </summary>
      /// <returns>
      /// the Transform inverse
      /// </returns>
      Transform inverse() const;

      /// <summary>
      /// Create a Transform initialized with explicit rotation around x axis.
      ///
      /** \f$ pT = \left[\begin{array}{cccc}
        * 1.0 & 0.0 & 0.0 & 0.0 \\
        * 0.0 & cos(pRotX) & -sin(pRotX) & 0.0 \\
        * 0.0 & sin(pRotX) & cos(pRotX) & 0.0 \\
        * 0.0 & 0.0 & 0.0 & 1.0 \end{array}\right]\f$
        */
      /// </summary>
      /// <param name="pRotX"> the float value for angle rotation in radian around x axis </param>
      static Transform fromRotX(const float pRotX);

      /// <summary>
      /// Create a Transform initialized with explicit rotation around y axis.
      ///
      /**
       * \f$ pT = \left[\begin{array}{cccc}
       * cos(pRotY) & 0.0 & sin(pRotY) & 0.0 \\
       * 0.0 & 1.0 & 0.0 & 0.0 \\
       * -sin(pRotY) & 0.0 & cos(pRotY) & 0.0 \\
       * 0.0 & 0.0 & 0.0 & 1.0
       * \end{array}\right]\f$
       */
      /// </summary>
      /// <param name="pRotY"> the float value for angle rotation in radian around y axis </param>
      static Transform fromRotY(const float pRotY);

      /// <summary>
      /// Create a Transform initialized with explicit rotation around z axis.
      ///
      /**
        * \f$ pT = \left[\begin{array}{cccc}
        * cos(pRotZ) & -sin(pRotZ) & 0.0 & 0.0 \\
        * sin(pRotZ) & cos(pRotZ) & 0.0 & 0.0 \\
        * 0.0 & 0.0 & 1.0 & 0.0 \\
        * 0.0 & 0.0 & 0.0 & 1.0
        * \end{array}\right]\f$
        */
      /// </summary>
      /// <param name="pRotZ"> the float value for angle rotation in radian around z axis </param>
      static Transform fromRotZ(const float pRotZ);


      /// <summary>
      /// Create a Transform initialize with euler angle.
      ///
      /// H = fromRotZ(pWZ)*fromRotY(pWY)*fromRotX(pWX)
      ///
      /// </summary>
      /// <param name="pWX"> the float value for euler angle x in radian </param>
      /// <param name="pWY"> the float value for euler angle y in radian </param>
      /// <param name="pWZ"> the float value for euler angle z in radian </param>
      static Transform from3DRotation(
        const float& pWX,
        const float& pWY,
        const float& pWZ);


      /// <summary>
      /// Create a Transform initialize with explicit value for translation part.
      ///
      /**
        * \f$ pT = \left[\begin{array}{cccc}
        * 1.0 & 0.0 & 0.0 & pX \\
        * 0.0 & 1.0 & 0.0 & pY \\
        * 0.0 & 0.0 & 1.0 & pZ \\
        * 0.0 & 0.0 & 0.0 & 1.0
        * \end{array}\right]\f$
        */
      /// </summary>
      /// <param name="pX"> the float value for translation axis x in meter (r1_c4) </param>
      /// <param name="pY"> the float value for translation axis y in meter (r2_c4) </param>
      /// <param name="pZ"> the float value for translation axis z in meter (r3_c4) </param>
      static Transform fromPosition(
        const float pX,
        const float pY,
        const float pZ);

      /// <summary>
      /// Create a Transform initialize with explicit value for translation part and euler angle.
      ///
      /// H = fromRotZ(pWZ)*fromRotY(pWY)*fromRotX(pWX)
      ///
      /// then
      ///
      /// H.r1_c4 = pX
      ///
      /// H.r2_c4 = pY
      ///
      /// H.r3_c4 = pZ
      ///
      /// </summary>
      /// <param name="pX"> the float value for translation axis x in meter (r1_c4) </param>
      /// <param name="pY"> the float value for translation axis y in meter (r2_c4) </param>
      /// <param name="pZ"> the float value for translation axis z in meter (r3_c4) </param>
      /// <param name="pWX"> the float value for euler angle x in radian </param>
      /// <param name="pWY"> the float value for euler angle y in radian </param>
      /// <param name="pWZ"> the float value for euler angle z in radian </param>
      static Transform fromPosition(
        const float& pX,
        const float& pY,
        const float& pZ,
        const float& pWX,
        const float& pWY,
        const float& pWZ);

      /// <summary>
      /// Compute the Transform between the actual
      /// Transform and the one given in argument:
      ///
      /// result: inverse(pT1)*pT2
      ///
      /// </summary>
      /// <param name="pT2"> the second transform </param>
      Transform diff(const Transform& pT2) const;


      /// <summary>
      /// Compute the squared distance between the actual
      /// Transform and the one given in argument (translation part):
      ///
      /// \f$(pT1.r_1c_4-pT2.r_1c_4)^2+(pT1.r_2c_4-pT2.r_2c_4)^2+(pT1.r_3c_4-pT2.r_3c_4)^2\f$
      /// </summary>
      /// <param name="pT2"> the second Transform </param>
      /// <returns>
      /// the float squared distance between the two Transform: translation part
      /// </returns>
      float distanceSquared(const Transform& pT2) const;


      /// <summary>
      /// Compute the distance between the actual
      /// Transform and the one given in argument:
      ///
      /// \f$\sqrt{(pT1.r_1c_4-pT2.r_1c_4)^2+(pT1.r_2c_4-pT2.r_2c_4)^2+(pT1.r_3c_4-pT2.r_3c_4)^2}\f$
      /// </summary>
      /// <param name="pT2"> the second Transform </param>
      /// <returns>
      /// the float distance between the two Transform
      /// </returns>
      float distance(const Transform& pT2) const;

      /// <summary>
      /// Return the Transform as a vector of float:
      ///
      /** \f$ \begin{array}{cccc}
        * [r_1c_1, & r_1c_2, & r_1c_3, & r_1c_4, \\
        * r_2c_1, & r_2c_2, & r_2c_3, & r_2c_4, \\
        * r_3c_1, & r_3c_2, & r_3c_3, & r_3c_4, \\
        * 0.0, & 0.0, & 0.0, & 1.0]
        * \end{array}\f$
        */
      /// </summary>
      void toVector(std::vector<float>& pReturnVector) const;
      std::vector<float> toVector(void) const;
    }; // end struct

    /// <summary>
    /// pTOut = pT*pTOut
    ///
    /// </summary>
    /// <param name="pT"> the first constant Transform </param>
    /// <param name="pTOut"> the second modified Transform </param>
    /// \ingroup Types
    void transformPreMultiply(
      const Transform& pT,
      Transform&       pTOut);

    /// <summary>
    /// Compute the norm translation part of the actual Transform:
    ///
    /// \f$\sqrt{pT.r_1c_4^2+pT.r_2c_4^2+pT.r_3c_4^2}\f$
    /// </summary>
    /// <param name="pT"> the given Transform </param>
    /// <returns>
    /// the float norm of the given Transform
    /// </returns>
    /// \ingroup Types
    float norm(const Transform& pT);

    /// <summary>
    /// Normalize data, if needed, to have transform properties.
    ///
    /// </summary>
    /// <param name="pT"> the given Transform </param>
    /// \ingroup Types
    void normalizeTransform(Transform& pT);

    /// <summary>
    /// DEPRECATED: Use toVector function.
    /// Copy the Transform in a vector of float:
    ///
    /** \f$ \begin{array}{cccc}
      * [r_1c_1, & r_1c_2, & r_1c_3, & r_1c_4, \\
      * r_2c_1, & r_2c_2, & r_2c_3, & r_2c_4, \\
      * r_3c_1, & r_3c_2, & r_3c_3, & r_3c_4, \\
      * 0.0, & 0.0, & 0.0, & 1.0]
      * \end{array}\f$
      */
    ///
    /// </summary>
    /// <param name="pT"> the given Transform </param>
    /// <param name="pTOut"> the vector of float update to given transform value </param>
    /// \ingroup Types
    void transformToFloatVector(
      const Transform&    pT,
      std::vector<float>& pTOut);

    /// <summary>
    /// DEPRECATED: Use toVector function.
    /// Return the Transform in a vector of float:
    ///
    /**
      * \f$ \begin{array}{cccc}
      * [r_1c_1, & r_1c_2, & r_1c_3, & r_1c_4, \\
      * r_2c_1, & r_2c_2, & r_2c_3, & r_2c_4, \\
      * r_3c_1, & r_3c_2, & r_3c_3, & r_3c_4, \\
      * 0.0, & 0.0, & 0.0, & 1.0]
      * \end{array}\f$
      */
    ///
    /// </summary>
    /// <param name="pT"> the given Transform </param>
    /// <returns>
    /// the vector of float update to given transform value
    /// </returns>
    /// \ingroup Types
    std::vector<float> transformToFloatVector(
      const Transform& pT);


    /// <summary>
    /// Compute the determinant of rotation part of the given Transform:
    ///
    /** \f$pT.r_1c_1*pT.r_2c_2*pT.r_3c_3 + pT.r_1c_2*pT.r_2c_3*pT.r_3c_1 +
      * pT.r_1c_3*pT.r_2c_1 * pT.r_3c_2 - pT.r_1c_1*pT.r_2c_3*pT.r_3c_2 -
      * pT.r_1c_2*pT.r_2c_1*pT.r_3c_3 - pT.r_1c_3*pT.r_2c_2*pT.r_3c_1\f$
      */
   /// </summary>
    /// <param name="pT"> the given Transform </param>
    /// <returns>
    /// the float determinant of rotation Transform part
    /// </returns>
    /// \ingroup Types
    float determinant(const Transform& pT);

    /// <summary>
    /// Compute the determinant of rotation part of the given vector of floats:
    ///
    /** \f$pT[0]*pT[5]*pT[10] + pT[1]*pT[6]*pT[8] +
      * pT[2]*pT[4]*pT[9] - pT[0]*pT[6]*pT[9] -
      * pT[1]*pT[4]*pT[10] - pT[2]*pT[5]*pT[8]\f$
      */
   /// </summary>
    /// <param name="pFloats"> the given vector of floats </param>
    /// <returns>
    /// the float determinant of rotation Transform part
    /// </returns>
    /// \ingroup Types
    float determinant(const std::vector<float>& pFloats);

    /// <summary>
    /// Return the transform inverse of the given Transform:
    ///
    /** \f$ pT = \left[\begin{array}{cc}
      * R & r \\
      * 0_{31} & 1
      * \end{array}\right]\f$
      */
    ///
    /** \f$ pTOut = \left[\begin{array}{cc}
      * R^t & (-R^t*r) \\
      * 0_{31} & 1
      * \end{array}\right]\f$
      */
    ///
    /// </summary>
    /// <param name="pT"> the given Transform </param>
    /// <param name="pTOut"> the inverse of the given Transform </param>
    /// \ingroup Types
    void transformInverse(
      const Transform& pT,
      Transform&       pTOut);

    /// <summary>
    /// Return the transform inverse of the given Transform:
    ///
    /** \f$ pT = \left[\begin{array}{cc}
      * R & r \\
      * 0_{31} & 1
      * \end{array}\right]\f$
      */
    ///
    /** \f$ pTOut = \left[\begin{array}{cc}
      * R^t & (-R^t*r) \\
      * 0_{31} & 1
      * \end{array}\right]\f$
      */
    ///
    /// </summary>
    /// <param name="pT"> the given Transform </param>
    /// <returns>
    /// the Transform inverse
    /// </returns>
    /// \ingroup Types
    Transform transformInverse(const Transform& pT);


    /// <summary>
    /// Create a Transform initialize with explicit rotation around x axis:
    ///
    /** \f$ pTOut = \left[\begin{array}{cccc}
      * 1.0 & 0.0 & 0.0 & 0.0 \\
      * 0.0 & cos(pRotX) & -sin(pRotX) & 0.0 \\
      * 0.0 & sin(pRotX) & cos(pRotX) & 0.0 \\
      * 0.0 & 0.0 & 0.0 & 1.0
      * \end{array}\right]\f$
      */
    ///
    /// </summary>
    /// <param name="pRotX"> the float value for angle rotation in radian around x axis </param>
    /// <returns>
    /// the Transform
    /// </returns>
    /// \ingroup Types
    Transform transformFromRotX(const float pRotX);

    /// <summary>
    /// Create a Transform initialize with explicit rotation around y axis:
    ///
    /** \f$ pTOut = \left[\begin{array}{cccc}
      * cos(pRotY) & 0.0 & sin(pRotY) & 0.0 \\
      * 0.0 & 1.0 & 0.0 & 0.0 \\
      * -sin(pRotY) & 0.0 & cos(pRotY) & 0.0 \\
      * 0.0 & 0.0 & 0.0 & 1.0
      * \end{array}\right]\f$
      */
   ///
    /// </summary>
    /// <param name="pRotY"> the float value for angle rotation in radian around y axis </param>
    /// <returns>
    /// the Transform
    /// </returns>
    /// \ingroup Types
    Transform transformFromRotY(const float pRotY);

    /// <summary>
    /// Create a Transform initialize with explicit rotation around z axis:
    ///
    /** \f$ pTOut = \left[\begin{array}{cccc}
      * cos(pRotZ) & -sin(pRotZ) & 0.0 & 0.0 \\
      * sin(pRotZ) & cos(pRotZ) & 0.0 & 0.0 \\
      * 0.0 & 0.0 & 1.0 & 0.0 \\
      * 0.0 & 0.0 & 0.0 & 1.0
      * \end{array}\right]\f$
      */
   ///
    /// </summary>
    /// <param name="pRotZ"> the float value for angle rotation in radian around z axis </param>
    /// <returns>
    /// the Transform
    /// </returns>
    /// \ingroup Types
    Transform transformFromRotZ(const float pRotZ);


    /// <summary>
    /// Create a Transform initialize with euler angle:
    /// H = fromRotZ(pWZ)*fromRotY(pWY)*fromRotX(pWX)
    ///
    /// </summary>
    /// <param name="pWX"> the float value for euler angle x in radian </param>
    /// <param name="pWY"> the float value for euler angle y in radian </param>
    /// <param name="pWZ"> the float value for euler angle z in radian </param>
    /// <returns>
    /// the Transform
    /// </returns>
    /// \ingroup Types
    Transform transformFrom3DRotation(
      const float& pWX,
      const float& pWY,
      const float& pWZ);

    /// <summary>
    /// Create a Transform initialize with explicit value for translation part:
    ///
    /** \f$ pTOut = \left[\begin{array}{cccc}
      * 1.0 & 0.0 & 0.0 & pX \\
      * 0.0 & 1.0 & 0.0 & pY \\
      * 0.0 & 0.0 & 1.0 & pZ \\
      * 0.0 & 0.0 & 0.0 & 1.0
      * \end{array}\right]\f$
      */
    ///
    /// </summary>
    /// <param name="pX"> the float value for translation axis x in meter (r1_c4) </param>
    /// <param name="pY"> the float value for translation axis y in meter (r2_c4) </param>
    /// <param name="pZ"> the float value for translation axis z in meter (r3_c4) </param>
    /// <returns>
    /// the Transform
    /// </returns>
    /// \ingroup Types
    Transform transformFromPosition(
      const float& pX,
      const float& pY,
      const float& pZ);

    /// <summary>
    /// Create a Transform initialize with explicit value for translation part and euler angle:
    ///
    /// H = fromRotZ(pWZ)*fromRotY(pWY)*fromRotX(pWX)
    ///
    /// H.r1_c4 = pX
    ///
    /// H.r2_c4 = pY
    ///
    /// H.r3_c4 = pZ
    ///
    /// </summary>
    /// <param name="pX"> the float value for translation axis x in meter (r1_c4) </param>
    /// <param name="pY"> the float value for translation axis y in meter (r2_c4) </param>
    /// <param name="pZ"> the float value for translation axis z in meter (r3_c4) </param>
    /// <param name="pWX"> the float value for euler angle x in radian </param>
    /// <param name="pWY"> the float value for euler angle y in radian </param>
    /// <param name="pWZ"> the float value for euler angle z in radian </param>
    /// <returns>
    /// the Transform
    /// </returns>
    /// \ingroup Types
    Transform transformFromPosition(
      const float& pX,
      const float& pY,
      const float& pZ,
      const float& pWX,
      const float& pWY,
      const float& pWZ);


    /// <summary>
    /// Inverse the given Transform in place:
    ///
    /// </summary>
    /// <param name="pT"> the given Transform </param>
    /// \ingroup Types
    void transformInvertInPlace(Transform& pT);


    /// <summary>
    /// Alternative name for inverse: return the transform inverse of the given Transform:
    ///
    /** \f$ pT = \left[\begin{array}{cc}
      * R & r \\
      * 0_{31} & 1
      * \end{array}\right]\f$
      */
    ///
    /** \f$ pTOut = \left[\begin{array}{cc}
      * R^t & (-R^t*r) \\
      * 0_{31} & 1
      * \end{array}\right]\f$
      */
    ///
    /// </summary>
    /// <param name="pT"> the given Transform </param>
    /// \ingroup Types
    Transform pinv(const Transform& pT);


    /// <summary>
    /// Compute the Transform between the actual Transform and the one give in argument result:
    ///
    /// inverse(pT1)*pT2
    ///
    /// </summary>
    /// <param name="pT1"> the first transform </param>
    /// <param name="pT2"> the second transform </param>
    /// <returns>
    /// the Transform
    /// </returns>
    /// \ingroup Types
    Transform transformDiff(
      const Transform& pT1,
      const Transform& pT2);

    /// <summary>
    /// Compute the squared distance between the actual
    /// Transform and the one give in argument (translation part):
    ///
    /// \f$(pT1.r_1c_4-pT2.r_1c_4)^2 +(pT1.r_2c_4-pT2.r_2c_4)^2+(pT1.r_3c_4-pT2.r_3c_4)^2\f$
    /// </summary>
    /// <param name="pT1"> the first Transform </param>
    /// <param name="pT2"> the second Transform </param>
    /// <returns>
    /// the float squared distance between the two Transform: translation part
    /// </returns>
    /// \ingroup Types
    float transformDistanceSquared(
      const Transform& pT1,
      const Transform& pT2);


    /// <summary>
    /// Compute the distance between the actual
    /// Transform and the one give in argument:
    ///
    /// \f$\sqrt{(pT1.r_1c_4-pT2.r_1c_4)^2+(pT1.r_2c_4-pT2.r_2c_4)^2+(pT1.r_3c_4-pT2.r_3c_4)^2}\f$
    /// </summary>
    /// <param name="pT1"> the first Transform </param>
    /// <param name="pT2"> the second Transform </param>
    /// <returns>
    /// the float distance between the two Transform
    /// </returns>
    /// \ingroup Types
    float transformDistance(
      const Transform& pT1,
      const Transform& pT2);

  } // end namespace Math
} // end namespace AL
#endif  // _LIBALMATH_ALMATH_TYPES_ALTRANSFORM_H_
