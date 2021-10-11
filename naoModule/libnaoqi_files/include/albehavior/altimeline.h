/**
* @author Aldebaran Robotics
* Aldebaran Robotics (c) 2012 All Rights Reserved
*/

#pragma once

#ifndef _LIB_ALBEHAVIOR_ALTIMELINE_ALBOX_H_
#define _LIB_ALBEHAVIOR_ALTIMELINE_ALBOX_H_

namespace AL
{

  class ALTimeline
  {
  public :

    ALTimeline(){}
    virtual ~ALTimeline(){}

    /**
     * play.\n
     * Read a timeline from the current buffer till the end.\n
     */
    virtual void play(void) = 0;

    /**
     * pause.\n
     * Pause the reading a timeline at the current frame.\n
     */
    virtual void pause(void) = 0;


    /**
     * stop.\n
     * Stop reading a timeline.\n
     */
    virtual void stop(void) = 0;

    /**
     * goTo.\n
     * goTo moving time cursor.\n
     */
    virtual void goTo(const int &pFrame) = 0;
    virtual void goTo(const std::string &pFrameName) = 0;

    virtual int getSize() const = 0;
    virtual int getFPS() const = 0;
    virtual void setFPS(const int fps) = 0;
  };

}  // namespace AL

#endif  // _LIB_ALBEHAVIOR_ALTIMELINE_ALBOX_H_

