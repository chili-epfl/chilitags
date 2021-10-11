/**
 * @author Vincent Rabaud
 * Aldebaran Robotics (c) 2013 All Rights Reserved
 */

/** Set of functions to convert between ALImage and cv::Mat
 * This is a header only implementation to be totally independent from OpenCV
 * If you include this header, make sure you link properly to OPENCV2_CORE
 */
#ifndef LIBALVISION_ALVISION_ALIMAGE_OPENCV_H_
#define LIBALVISION_ALVISION_ALIMAGE_OPENCV_H_

#include <cstring> // for std::memcpy
#include <opencv2/core/core.hpp>

#include <alerror/alerror.h>

#include "alimage.h"
#include "alvisiondefinitions.h"

namespace AL
{
/** Converts an ALImage to an OpenCV cv::Mat by NOT copying the data over: the cv::Mat does not own the data and will
 * not delete it in its destructor. If you want to copy the data, just .clone the output cv::Mat()
 * @param al_image
 * @param cv_type if provided, it interprets the content of al_image as such
 * @return
 */
static inline cv::Mat aLImageToCvMat(const AL::ALImage & al_image, int cv_type = -1)
{
  // OpenCV does not take a const void* because the object could be modified later. This pointer will only be used
  // in a tmp local cv::Mat so it's fine
  unsigned char *data = const_cast<unsigned char*>(al_image.getData());

  if (cv_type >= 0)
    return cv::Mat(al_image.getHeight(), al_image.getWidth(), cv_type, data);

  // Check the types
  int n_layers = AL::getNumLayersInColorSpace(al_image.getColorSpace());
  int n_channels = AL::getNumChannelsInColorSpace(al_image.getColorSpace());
  if ((n_layers < 0) || (n_channels < 0)) {
    std::stringstream ss;
    ss << "Color space \"" << al_image.getColorSpace() << "\" not supported";
    throw AL::ALError("ALVision", "aLImageToCvMat", ss.str());
  }
  int cv_depth;
  switch (n_layers / n_channels)
  {
  case 4:
    cv_depth = CV_32F;
    break;
  case 2:
    cv_depth = CV_16U;
    break;
  case 1:
    cv_depth = CV_8U;
    break;
  default:
    std::stringstream ss;
    ss << "Depth \"" << (n_layers / n_channels) << "\" not supported";
    throw AL::ALError("ALVision", "aLImageToCvMat", ss.str());
  }

  return cv::Mat(al_image.getHeight(), al_image.getWidth(),
  CV_MAKETYPE(cv_depth, n_channels), data);
}

/** Converts an OpenCV cv::Mat to an ALImage by NOT copying the data over. Be careful, if your cv::Mat goes out of
 * scope, the ALImage pointer is invalid
 * @param img the cv::Mat image the output image will link to
 * @param colorSpace the color space as defined in ALVision
 * @return
 */
static inline AL::ALImage* cvMatToALImage(const cv::Mat & img, int colorSpace,
                                          float pLeftAngle  = 0.0f, float pTopAngle    = 0.0f,
                                          float pRightAngle = 0.0f, float pBottomAngle = 0.0f)
{
  // Check the number of channels
    if (AL::getNumChannelsInColorSpace(colorSpace) != img.channels())
      throw AL::ALError("ALVision", "cvMatToALImage",
          "Channel number incompatibility between cv::Mat and colorSpace");

  // Check the type
    switch (img.depth())
    {
    case CV_8U:
    case CV_16U:
    case CV_32F:
      break;
    default:
      throw AL::ALError("ALVision", "cvMatToALImage",
          "Type incompatibility between cv::Mat and colorSpace");
    }

  // Create an ALImage with the buffer
  AL::ALImage *al_image = new AL::ALImage(img.cols, img.rows, colorSpace, true,
                                          pLeftAngle, pTopAngle, pRightAngle, pBottomAngle);
  al_image->setData(img.data);

  return al_image;
}

/** Converts an OpenCV cv::Mat to an ALImage by COPYING the data over
 * @param img the cv::Mat image the output image will copy
 * @param colorSpace the color space as defined in ALVision
 * @return
 */
static inline AL::ALImage* cvMatToALImageCopy(const cv::Mat & img,
    int colorSpace,
    float pLeftAngle  = 0.0f, float pTopAngle    = 0.0f,
    float pRightAngle = 0.0f, float pBottomAngle = 0.0f)
{
  // Check the number of channels
    if (AL::getNumChannelsInColorSpace(colorSpace) != img.channels())
      throw AL::ALError("ALVision", "cvMatToALImage",
          "Channel number incompatibility between cv::Mat and colorSpace");

  // Check the type
    switch (img.type())
    {
    case CV_8U:
    case CV_16U:
    case CV_32F:
      break;
    default:
      throw AL::ALError("ALVision", "cvMatToALImage",
          "Type incompatibility between cv::Mat and colorSpace");
    }

  // Copy the image data in a buffer
  size_t data_size = img.cols * img.rows * img.elemSize();
  unsigned char *data = new unsigned char[data_size];
  std::memcpy(data, img.data, data_size);

  // Create an ALImage with the buffer
  AL::ALImage *al_image = new AL::ALImage(img.cols, img.rows, colorSpace, false,
                                          pLeftAngle, pTopAngle, pRightAngle, pBottomAngle);
  al_image->setData(data);

  return al_image;
}
}

#endif /* LIBALVISION_ALVISION_ALIMAGE_OPENCV_H_ */
