/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */


#pragma once
#ifndef _LIBALMATH_ALMATH_TOOLS_ALTRANSFORMHELPERS_H_
#define _LIBALMATH_ALMATH_TOOLS_ALTRANSFORMHELPERS_H_

#include <almath/types/alposition2d.h>
#include <almath/types/alposition3d.h>
#include <almath/types/alposition6d.h>
#include <almath/types/alrotation.h>
#include <almath/types/alrotation3d.h>
#include <almath/types/alvelocity6d.h>
#include <almath/types/altransform.h>
#include <almath/types/alaxismask.h>
#include <almath/types/alpose2d.h>
#include <almath/types/alquaternion.h>
#include <almath/types/aldisplacement.h>

namespace AL {
  namespace Math {


  /// <summary>
  /// Compute the logarithme of a transform.
  /// Angle must be between \f$\left[-\pi+0.001, \pi-0.001\right]\f$
  /**
    * Cette fonction calcule le
    * logarithme associe a une matrice de type Deplacement -
    * matrice homogene 4x4 (SE3)
    * La sortie est un torseur cinematique de se3.
    * Le resultat n'est garanti que pour des angles dans [-pi+0.001,pi-0.001].
    * cette fonction calcule la differentielle du logarithme associe
    * a une matrice de type Deplacement - matrice homogene 4x4 (SE3).
    */
  /// </summary>
  /// <param name="pT"> the given Transform </param>
  /// <param name="pVel"> the given Transform </param>
  /// <returns>
  /// the Velocity6D logarithme: kinematic screw in se3
  /// </returns>
  /// \ingroup Tools
  void transformLogarithmInPlace(
    const Transform& pT,
    Velocity6D&      pVel);


    /// <summary>
    /// Compute the logarithme of a transform.
    /// Angle must be between \f$\left[-\pi+0.001, \pi-0.001\right] \f$
    /**
      * Cette fonction calcule le
      * logarithme associe a une matrice de type Deplacement -
      * matrice homogene 4x4 (SE3)
      * La sortie est un torseur cinematique de se3.
      * Le resultat n'est garanti que pour des angles dans [-pi+0.001,pi-0.001].
      * cette fonction calcule la differentielle du logarithme associe
      * a une matrice de type Deplacement - matrice homogene 4x4 (SE3).
      */
    /// </summary>
    /// <param name="pT"> the given Transform </param>
    /// <returns>
    /// the Velocity6D logarithme: kinematic screw in se3
    /// </returns>
    /// \ingroup Tools
    Velocity6D transformLogarithm(const Transform& pT);


    /// <summary>
    /// Compute the logarithme of a transform.
    /// Angle must be between \f$\left[-\pi+0.001, \pi-0.001\right] \f$
    /**
      * Function Velocity Exponential: compute homogenous matrix
      * displacement from a dt * 6D velocity vector.
      */
    /// </summary>
    /// <param name="pVel"> the given Velocity6D </param>
    /// <returns>
    /// the Velocity6D logarithme: kinematic screw in se3
    /// </returns>
    /// \ingroup Tools
    Transform velocityExponential(const Velocity6D& pVel);

    // TODO: Add to doc or set private.
    void velocityExponentialInPlace(
      const Velocity6D& pVel,
      Transform&        pT);

