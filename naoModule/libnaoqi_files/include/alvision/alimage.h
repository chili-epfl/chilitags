/**
 * @author Pierre-Emmanuel VIEL
 * Copyright (c) Aldebaran Robotics 2008, 2011, 2012 All Rights Reserved
 */

#pragma once
#ifndef _LIBALVISION_ALVISION_ALIMAGE_H_
#define _LIBALVISION_ALVISION_ALIMAGE_H_

#include <string>
#include <iostream>
#include <vector>
#include <cassert>

#include <alvision/alvisiondefinitions.h>
#include <qi/os.hpp>

/** \file alvision/alimage.h
 *  \brief handle image
 */

namespace AL
{
class ALValue;

class ALImage
{
public:
  struct ROI {
    ROI(int left, int top, int width, int height);
    ROI(int left, int top, int width, int height,
        float leftAngle,  float topAngle,
        float rightAngle, float bottomAngle);
    int x;
    int y;
    int w;
    int h;
    float leftAngle;
    float topAngle;
    float rightAngle;
    float bottomAngle;
  };

  // .:: methods ::

public:
  /**
     *ALImage
     *@brief constructor
     *@param[in] pWidth width of the image
     *@param[in] pHeight height of the image
     *@param[in] pColorSpace color space of the image
     *@param[in] pDataAreExternal is data buffer external, or is it allocated with the image?
     *@param[in] pLeftAngle camera FOV left angle in radian
     *@param[in] pTopAngle camera FOV top angle in radian
     *@param[in] pRightAngle camera FOV right angle in radian
     *@param[in] pBottomAngle camera FOV bottom angle in radian
     */
  ALImage(int pWidth, int pHeight, int pColorSpace, bool pDataAreExternal = false,
          float pLeftAngle = 0.f, float pTopAngle = 0.f,
          float pRightAngle = 0.f, float pBottomAngle = 0.f);

  /**
     *ALImage
     *@brief constructor
     *@param[in] pResolution resolution of the image
     *@param[in] pColorSpace color space of the image
     *@param[in] pDataAreExternal is data buffer external, or is it allocated with the image?
     *@param[in] pLeftAngle camera FOV left angle in radian
     *@param[in] pTopAngle camera FOV top angle in radian
     *@param[in] pRightAngle camera FOV right angle in radian
     *@param[in] pBottomAngle camera FOV bottom angle in radian
     */
  ALImage(int pResolution, int pColorSpace, bool pDataAreExternal = false,
          float pLeftAngle = 0.f, float pTopAngle = 0.f,
          float pRightAngle = 0.f, float pBottomAngle = 0.f);

  ~ALImage();

  /**
     *toALValue
     *@brief return an ALValue containing image structure
     *@result[0] : [int] with of the image
     *@result[1] : [int] height of the image
     *@result[2] : [int] number of layers of the image
     *@result[3] : [int] colorspace of the image
     *@result[4] : [int] time stamp in second
     *@result[5] : [int] time stamp in microsecond (and under second)
     *@result[6] : [int] data of the image
     *@result[7] : [int] camera ID
     *@result[8] : [float] camera FOV left angle   (radian)
     *@result[9] : [float] camera FOV top angle    (radian)
     *@result[10]: [float] camera FOV right angle  (radian)
     *@result[11]: [float] camera FOV bottom angle (radian)
     */
  ALValue toALValue();

  /** @brief Allocate an ALImage and return a pointer on it using an ALValue to fill it.
    * @param[in] image ALValue containing:
    * image[0] : [int] with of the image
    * image[1] : [int] height of the image
    * image[2] : [int] number of layers of the image
    * image[3] : [int] colorspace of the image
    * image[4] : [int] time stamp in second
    * image[5] : [int] time stamp in microsecond (and under second)
    * image[6] : [int] data of the image
    * image[7] : [int] camera ID
    * image[8] : [float] camera FOV left angle   (radian)
    * image[9] : [float] camera FOV top angle    (radian)
    * image[10]: [float] camera FOV right angle  (radian)
    * image[11]: [float] camera FOV bottom angle (radian)
    * @return a pointer to ALImage otherwise return a NULL pointer.
    * @note This method performs a deep copy, so ALValue can be suppressed.
    */
  static ALImage* fromALValue(const ALValue& image);

