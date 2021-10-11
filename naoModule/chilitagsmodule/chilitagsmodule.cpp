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

#include "chilitagsmodule.hpp"
#include <iostream>
#include <alcommon/albroker.h>
#include <qi/log.hpp>
#include <alvision/alimage.h>
#include <alvision/alvisiondefinitions.h>

using namespace AL;

ChilitagsModule::ChilitagsModule(boost::shared_ptr<ALBroker> broker, const std::string& name) :
    ALModule(broker, name)
{
    /** Describe the module here. This will appear on the webpage*/
    setModuleDescription("Chilitags module for estimating the 3d position of the tag and the transformation matrix between chili tag and the nao camera.");

    functionName("subscribeCameraRemote", getName(), "Subscribe to the camera remotely by giving IP, port, and camera index.");
    addParam("robotIp", "IP of the robot");
    addParam("robotPort", "Port of the robot");
    addParam("cameraIndex", "0 for top camera, 1 for bottom (default)");
    BIND_METHOD(ChilitagsModule::subscribeCameraRemote);

    functionName("subscribeCameraLocal", getName(), "Subscribe to the camera locally (on the robot), by giving camera index.");
    addParam("cameraIndex", "0 for top camera, 1 for bottom (default)");
    BIND_METHOD(ChilitagsModule::subscribeCameraLocal);

    functionName("subscribeCameraDefault", getName(), "Subscribe to the bottom camera on the robot.");
    BIND_METHOD(ChilitagsModule::subscribeCamera);

    functionName("unsubscribeCamera", getName(), "Unsubscribe from the camera.");
    BIND_METHOD(ChilitagsModule::unsubscribeCamera);

    functionName("setCameraResolution640x480", getName(), "Set the camera resolution to 640x480 (optional function, default is 320x240).");
    BIND_METHOD(ChilitagsModule::setCameraResolution640x480);

    functionName("setCameraResolution320x240", getName(), "Set the camera resolution to 320x240 (needed to reset if the resolution has changed).");
    BIND_METHOD(ChilitagsModule::setCameraResolution320x240);

    functionName("setDefaultTagSize", getName(), "Set the default tag size for Chilitags. Default is 30 mm. Call this method (if you need to) before calling estimate functions.");
    addParam("tagSize", "The tag size to set for the Chilitags (in mm)");
    BIND_METHOD(ChilitagsModule::setDefaultTagSize);

    functionName("readTagConfiguration", getName(), "Read the configuration of Chilitags from a YAML file. See 'tag_configuration_sample.yml' for an example.");
    addParam("configFilename", "Configuration file name for tags");
    BIND_METHOD(ChilitagsModule::readTagConfiguration);

    functionName("resetTagSettings", getName(), "Reset tag settings: tag size is 30 mm and no configuration file is used.");
    BIND_METHOD(ChilitagsModule::resetTagSettings);

    functionName("estimatePosGivenTag", getName(), "Get a vector of a 17-element vector corresponding to the transformation matrix between the given chilitag and the nao camera");
    addParam("estimatePosGivenTag", "Give a specific tag to search for");
    BIND_METHOD(ChilitagsModule::estimatePosGivenTag);

    functionName("estimatePosAllTags", getName(), "Get a vector of 17-element vectors corresponding to the transformation matrix between the chilitag and the nao camera for each visible chilitag");
    BIND_METHOD(ChilitagsModule::estimatePosAllTags);

}

ChilitagsModule::~ChilitagsModule() {
}
void ChilitagsModule::init()
{
    /** Init is called just after construction.
     *
     * Here we call sayHello, so that the module does something
     * without us having to explicitly call sayHello from somewhere else.
     */
}

void ChilitagsModule::subscribeCameraRemote(std::string robotIp, int robotPort, int cameraIndex)
{
    ET.subscribeCamera(robotIp, robotPort, cameraIndex);
    std::string camType = "bottom"; //cameraIndex = 1
    if(cameraIndex == 0) {
        camType = "top";
    }
    qiLogInfo("module.example") << "Subscribed "<< camType << " camera at " << robotIp << ":" << robotPort<< std::endl;

}

void ChilitagsModule::subscribeCameraLocal(int cameraIndex)
{
    std::string robotIp = "127.0.0.1";
    int robotPort = 9559;
    subscribeCameraRemote(robotIp, robotPort, cameraIndex);
}

void ChilitagsModule::subscribeCamera()
{
    int cameraIndex = 1; //bottom camera
    subscribeCameraLocal(cameraIndex);
}

void ChilitagsModule::setCameraResolution640x480()
{
    ET.setCameraResolution(1);
}

void ChilitagsModule::setCameraResolution320x240()
{
    ET.setCameraResolution(0);
}

void ChilitagsModule::unsubscribeCamera()
{
    ET.unsubscribeCamera();
    qiLogInfo("module.example") << "Unsubscribed camera." << std::endl;
}

void ChilitagsModule::setDefaultTagSize(float tagSize)
{
    ET.setDefaultTagSize(tagSize);
}

void ChilitagsModule::readTagConfiguration(std::string configFilename)
{
    ET.readTagConfiguration(configFilename);
}

void ChilitagsModule::resetTagSettings()
{
    ET.resetTagSettings();
}

std::vector< std::vector<float> > ChilitagsModule::estimatePosAllTags()
{
    tagsVec.clear();
    ET.estimateTagsNao(false, "", tagsVec);
    qiLogInfo("module.example") << "Estimated position of all visible tags." << std::endl;
    return tagsVec;
}

std::vector< std::vector<float> > ChilitagsModule::estimatePosGivenTag(std::string givenTagName)
{
    tagsVec.clear();
    ET.estimateTagsNao(true, givenTagName, tagsVec);
    qiLogInfo("module.example") << "Estimated position of tag " << givenTagName << std::endl;
    return tagsVec;
}