    /// <summary>
    /** \f$ \left[\begin{array}{c}
      * pVOut.xd  \\
      * pVOut.yd  \\
      * pVOut.zd  \\
      * pVOut.wxd \\
      * pVOut.wyd \\
      * pVOut.wzd \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{cccccc}
      * r_1c_1 & r_1c_2 & r_1c_3 & 0 & 0 & 0 \\
      * r_2c_1 & r_2c_2 & r_2c_3 & 0 & 0 & 0 \\
      * r_3c_1 & r_3c_2 & r_3c_3 & 0 & 0 & 0 \\
      * 0 & 0 & 0 & r_1c_1 & r_1c_2 & r_1c_3 \\
      * 0 & 0 & 0 & r_2c_1 & r_2c_2 & r_2c_3 \\
      * 0 & 0 & 0 & r_3c_1 & r_3c_2 & r_3c_3 \\
      * \end{array}\right]
      *
      * \left[\begin{array}{c}
      * pVIn.xd  \\
      * pVIn.yd  \\
      * pVIn.zd  \\
      * pVIn.wxd \\
      * pVIn.wyd \\
      * pVIn.wzd \\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the given Transform </param>
    /// <param name = "pVelIn"> a Velocity6D containing the velocity
    /// to change
    /// </param>
    /// <param name = "pVelOut">  a Velocity6D containing the changed velocity
    /// </param>
    /// \ingroup Tools
    void changeReferenceVelocity6D(
      const Transform&  pT,
      const Velocity6D& pVelIn,
      Velocity6D&       pVelOut);

    /// <summary>
    /** \f$ \left[\begin{array}{c}
      * pPOut.x  \\
      * pPOut.y  \\
      * pPOut.z  \\
      * pPOut.wx \\
      * pPOut.wy \\
      * pPOut.wz \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{cccccc}
      * r_1c_1 & r_1c_2 & r_1c_3 & 0 & 0 & 0 \\
      * r_2c_1 & r_2c_2 & r_2c_3 & 0 & 0 & 0 \\
      * r_3c_1 & r_3c_2 & r_3c_3 & 0 & 0 & 0 \\
      * 0 & 0 & 0 & r_1c_1 & r_1c_2 & r_1c_3 \\
      * 0 & 0 & 0 & r_2c_1 & r_2c_2 & r_2c_3 \\
      * 0 & 0 & 0 & r_3c_1 & r_3c_2 & r_3c_3 \\
      * \end{array}\right]
      *
      * \left[\begin{array}{c}
      * pPIn.x  \\
      * pPIn.y  \\
      * pPIn.z  \\
      * pPIn.wx \\
      * pPIn.wy \\
      * pPIn.wz \\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the given Transform </param>
    /// <param name = "pPosIn"> a Position6D containing the position
    /// to change
    /// </param>
    /// <param name = "pPosOut">  a Position6D containing the changed position
    /// </param>
    /// \ingroup Tools
    void changeReferencePosition6D(
      const Transform&  pT,
      const Position6D& pPosIn,
      Position6D&       pPosOut);

    // TODO: rename argument.
    void changeReferencePosition3DInPlace(
      const Transform& pT,
      Position3D&      pPosOut);

    // TODO: rename argument.
    void changeReferenceTransposePosition3DInPlace(
      const Transform& pT,
      Position3D&      pPosOut);

    /// <summary>
    /** \f$ \left[\begin{array}{c}
      * pPosOut.x \\
      * pPosOut.y \\
      * pPosOut.z \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{ccc}
      * r_1c_1 & r_1c_2 & r_1c_3\\
      * r_2c_1 & r_2c_2 & r_2c_3\\
      * r_3c_1 & r_3c_2 & r_3c_3\\
      * \end{array}\right]
      *
      * \left[\begin{array}{c}
      * pPosIn.x \\
      * pPosIn.y \\
      * pPosIn.z \\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the given Transform </param>
    /// <param name = "pPosIn"> a Position3D containing the position
    /// to change
    /// </param>
    /// <param name = "pPosOut"> a Position3D containing the changed position
    /// </param>
    /// \ingroup Tools
    void changeReferencePosition3D(
      const Transform&  pT,
      const Position3D& pPosIn,
      Position3D&       pPosOut);

    /// <summary>
    /** \f$ \left[\begin{array}{c}
      * pTOut \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{c}
      * pT
      * \end{array}\right]
      * \left[\begin{array}{c}
      * pTIn \\
      * \end{array}\right]^T
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the given Transform </param>
    /// <param name = "pPosIn"> a Position3D containing the position to change
    /// </param>
    /// <param name = "pPosOut"> a Position3D containing the changed position
    /// </param>
    /// \ingroup Tools
    void changeReferenceTransposePosition3D(
      const Transform&  pT,
      const Position3D& pPosIn,
      Position3D&       pPosOut);

    /// <summary>
    /** \f$ \left[\begin{array}{c}
      * pTOut \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{c}
      * pT
      * \end{array}\right]
      * \left[\begin{array}{c}
      * pTIn \\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the given Transform </param>
    /// <param name = "pTIn"> the Transform to change
    /// </param>
    /// <param name = "pTOut"> the changed Transform
    /// </param>
    /// \ingroup Tools
    void changeReferenceTransform(
      const Transform& pT,
      const Transform& pTIn,
      Transform&       pTOut);

    /// <summary>
    /** \f$ \left[\begin{array}{c}
      * pTOut \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{c}
      * pT
      * \end{array}\right]
      * \left[\begin{array}{c}
      * pTIn \\
      * \end{array}\right]^T
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the given Transform </param>
    /// <param name = "pTIn"> the Transform to change
    /// </param>
    /// <param name = "pTOut"> the changed Transform
    /// </param>
    /// \ingroup Tools
    void changeReferenceTransposeTransform(
      const Transform& pT,
      const Transform& pTIn,
      Transform&       pTOut);


    /// <summary>
    /** \f$ \left[\begin{array}{c}
      * pVOut.xd  \\
      * pVOut.yd  \\
      * pVOut.zd  \\
      * pVOut.wxd \\
      * pVOut.wyd \\
      * pVOut.wzd \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{cccccc}
      * r_1c_1 & r_2c_1 & r_3c_1 & 0 & 0 & 0 \\
      * r_1c_2 & r_2c_2 & r_3c_2 & 0 & 0 & 0 \\
      * r_1c_3 & r_2c_3 & r_3c_3 & 0 & 0 & 0 \\
      * 0 & 0 & 0 & r_1c_1 & r_2c_1 & r_3c_1 \\
      * 0 & 0 & 0 & r_1c_2 & r_2c_2 & r_3c_2 \\
      * 0 & 0 & 0 & r_1c_3 & r_2c_3 & r_3c_3 \\
      * \end{array}\right]
      *
      * \left[\begin{array}{c}
      * pVIn.xd  \\
      * pVIn.yd  \\
      * pVIn.zd  \\
      * pVIn.wxd \\
      * pVIn.wyd \\
      * pVIn.wzd \\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the given Transform </param>
    /// <param name = "pVelIn"> a Velocity6D containing the velocity
    /// to change
    /// </param>
    /// <param name = "pVelOut">  a Velocity6D containing the changed velocity
    /// </param>
    /// \ingroup Tools
    void changeReferenceTransposeVelocity6D(
      const Transform&  pT,
      const Velocity6D& pVelIn,
      Velocity6D&       pVelOut);

    /// <summary>
    /** \f$ \left[\begin{array}{c}
      * pPOut.x  \\
      * pPOut.y  \\
      * pPOut.z  \\
      * pPOut.wx \\
      * pPOut.wy \\
      * pPOut.wz \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{cccccc}
      * r_1c_1 & r_2c_1 & r_3c_1 & 0 & 0 & 0 \\
      * r_1c_2 & r_2c_2 & r_3c_2 & 0 & 0 & 0 \\
      * r_1c_3 & r_2c_3 & r_3c_3 & 0 & 0 & 0 \\
      * 0 & 0 & 0 & r_1c_1 & r_2c_1 & r_3c_1 \\
      * 0 & 0 & 0 & r_1c_2 & r_2c_2 & r_3c_2 \\
      * 0 & 0 & 0 & r_1c_3 & r_2c_3 & r_3c_3 \\
      * \end{array}\right]
      *
      * \left[\begin{array}{c}
      * pPIn.x  \\
      * pPIn.y  \\
      * pPIn.z  \\
      * pPIn.wx \\
      * pPIn.wy \\
      * pPIn.wz \\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the given Transform </param>
    /// <param name = "pPosIn"> a Position6D containing the position
    /// to change
    /// </param>
    /// <param name = "pPosOut">  a Position6D containing the changed position
    /// </param>
    /// \ingroup Tools
    void changeReferenceTransposePosition6D(
      const Transform&  pT,
      const Position6D& pPosIn,
      Position6D&       pPosOut);

    /// <summary>
    /// Preform a logarithmic mean of pTIn1 and pTIn2 and put it in pTout.
    /// </summary>
    /// <param name = "pTIn1"> the first given Transform </param>
    /// <param name = "pTIn2"> the second given Transform </param>
    /// <param name = "pVal"> the value between 0 and 1 used in the logarithmic
    /// mean </param>
    /// <param name = "pTOut">  the output Transform.
    /// </param>
    /// \ingroup Tools
    void transformMeanInPlace(
      const Transform& pTIn1,
      const Transform& pTIn2,
      const float&     pVal,
      Transform&       pTOut);

    /// <summary>
    /// Preform a logarithmic mean of pTIn1 and pTIn2.
    /// </summary>
    /// <param name = "pTIn1"> cartesian coordinates </param>
    /// <param name = "pTIn2"> the given Transform </param>
    /// <param name = "pVal"> the value between 0 and 1 used in the logarithmic
    /// mean, 0.5 by default </param>
    /// <returns>
    /// a Transform with the mean of pTIn1 and pTIn2
    /// </returns>
    /// \ingroup Tools
    Transform transformMean(
      const Transform& pTIn1,
      const Transform& pTIn2,
      const float&     pVal = 0.5f);

    /// <summary>
    /// Create a Transform from 3D cartesian coordiantes and a Rotation.
    /**
      * \f$ T = \left[\begin{array}{cccc}
      * pRot.r_1c_1 & pRot.r_1c_2 & pRot.r_1c_3 & pX \\
      * pRot.r_2c_1 & pRot.r_2c_2 & pRot.r_2c_3 & pY \\
      * pRot.r_3c_1 & pRot.r_3c_2 & pRot.r_3c_3 & pZ \\
      * 0.0 & 0.0 & 0.0 & 1.0 \end{array}\right] \f$
      */
    /// </summary>
    /// <param name="pRot"> the given Rotation </param>
    /// <param name="pX"> the translation along x axis </param>
    /// <param name="pY"> the translation along y axis </param>
    /// <param name="pZ"> the translation along z axis </param>
    /// <returns>
    /// the Transform result.
    /// </returns>
    /// \ingroup Tools
    Transform transformFromRotationPosition3D(
      const Rotation& pRot,
      const float&    pX,
      const float&    pY,
      const float&    pZ);