  inline void setWidth( const int width )   { fWidth = width; }
  inline void setHeight( const int height ) { fHeight = height; }
  inline void setLeftAngle( const float leftAngle )     { fFOV.leftAngle = leftAngle; }
  inline void setTopAngle( const float topAngle )       { fFOV.topAngle = topAngle; }
  inline void setRightAngle( const float rightAngle )   { fFOV.rightAngle = rightAngle; }
  inline void setBottomAngle( const float bottomAngle ) { fFOV.bottomAngle = bottomAngle; }
  inline void setAngles( const float leftAngle,  const float topAngle,
                         const float rightAngle, const float bottomAngle )
  { fFOV.leftAngle = leftAngle;   fFOV.topAngle = topAngle;
    fFOV.rightAngle = rightAngle; fFOV.bottomAngle = bottomAngle; }

  /*! @brief set the Resolution of the image without changing the allocation size.
   * @param[in] pResolution resolution of the image
   * @deprecated you should not use this function.*/
  bool setSize(int pResolution) { return setResolution(pResolution); }

  /**
     *setResolution
     *@brief set the Resolution of the image without changing the allocation size.
     *@param[in] pResolution resolution of the image.
     */
  bool setResolution(int pResolution);

  /**
     *setColorSpace
     *@brief set the ColorSpace of the image without changing the allocation size.
     *@param[in] pColorSpace ColorSpace of the image.
     */
  bool setColorSpace(int pColorSpace);

  /**
     *getFrame //DEPRECATED
     *@brief return the reference to the image data.
     *@result reference to the image data.
     */
  inline const unsigned char* getFrame() const
  { assert( fData != 0);
    std::cout << "getFrame() is deprecated. Please replace by getData()." << std::endl;
    return fData; }

  /**
     *getData
     *@brief return the reference to the image data.
     *@result reference to the image data.
     */
  inline const unsigned char* getData() const { assert( fData != 0); return fData; }

  // for the camera
  /**
     *getFrame //DEPRECATED
     *@brief return the pointer to the image data.
     *@result pointer to the image data.
     */
  inline unsigned char* getFrame()
  { assert( fData != 0);
    std::cout << "getFrame() is deprecated. Please replace by getData()." << std::endl;
    return fData; }

  /**
     *getData
     *@brief return the pointer to the image data.
     *@result pointer to the image data.
     */
  inline unsigned char* getData() { assert( fData != 0); return fData; }

  /**
     *setData
     *@brief set the image data pointer to point to the specified buffer.
     *@param[in] pData pointer to the image data buffer.
     */
  inline void setData(unsigned char* pData) { fData = pData; }

  /**
     *setTimeStamp
     *@brief set the image timestamp.
     *@param[in] pTimeStamp timestamp to set.
     */
  inline void setTimeStamp(const qi::os::timeval pTimeStamp)
  {
    if( (pTimeStamp.tv_usec < 0) || (pTimeStamp.tv_sec < 0) )
    {
      fTimeStamp = -1;
      return;
    }
    setTimeStamp(static_cast<int>(pTimeStamp.tv_sec), static_cast<int>(pTimeStamp.tv_usec));
  }

  /**
     *setTimeStamp
     *@brief set the image timestamp
     *@param[in] pTimeStamp time in a long long format.
     */
  inline void setTimeStamp(long long pTimeStamp) { fTimeStamp = pTimeStamp; }

  /**
     *setTimeStamp
     *@brief set the image timestamp
     *@param[in] pSeconds time in seconds
     *@param[in] pMicroSeconds time in µseconds
     */
  inline void setTimeStamp(int pSeconds, int pMicroSeconds)
  {
    fTimeStamp = (long long)pSeconds*1000000LL + (long long)pMicroSeconds;
  }


  /**
     *setCameraId
     *@brief set the ID of the camera that shot the picture
     *@param[in] pCameraId ID of the camera that shot the picture
     */
  inline void setCameraId(char pCameraId) { fCameraId = pCameraId; }


