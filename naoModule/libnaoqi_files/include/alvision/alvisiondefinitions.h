/**
 * @author Pierre-Emmanuel VIEL
 * Copyright (c) Aldebaran Robotics 2008, 2011 All Rights Reserved
 */

#pragma once
#ifndef _LIBALVISION_ALVISION_ALVISIONDEFINITIONS_H_
#define _LIBALVISION_ALVISION_ALVISIONDEFINITIONS_H_

/** \file alvision/alvisiondefinitions.h
 *  \brief vision defines
 */

namespace AL
{
  #define TORAD  3.14f/180.0f

  /**
  *Camera Model ID
  */
  const int kOV7670  = 1;
  const int kMT9M114 = 2;
  const int kOV5640  = 3;
  const int kXTION   = 4;

  /**
  *Camera Index
  */
  const int kTopCamera = 0;
  const int kBottomCamera = 1;
  const int kDepthCamera = 2;

  /**
  *Cameras aperture
  * @deprecated Should not be exposed.
  */
  const float kApertureH_OV7670  = 47.8f; //!< @deprecated since 1.16
  const float kApertureV_OV7670  = 36.8f; //!< @deprecated since 1.16
  const float kApertureH_MT9M114 = 60.9f; //!< @deprecated since 1.16
  const float kApertureV_MT9M114 = 47.6f; //!< @deprecated since 1.16

  /**
  *Format of the image
  */
  const int kQQVGA = 0;  // 160*120
  const int kQVGA  = 1;  // 320*240
  const int kVGA   = 2;  // 640*480
  const int k4VGA  = 3;  //1280*960
  const int k960p  = k4VGA;  //deprecated
  const int k16VGA = 4;  //2560*1920
  const int k1920p = k16VGA;  //2560*1920
  const int k720p = 5;  //1280*720
  const int k1080p = 6;  //1920*1080
  const int kQQQVGA = 7;  // 80*60
  const int kQQQQVGA = 8;  // 40*30

  /**
  *ColorSpace
  */
  const int kYuvColorSpace = 0;
  const int kyUvColorSpace = 1;
  const int kyuVColorSpace = 2;
  const int kRgbColorSpace = 3;
  const int krGbColorSpace = 4;
  const int krgBColorSpace = 5;
  const int kHsyColorSpace = 6;
  const int khSyColorSpace = 7;
  const int khsYColorSpace = 8;
  const int kYUV422ColorSpace = 9;
  const int kYUV422InterlacedColorSpace = kYUV422ColorSpace; // deprecated
  const int kYUVColorSpace = 10;
  const int kRGBColorSpace = 11;
  const int kHSYColorSpace = 12;
  const int kBGRColorSpace = 13;     // for opencv ease of use
  const int kYYCbCrColorSpace = 14;  // for tiff io implementation
  const int kH2RGBColorSpace = 15;   // H from HSY to RGB in fake colors
  const int kHSMixedColorSpace = 16; // HS and (H +S)/2
  const int kDepthColorSpace = 17;
  const int kARGBColorSpace = 18;
  const int kXYZColorSpace = 19;
  const int kInfraredColorSpace = 20;
  const int kDistanceColorSpace = 21; //!< @since 1.22

  /**
   *Standard Id (used for camera registers configuration)
   */
  const int kCameraBrightnessID       = 0;
  const int kCameraContrastID         = 1;
  const int kCameraSaturationID       = 2;
  const int kCameraHueID              = 3;
  const int kCameraRedChromaID        = 4;
  const int kCameraBlueChromaID       = 5;
  const int kCameraGainID             = 6;
  const int kCameraHFlipID            = 7;
  const int kCameraVFlipID            = 8;
  const int kCameraLensXID            = 9;
  const int kCameraLensYID            = 10;
  const int kCameraAutoExpositionID   = 11;
  const int kCameraAutoWhiteBalanceID = 12;
  const int kCameraAutoGainID         = 13;
  const int kCameraResolutionID       = 14;
  const int kCameraFrameRateID        = 15;
  const int kCameraBufferSizeID       = 16;
  const int kCameraExposureID         = 17;
  const int kCameraSelectID           = 18;
  const int kCameraSetDefaultParamsID = 19;
  const int kCameraColorSpaceID       = 20;
  const int kCameraExposureCorrectionID = 21;
  const int kCameraExposureAlgorithmID = 22;
  const int kCameraAecAlgorithmID     = kCameraExposureAlgorithmID; // deprecated
  const int kCameraFastSwitchID       = 23;
  const int kCameraSharpnessID        = 24;
  const int kCameraAwbGreenGainID     = 25;
  const int kCameraAblcID             = 26;
  const int kCameraAblcTargetID       = 27;
  const int kCameraAblcStableRangeID  = 28;
  const int kCameraBlcBlueID          = 29;
  const int kCameraBlcRedID           = 30;
  const int kCameraBlcGbID            = 31;
  const int kCameraBlcGrID            = 32;
  const int kCameraWhiteBalanceID     = 33;
  const int kCameraBacklightCompensationID = 34;
  const int kCameraKeepAliveID        = 35; //!< @since 1.16
  const int kCameraDepthConfidenceThresholdID = 36; //!< @since 1.16
  const int kCameraDepthFastFilterID  = 37; //!< @since 1.16
  const int kCameraTemperatureID      = 38; //!< @since 1.18
  const int kCameraAverageLuminanceID = 39; //!< @since 1.22.2
  const int kCameraAutoFocusID = 40; //!< @since 1.22.4

  /*! @brief Utility function that checks that a resolution index is valid.
  * (ie, present in the definitions just above)*/
  bool isResolutionValid(const int resIndex);

  /*! @brief Utility function that takes a resolution index as an input and returns
   * the corresponding width and height values.
   * If resolution index is unknown, width and height are set to -1.*/
  void setSizeFromResolution(const int resIndex, int& outWidth, int& outHeight);

  /*! @brief Utility function that takes width and height as inputs and returns the
   * corresponding resolution index.
   * @return The resolution index otherwise return -1.*/
  int getResolutionFromSize(const int width, const int height);

  /*! @brief Utility function that checks that a color space index is valid.
  * (ie, present in the definitions just above)*/
  bool isColorSpaceValid(const int colorspace);

  /*! @brief Utility function that returns the number of layers for a given color space.
  * @return the number of byte the colorspace use, otherwise returns -1 for unknown colorspace.
  * @note Since this method is use by AL::ALImage to allocate memory with the
  * assumption of 1 layer is stored in 1 byte. Thus if the color space store some channel
  * in a 16bits container (e.g. Depth map), method will return 2 instead of 1.
  */
  int getNumLayersInColorSpace(const int colorSpace);

  /*!
   * @brief Utility function that returns the number of channels for a given color space.
   * @return The number of channels for this color space.
   * @note This method assumes that the data is stored with the correct type,
   * for example it will return 1 for the AL::kDepthColorSpace because it corresponds
   * to a 1-channel unsigned short image buffer, although it uses two layers.
   */
  int getNumChannelsInColorSpace(const int colorSpace);

  inline float convertAngleValToNormalizedImgVal(const float& radValue,
                                                 const float& imageRadMin,
                                                 const float& imageRadMax)
    { return ( radValue / (imageRadMax-imageRadMin)); }

  inline float convertAnglePosToNormalizedImgPos(const float& radPosition,
                                                 const float& imageRadMin,
                                                 const float& imageRadMax)
    { return ((radPosition-imageRadMin) / (imageRadMax-imageRadMin)); }
} // namespace AL


#endif  // _LIBALVISION_ALVISION_ALVISIONDEFINITIONS_H_