    /// <summary>
    /// Create a Transform from a Position3D and a Rotation.
    /** \f$ T = \left[\begin{array}{cccc}
      * pRot.r_1c_1 & pRot.r_1c_2 & pRot.r_1c_3 & pPos.x \\
      * pRot.r_2c_1 & pRot.r_2c_2 & pRot.r_2c_3 & pPos.y \\
      * pRot.r_3c_1 & pRot.r_3c_2 & pRot.r_3c_3 & pPos.z \\
      * 0.0 & 0.0 & 0.0 & 1.0 \end{array}\right] \f$
      */
    /// </summary>
    /// <param name="pPos"> the given Position3D </param>
    /// <param name="pRot"> the given Rotation </param>
    /// <returns>
    /// the Transform result.
    /// </returns>
    /// \ingroup Tools
    Transform transformFromRotationPosition3D(
      const Rotation&   pRot,
      const Position3D& pPos);

    /// <summary>
    /// Modify pTransform to set the translation part to pPosition.
    /** \f$
      * \left[\begin{array}{c}
      *   Transform \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{cc}
      *   pRotation& *_{3,1}\\
      *   0_{1,3} & 1\\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pPosition"> a Position3D cartesian coordinates </param>
    /// <param name = "pTransform"> the given Transform </param>
    /// \ingroup Tools
    void transformFromPosition3DInPlace(
      const Position3D& pPosition,
      Transform&        pTransform);

    /// <summary>
    /// Create a 4*4 transform matrix from cartesian coordinates
    /// given in pPosition.
    /** \f$
      * \left[\begin{array}{c}
      *   Transform \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{cc}
      *   pRotation& *_{3,1}\\
      *   0_{1,3} & 1\\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pPosition"> position in cartesian coordinates </param>
    /// <returns>
    /// a Transform with the translation part initialized to pPosition, rotation
    /// part is set to identity
    /// </returns>
    /// \ingroup Tools
    Transform transformFromPosition3D(const Position3D& pPosition);

    /// <summary>
    /// Modify the rotation part of the transform.
    /// The translation part of the transform is not modified.
    /** \f$
      * \left[\begin{array}{c}
      *   Transform \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{cc}
      *   pRotation& *_{3,1}\\
      *   0_{1,3} & 1\\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pRotation"> the given Rotation </param>
    /// <param name = "pTransform"> the Transform to modify </param>
    /// \ingroup Tools
    void transformFromRotationInPlace(
      const Rotation& pRotation,
      Transform&      pTransform);

    /// <summary>
    /** \f$
      * \left[\begin{array}{c}
      *   Transform \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{cc}
      *   pRotation& 0_{3,1}\\
      *   0_{1,3} & 1\\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pRotation"> the given Rotation </param>
    /// <returns>
    /// a Transform with the rotation part initialized to pRotation
    /// </returns>
    /// \ingroup Tools
    Transform transformFromRotation(const Rotation& pRotation);

    /// <summary>
    /// Extract the position coordinates from a Transform.
    /// </summary>
    /// <param name = "pTransform"> the given transform </param>
    /// <param name = "pRotation"> a Rotation to be set with the reslut </param>
    /// \ingroup Tools
    void rotationFromTransformInPlace(
      const Transform& pTransform,
      Rotation&        pRotation);

    /// <summary>
    ///
    /// </summary>
    /// <param name = "pTransform"> position in cartesian coordinates </param>
    /// <returns>
    /// the Rotation extracted from the Transform
    /// </returns>
    /// \ingroup Tools
    Rotation rotationFromTransform(const Transform& pTransform);

    /// <summary>
    /// return 3 angles which result in the equivalent rotation when composed
    /// in the following order: Rz(wz) * Ry(wy) * Rx(wx) = R
    /// </summary>
    /// <param name = "pRotation"> the Rotation to extract </param>
    /// <returns>
    /// the Rotation3D extracted from pRotation
    /// </returns>
    /// \ingroup Tools
    Rotation3D rotation3DFromRotation(const Rotation& pRotation);

    /// <summary>
    /// Compute Position6D corresponding to the Transform.
    /// </summary>
    /// <param name = "pT"> the transform you want to extract </param>
    /// <param name = "pPos"> the transform you want to extract </param>
    /// \ingroup Tools
    void position6DFromTransformInPlace(
        const Transform& pT,
        Position6D&      pPos);

    /// <summary>
    /// Compute Position6D corresponding to 4*4 Homogenous Transform.
    /// </summary>
    /// <param name = "pT"> the transform you want to extract </param>
    /// <returns> the extracted Position6D </returns>
    /// \ingroup Tools
    Position6D position6DFromTransform(const Transform& pT);

    /// <summary>
    /// Compute a Transform from a Pose2D.
    /// </summary>
    /// <param name = "pPose"> the Pose2D to extract </param>
    /// <param name = "pT"> the result Transform </param>
    /// \ingroup Tools
    void transformFromPose2DInPlace(
        const Pose2D& pPose,
        Transform&    pT);

    /// <summary>
    /// Create a Transform from a Pose2D.
    /// </summary>
    /// <param name = "pPose"> the pose2D you want to extract </param>
    /// <returns> the result Transform </returns>
    /// \ingroup Tools
    Transform transformFromPose2D(const Pose2D& pPose);

    /// <summary>
    /// Compute a Pose2D from a Transform.
    /// </summary>
    /// <param name = "pT"> the Transform you want to extract </param>
    /// <param name = "pPos"> the result Pose2D </param>
    /// \ingroup Tools
    void pose2DFromTransformInPlace(
        const Transform& pT,
        Pose2D&          pPos);

    /// <summary>
    /// Create a Pose2D from a Transform.
    /// </summary>
    /// <param name = "pT"> the transform you want to extract </param>
    /// <returns> the Pose2D extracted from the Transform </returns>
    /// \ingroup Tools
    Pose2D pose2DFromTransform(const Transform& pT);

    /// <summary>
    /// Compute a Position2D from a Transform.
    /// </summary>
    /// <param name = "pT"> the Transform you want to extract </param>
    /// <param name = "pPos"> the result Position2D </param>
    /// \ingroup Tools
    void position2DFromTransformInPlace(
        const Transform&     pT,
        Position2D&          pPos);

    /// <summary>
    /// Create a Position2D from a Transform.
    /// </summary>
    /// <param name = "pT"> the transform you want to extract </param>
    /// <returns> the Position2D extracted from the Transform </returns>
    /// \ingroup Tools
    Position2D position2DFromTransform(const Transform& pT);

    /// <summary>
    /// Create a Transform from the 3 angles stored in a Rotation3D.
    /// The angles are composed in the following order:
    /// Rz(wz) * Ry(wy) * Rx(wx) = R
    /// </summary>
    /// <param name = "pRotation"> the Rotation you want to extract </param>
    /// <returns> the result Transform </returns>
    /// \ingroup Tools
    Transform transformFromRotation3D(const Rotation3D& pRotation);

    /// <summary>
    /// Create a Transform from a Position6D.
    /// </summary>
    /// <param name = "pPosition6D"> the Position6D you want to extract </param>
    /// <returns> the result Transform </returns>
    /// \ingroup Tools
    Transform transformFromPosition6D(const Position6D& pPosition6D);

    /// <summary>
    /// Computes a 6 differential motion require to move
    /// from a 4*4 Homogenous transform matrix Current to
    /// a 4*4 Homogenous transform matrix target.
    ///
    /// For instance, one would do
    ///
    ///     Position6D P_a;
    ///     position6DFromTransformDiffInPlace(H_ab, H_ac, P)
    ///
    /// Now P contains (an approximation of) the dispacement from the frame b
    /// to the frame c, expressed at the origin of frame b, and in the basis
    /// of frame a
    /// </summary>
    /// <param name = "pCurrent"> the Position6D you want to extract </param>
    /// <param name = "pTarget"> the Position6D you want to extract </param>
    /// <param name = "result"> the result Position6D </param>
    /// \ingroup Tools
    void position6DFromTransformDiffInPlace(
      const Transform& pCurrent,
      const Transform& pTarget,
      Position6D&      result);

    /// <summary>
    /// Computes a 6 differential motion require to move
    /// from a 4*4 Homogenous transform matrix Current to
    /// a 4*4 Homogenous transform matrix target.
    /// </summary>
    /// <param name = "pCurrent"> the Position6D you want to extract </param>
    /// <param name = "pTarget"> the Position6D you want to extract </param>
    /// <returns> the result Position6D </returns>
    /// \ingroup Tools
    Position6D position6DFromTransformDiff(
      const Transform& pCurrent,
      const Transform& pTarget);

    /// <summary>
    /// Compute a Position3D from a Transform.
    ///
    /** \f$
      * \left[\begin{array}{c}
      *   pPos.x \\
      *   pPos.y \\
      *   pPos.z \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{c}
      *   pT.r_1c_4 \\
      *   pT.r_2c_4 \\
      *   pT.r_3c_4 \\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the Transform you want to extract </param>
    /// <param name = "pPos"> the result Position3D </param>
    /// \ingroup Tools
    void position3DFromTransformInPlace(
      const Transform& pT,
      Position3D&      pPos);

    /// <summary>
    /// Create a Position3D from a Transform.
    ///
    /** \f$
      * \left[\begin{array}{c}
      *   return.x \\
      *   return.y \\
      *   return.z \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{c}
      *   pT.r_1c_4 \\
      *   pT.r_2c_4 \\
      *   pT.r_3c_4 \\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the Transform you want to extract </param>
    /// <returns> the result Position6D </returns>
    /// \ingroup Tools
    Position3D position3DFromTransform(const Transform& pT);


    /// <summary>
    /// Create a Rotation3D (Roll, Pitch, Yaw) corresponding to the rotational
    /// part of the Transform.
    /// R =  Rz(wz) * Ry(wy) * Rx(wx)
    /// </summary>
    /// <param name = "pT"> the Transform you want to extract </param>
    /// <returns> the result Rotation3D </returns>
    /// \ingroup Tools
    Rotation3D rotation3DFromTransform(const Transform& pT);

    /// <summary>
    /// Compute a Transform from
    /// </summary>
    /// <param name = "pAxis"> the Rotation you want to extract </param>
    /// <param name = "pTheta"> the rotation you want to extract </param>
    /// <param name = "pPos"> the Position3D you want to extract </param>
    /// <param name = "pT"> the Rotation you want to extract </param>
    /// \ingroup Tools
    void transformFromRotVecInPlace(
      const int         pAxis,
      const float       pTheta,
      const Position3D& pPos,
      Transform&        pT);

    /// <summary>
    /// </summary>
    /// <param name = "pAxis"> the Rotation you want to extract </param>
    /// <param name = "pTheta"> the Rotation you want to extract </param>
    /// <param name = "pPos"> the Rotation you want to extract </param>
    /// <returns> the result Transform </returns>
    /// \ingroup Tools
    Transform transformFromRotVec(
      const int         pAxis,
      const float       pTheta,
      const Position3D& pPos);


    /// <summary>
    /// </summary>
    /// <param name = "pPos"> the Rotation you want to extract </param>
    /// <param name = "pT"> the Rotation you want to extract </param>
    /// \ingroup Tools
    void transformFromRotVecInPlace(
      const Position3D& pPos,
      Transform&        pT);

    /// <summary>
    /// </summary>
    /// <param name = "pPos"> the Rotation you want to extract </param>
    /// <returns> the result Transform </returns>
    /// \ingroup Tools
    Transform transformFromRotVec(const Position3D& pPos);

    /// <summary>
    /// </summary>
    /// <param name = "pAxis"> the Rotation you want to extract </param>
    /// <param name = "pTheta"> the Rotation you want to extract </param>

    /// <returns> the result Transform </returns>
    /// \ingroup Tools
    Transform transformFromRotVec(
      const int&   pAxis,
      const float& pTheta);

    Position3D operator*(
      const Transform&  pT,
      const Position2D& pPos);

    Position3D operator*(
      const Transform&  pT,
      const Position3D& pPos);

    /**
    * Function axisRotationProjection:
    * finding the closest rotation Rw of R around an axis (Position3D)
    * @param pAxis: axis of rotation
    * @param pT: a transform
    * @return Transform
    **/
    Transform axisRotationProjection(
      const Position3D& pAxis,
      const Transform&  pT);

