/**
 * @author Alexandre Mazel
 *
 */


#pragma once
#ifndef _LIBALAUDIO_ALAUDIO_ALSOUNDEXTRACTOR_H_
#define _LIBALAUDIO_ALAUDIO_ALSOUNDEXTRACTOR_H_

#include <alextractor/alextractor.h>
#include <alvalue/alvalue.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>
#include <qi/log.hpp>
#include <qi/macro.hpp>

typedef signed short AL_SOUND_FORMAT; // ASSUME: sound data are in 16 bits

// deprecated
// usable and practical logging system

#define DESACTIVATE_ALL_DEV_INFO          // define me to desactivate all debug or trace info (should be defined on public release version)

#ifndef DESACTIVATE_ALL_DEV_INFO
# define AL_SOUND_EXTRACTOR_DEBUG_PRINTF(...)    if ( getDebugMode() ) { printf(__VA_ARGS__); }
# define AL_SOUND_EXTRACTOR_DEBUG_LOG(onestr)    if ( getDebugMode() ) { fLoggerProxy->debug( getName(), std::string( onestr ) ); }
# define AL_SOUND_EXTRACTOR_INFO_LOG(onestr)     if ( getDebugMode() ) { fLoggerProxy->info( getName(), std::string( onestr ) ); }
# define AL_SOUND_EXTRACTOR_ERROR_LOG(onestr)    if ( getDebugMode() ) { fLoggerProxy->error( getName(), std::string( onestr ) ); }
#else
# define AL_SOUND_EXTRACTOR_DEBUG_PRINTF(...)    /* onestr */
# define AL_SOUND_EXTRACTOR_DEBUG_LOG(onestr)    /* onestr */
# define AL_SOUND_EXTRACTOR_INFO_LOG(onestr)     /* onestr */
# define AL_SOUND_EXTRACTOR_ERROR_LOG(onestr)    /* onestr */
#endif

namespace AL
{
class ALProxy;
class ALBroker;

enum AUDIOCHANNELTYPE
{
  ALLCHANNELS  = 0,
  LEFTCHANNEL  = 1,
  RIGHTCHANNEL = 2,
  FRONTCHANNEL = 3,
  REARCHANNEL  = 4,
  FIRSTCHANNEL = LEFTCHANNEL,
  SECONDCHANNEL= RIGHTCHANNEL,
  THIRDCHANNEL = FRONTCHANNEL,
  FOURTHCHANNEL= REARCHANNEL
};

class ALSoundExtractor: public ALExtractor
{
public:
  ALSoundExtractor( boost::shared_ptr<AL::ALBroker> pBroker, std::string pName );

  virtual ~ALSoundExtractor();

  virtual std::string version(void) {return "";}
  virtual void startDetection(void);
  virtual void stopDetection(void);

  /**
    * setDebugMode. enable/disable the printing of some debug information
    * @param pbSetOrUnset enable the functionality when true
    * @deprecated This functionnality is now handled by qi/log
    */
  QI_API_DEPRECATED void setDebugMode(const bool &pbSetOrUnset = true)
  {
    qiLogWarning("audio.alsoundextractor", "The call to setDebugMode() is "
                 "now deprectated. This functionnality is now handled by qi/log");
    fbDebugMode = pbSetOrUnset;
  }

  /**
    * getDebugMode. get the status about the printing of some debug information
    * @deprecated This functionnality is now handled by qi/log
    */
  QI_API_DEPRECATED inline bool getDebugMode(void)
  {
    qiLogWarning("audio.alsoundextractor", "The call to getDebugMode() is "
                 "now deprectated. This functionnality is now handled by qi/log");
    return fbDebugMode;
  }


  virtual void process(const int & nbOfChannels,
                       const int & nbrOfSamplesByChannel,
                       const AL_SOUND_FORMAT * buffer,
                       const ALValue & timestamp);


  QI_API_DEPRECATED virtual void processSound(const int nbOfChannels,
                                          const int nbrOfSamplesByChannel,
                                          const AL_SOUND_FORMAT* buffer);

  QI_API_DEPRECATED virtual void processSoundRemote(const int & nbOfChannels,
                                  const int & nbrOfSamplesByChannel,
                                  const ALValue & buffer);

private:
  void processRemote(const int & nbOfChannels,
                     const int & nbrOfSamplesByChannel,
                     const ALValue & timestamp,
                     const ALValue & buffer);

  void xStartDetection(const int pPeriod,
                       const float pPrecision)
  {
    startDetection();
  }

  virtual void xUpdateParameters(const int pPeriod,
                                 const float pPrecision){}

  void xStopDetection(void)
  {
    stopDetection();
  }

  virtual std::vector<std::string> getOutputNames();

protected:

  bool fIsRunning;
  bool fbDebugMode;
  boost::shared_ptr<ALProxy>  audioDevice;
  ALValue fNullTimestamp;
};

}

#endif
