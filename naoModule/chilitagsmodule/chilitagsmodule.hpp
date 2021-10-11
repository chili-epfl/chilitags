/*******************************************************************************
*   Copyright (c) 2016-present, Bahar Irfan. All rights reserved.              *
*                                                                              *
*   This file contains the class for ChilitagsModule (Chilitags for NAO Robot).*
*                                                                              *
*   Please cite the following work if using this work:                         *
*                                                                              *
*      Chilitags for NAO Robot. B. Irfan and S. Lemaignan. University of       *
*     Plymouth, UK. https://github.com/birfan/chilitags. 2016.                 *
*                                                                              *
*      Chilitags 2: Robust Fiducial Markers for Augmented Reality. Q. Bonnard, *
*     S. Lemaignan, G.  Zufferey, A. Mazzei, S. Cuendet, N. Li, P. Dillenbourg.*
*     CHILI, EPFL, Switzerland. http://chili.epfl.ch/software. 2013.           *
*                                                                              *
*   Chilitags is free software: you can redistribute it and/or modify          *
*   it under the terms of the Lesser GNU General Public License as             *
*   published by the Free Software Foundation, either version 3 of the         *
*   License, or (at your option) any later version.                            *
*                                                                              *
*   Chilitags is distributed in the hope that it will be useful,               *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of             *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
*   GNU Lesser General Public License for more details.                        *
*                                                                              *
*   ChilitagsModule is released under GNU Lesser General Public License v3.0   *
*   (LGPL3) in accordance with Chilitags (Bonnard et al., 2013). You should    *
*   have received a copy of the GNU Lesser General Public License along with   *
*   Chilitags.  If not, see <http://www.gnu.org/licenses/>.                    *
*******************************************************************************/

#ifndef CHILITAGSMODULE_H
#define CHILITAGSMODULE_H

#include <boost/shared_ptr.hpp>
#include <alcommon/almodule.h>
#include "../tagEstimation/estimate3d_nao.hpp"

namespace AL
{
// This is a forward declaration of AL:ALBroker which
// avoids including <alcommon/albroker.h> in this header
class ALBroker;
}

/**
 * A simple example module that says "Hello world" using
 * text to speech, or prints to the log if we can't find TTS
 *
 * This class inherits AL::ALModule. This allows it to bind methods
 * and be run as a remote executable or as a plugin within NAOqi
 */
class ChilitagsModule : public AL::ALModule
{
private:
EstimateTag ET;
std::vector< std::vector<float> > tagsVec;
public:
ChilitagsModule(boost::shared_ptr<AL::ALBroker> pBroker, const std::string& pName);

virtual ~ChilitagsModule();

/** Overloading ALModule::init().
 * This is called right after the module has been loaded
 */
virtual void init();

void subscribeCameraRemote(std::string robotIp, int robotPort, int cameraIndex);

void subscribeCameraLocal(int cameraIndex);

void subscribeCamera();

void unsubscribeCamera();

void setCameraResolution640x480();

void setCameraResolution320x240();

void setDefaultTagSize(float tagSize);

void readTagConfiguration(std::string configFilename);

void resetTagSettings();

std::vector< std::vector<float> > estimatePosAllTags();

std::vector< std::vector<float> > estimatePosGivenTag(std::string givenTagName);

};
#endif // CHILITAGSMODULE_H

