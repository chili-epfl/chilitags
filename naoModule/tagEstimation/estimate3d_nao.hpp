/*******************************************************************************
*   Copyright (c) 2016-present, Bahar Irfan. All rights reserved.              *
*                                                                              *
*   This file is based on EstimatePose3D adapted for the NAO robot.            *
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
#include <iostream>

#include <chilitags.hpp>

#include <opencv2/core/core.hpp> // for cv::Mat

// Aldebaran includes.
#include <alproxies/alvideodeviceproxy.h>
#include <alvision/alimage.h>
#include <alvision/alvisiondefinitions.h>

#include <alerror/alerror.h>
#include <alcommon/albroker.h>
#include <alcommon/albrokermanager.h>

#include <boost/shared_ptr.hpp>

using namespace cv;

class EstimateTag {
private:
/* proxy parameters */
boost::shared_ptr<AL::ALProxy> camProxy;
std::string clientName;
/* camera parameters */
int camIndex;
float inputWidth;
float inputHeight;
int cameraRes;
float focalLength;
float tagSize;
bool readConfigFile;
std::string configFilename;

public:
EstimateTag();
~EstimateTag();
void estimateTagsNao(bool givenTagToDetect, std::string givenTagName, std::vector<std::vector<float> >& tagsVec);

bool setCameraResolution(int cam_res_index);

bool subscribeCamera(std::string robotIp, int robotPort, int cameraIndex);

void unsubscribeCamera();

void setDefaultTagSize(float tag_size);

void readTagConfiguration(std::string configFilename);

void resetTagSettings();
};
