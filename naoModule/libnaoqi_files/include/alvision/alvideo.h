/**
 * @author Pierre-Emmanuel VIEL
 * Copyright (c) Aldebaran Robotics 2008, 2011 All Rights Reserved
 */

#pragma once
#ifndef _LIBALVISION_ALVISION_ALVIDEO_H_
#define _LIBALVISION_ALVISION_ALVIDEO_H_


# include <alvision/alvisiondefinitions.h>
# include <alvision/alimage.h>
# include <iostream>
# include <fstream>
# include <vector>

/** \file alvision/alvideo.h
 *  \brief handle video
 */

namespace AL
{
  //structures for video raw stream recording
  /*
   * streamHeader
   * @brief single stream header
   */
  struct streamHeader
  {
    unsigned int width : 32;
    unsigned int height: 32;
    unsigned int colorSpace : 32;
    unsigned int pixelDepth : 32;
  };

  /*
   * videoHeader
   * @brief multiple stream header global header with version field
   */
  struct videoHeader
  {
    unsigned int magicNumber : 32;  // magic number
    unsigned int userSpaceSize : 32;
    unsigned int numberOfFrames : 32;
    unsigned int numberOfStreams : 32;
  };

  struct streamProperties
  {
    unsigned int width;
    unsigned int height;
    unsigned int resolution;
    unsigned int colorSpace;
    unsigned int nbLayers;
    unsigned int pixelDepth;
    unsigned int sizePerImage;
  };


  class ALVideo
  {

  // .:: methods ::

  public:
    ALVideo();
    ~ALVideo();

    bool recordVideo(const std::string pFilePath, const unsigned int pUserSpaceSize, const std::vector<streamHeader>& pStreamHeaderVector);
    bool readVideo(const std::string pFilePath);
    void closeVideo();
    bool goToFrame(const unsigned int pFrameNumber, const unsigned int pStreamNumber);
    bool getFrame(ALImage & pImage, const unsigned int pFrameNumber, const unsigned int pStreamNumber, const bool pCheckFormat = true);
    bool getNextFrame(ALImage & pImage, const bool pCheckFormat = true);
    bool getPrecedingFrame(ALImage & pImage, const bool pCheckFormat = true);
    bool write(char* ptrImageData, const int pSizeData, const long long pTimeStamp = 0, const char pCameraId = 0,
               const float pLeftAngle = 0, const float pTopAngle = 0, const float pRightAngle = 0, const float pBottomAngle = 0);
    bool write(int height, int width, char *imageData, const long long pTimeStamp, const char pCameraId,
               const float pLeftAngle, const float pTopAngle, const float pRightAngle, const float pBottomAngle);

    inline const unsigned char* getMagicNumber() const       { return (unsigned char*)&fMagicNumber; };
    inline unsigned int getNumberOfFrames() const      { return fNumberOfFrames; };
    inline unsigned int getNumberOfStreams() const     { return fNumberOfStreams; };
    inline unsigned int getCurrentFrameNumber() const  { return fCurrentFrameNumber; };
    inline unsigned int getCurrentStreamNumber() const { return fCurrentStreamNumber; };
    inline bool isOpenForReading() const               { return fIsOpenForReading; };
    inline bool isOpenForWriting() const               { return fIsOpenForWriting; };

    inline int getStreamWidth(const unsigned int pStreamNumber) const       { return (pStreamNumber<fNumberOfStreams) ? fStreamPropertiesVector[pStreamNumber].width        : -1; };
    inline int getStreamHeight(const unsigned int pStreamNumber)const       { return (pStreamNumber<fNumberOfStreams) ? fStreamPropertiesVector[pStreamNumber].height       : -1; };
    inline int getStreamResolution(const unsigned int pStreamNumber) const  { return (pStreamNumber<fNumberOfStreams) ? fStreamPropertiesVector[pStreamNumber].resolution   : -1; };
    inline int getStreamColorSpace(const unsigned int pStreamNumber) const  { return (pStreamNumber<fNumberOfStreams) ? fStreamPropertiesVector[pStreamNumber].colorSpace   : -1; };
    inline int getStreamNbLayers(const unsigned int pStreamNumber) const    { return (pStreamNumber<fNumberOfStreams) ? fStreamPropertiesVector[pStreamNumber].nbLayers     : -1; };
    inline int getStreamPixelDepth(const unsigned int pStreamNumber) const  { return (pStreamNumber<fNumberOfStreams) ? fStreamPropertiesVector[pStreamNumber].pixelDepth   : -1; };
    inline int getStreamSizePerImage(const unsigned int pStreamNumber)const { return (pStreamNumber<fNumberOfStreams) ? fStreamPropertiesVector[pStreamNumber].sizePerImage : -1; };


  // .:: members ::

  private:
    volatile bool fIsOpenForReading;
    volatile bool fIsOpenForWriting;

    std::ifstream     fVideoStreamIn;
    std::ofstream     fVideoStreamOut;
    std::string       fFilePath;

    unsigned int fMagicNumber;
    unsigned int fUserSpaceSize;
    unsigned int fNumberOfFrames;
    unsigned int fNumberOfStreams;
    unsigned int fSizeOfHeader;
    unsigned int fSizePerMultiplexedFrame;
    std::vector<struct streamProperties> fStreamPropertiesVector;

    unsigned int fCurrentStreamNumber;
    unsigned int fCurrentFrameNumber;
  };
}

#endif  // _LIBALVISION_ALVISION_ALVIDEO_H_