  /**
     *getSize
     *@return the size of the allocated memory for the image (the size of fData buffer)
     */
  inline unsigned int getSize() const { return fWidth*fHeight*fNbLayers; }

  /*
     * Accessor
     */
  inline int getWidth( void )  const { return fWidth; }
  inline int getHeight( void ) const { return fHeight; }
  inline int getResolution( void ) const { return getResolutionFromSize(fWidth, fHeight); }
  inline int getColorSpace( void ) const { return fColorSpace; }
  inline int getNbLayers( void ) const { return fNbLayers; }
  inline long long getTimeStamp( void ) const { return fTimeStamp; }
  inline char getCameraId() const { return fCameraId; }
  inline int getMaxResolution( void ) const { return fMaxResolution; }
  inline int getNbOfLayersMax( void ) const { return fMaxNumberOfLayers; }
  inline bool areDataExternal( void ) const { return fDataAreExternal; }
  int getAllocatedSize() const { return fAllocatedSize; }
  inline float getLeftAngle( void )   const { return fFOV.leftAngle; }
  inline float getTopAngle( void )    const { return fFOV.topAngle; }
  inline float getRightAngle( void )  const { return fFOV.rightAngle; }
  inline float getBottomAngle( void ) const { return fFOV.bottomAngle; }
  inline void getAngles( float& leftAngle, float& topAngle, float& rightAngle, float& bottomAngle )
  const { leftAngle = fFOV.leftAngle; topAngle = fFOV.topAngle;
    rightAngle = fFOV.rightAngle; bottomAngle = fFOV.bottomAngle; }

  /*
     * For debug purpose: print the object in an human format
     */
  std::string toString( void ) const;

  int getNumOfROIs() const { return (int)fROIs.size(); }

  const ROI* getROI(int index) const {
    if (index < 0 || index >= getNumOfROIs())
      return NULL;
    return &(fROIs[index]);
  }

  void addROI(const ROI& rect) {
    fROIs.push_back(rect);
  }

  void cleanROIs() {
    fROIs.clear();
  }

  void setEnableROIs(bool enable) {
    fROIEnabled = enable;
  }

  bool isROIEnabled() const {
    return fROIEnabled;
  }


  int writeFile(const char* _fileNameAndPath);
  int readFile(const char* _fileNameAndPath);
  int savePPM(const char* _fileNameAndPath);

  bool computeYUV422imageFromBGR(int height, int width, char *data);
  bool computeBGRimageFromYUV422(const unsigned char* _dest);
  bool computeYYYUUUVVVimageFromYUV422(const unsigned char* _dest);
  bool computeYYYYUUVVimageFromYUV422(const unsigned char* _dest);
private:
  bool reallocateDataSize(const int resolution, const int nbLayers);


  // .:: members ::
private:
  /// width of the image
  int fWidth;

  /// height of the image
  int fHeight;

  /// number of layers of the image
  int fNbLayers;

  /// color space of the image
  int fColorSpace;

  /// Time in microsecond when the image was captured
  long long fTimeStamp;

  /// pointer to the image data
  unsigned char* fData;

  /// ID of the camera that shot the picture
  char fCameraId;

  /// Size of memory allocation
  int fAllocatedSize;

  /// Maximum resolution accepted in the reserved memory
  int fMaxResolution;

  /// Maximum number of layers accepted in the reserved memory
  int fMaxNumberOfLayers;

  /// If true, image points to an external data buffer.
  /// If false, data buffer was allocated while creating instance.
  bool fDataAreExternal;

  /// Manage the field of view of the image that changes with camera model and cropping
  struct FOV {
    float leftAngle;
    float topAngle;
    float rightAngle;
    float bottomAngle;
  };
  struct FOV fFOV;

  std::vector<ROI> fROIs;

  bool fROIEnabled;
};
}

// take a pixel in YUV and compute its RGB Value. RGB value are returned directly in params
void computeRgbFromYuv( unsigned char * pYR, unsigned char * pUG, unsigned char * pVB );


#endif  // _LIBALVISION_ALVISION_ALIMAGE_H_