    /**
    * Function axisRotationProjection:
    * finding the closest rotation Rw of R around an axis (Position3D)
    * @param pAxis: axis of rotation
    * @param pRot: a rotation
    * @return Rotation
    **/
    Rotation axisRotationProjection(
      const Position3D& pAxis,
      const Rotation&   pRot);


    /**
    * Function axisRotationProjectionInPlace:
    * finding the closest rotation Rw of R around an axis (Position3D)
    * @param pAxis: axis of rotation
    * @param pT: a transform
    **/
    void axisRotationProjectionInPlace(
      const Position3D& pAxis,
      Transform&        pT);

    /**
    * Function axisRotationProjectionInPlace:
    * finding the closest rotation Rw of R around an axis (Position3D)
    * @param pAxis: axis of rotation
    * @param pRot: a rotation
    **/
    void axisRotationProjectionInPlace(
      const Position3D& pAxis,
      Rotation&         pRot);

    /**
    * Function orthogonalSpace:
    * create an orthonormal direct base from a vector (Position3D)
    * @param pPos: a vector of direction
    * @param pTf: the result transform
    **/
    void orthogonalSpace(
      const Position3D& pPos,
      Transform&        pTf);

    Transform orthogonalSpace(const Position3D& pPos);

    Transform transformFromQuaternion(
      const Quaternion& pQua);

    Quaternion quaternionFromTransform(
      const Transform& pT);

    /**
    * Function transformFromDisplacement:
    * computing the transform equivalent to the displacement
    * @param pDisp: a displacement
    * @return computed Transform
    **/
    Transform transformFromDisplacement(const Displacement& pDisp);

    /**
    * Function displacementFromTransform:
    * computing the displacement equivalent to the transform
    * @param pTrans: a transform
    * @return computed Displacement
    **/
    Displacement displacementFromTransform(const Transform& pTrans);

  } // namespace Math
} // namespace AL
#endif  // _LIBALMATH_ALMATH_TOOLS_ALTRANSFORMHELPERS_H_
