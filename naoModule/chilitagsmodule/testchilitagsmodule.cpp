/*******************************************************************************
*   Copyright (c) 2016-present, Bahar Irfan. All rights reserved.              *
*                                                                              *
*   \file testchilitagsmodule.cpp                                              *
*   \brief Test how to call a module from the outside.                         *
*                                                                              *
*   An example on how to call the example ChilitagsModule module from the      *
*   outside.                                                                   *
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
#include <alerror/alerror.h>
#include <alcommon/alproxy.h>
#include <alcommon/albroker.h>
#include <alcommon/albrokermanager.h>
#include <alcommon/altoolsmain.h>

int main(int argc, char* argv[]) {
    if(argc != 2)
    {
        std::cerr << "Wrong number of arguments!" << std::endl;
        std::cerr << "Usage: testchilitagsmodule NAO_IP" << std::endl;
        exit(2);
    }

    const std::string robotIP = argv[1];
    int port = 9559;
    int camIndex = 0;
    float tagSize = 20.f;
    std::string configFilename = "tag_configuration_sample.yml";

    std::vector<std::vector<float> > givenTag;

    try {
        /** Create a generic proxy to "ChilitagsModule" module.
         * Arguments for the constructor are
         * - name of the module
         * - string containing the IP adress of the robot
         * - port (default is 9559)
         */
        boost::shared_ptr<AL::ALBroker> broker =
            AL::ALBroker::createBroker("MyBroker", "0.0.0.0", 54500, robotIP, port);

        boost::shared_ptr<AL::ALProxy> testProxy
            = boost::shared_ptr<AL::ALProxy>(new AL::ALProxy(broker, "ChilitagsModule"));

        //    testProxy->callVoid("setCameraResolution640x480"); //optional

        //    testProxy->callVoid("setCameraResolution320x240"); //default but needed to reset again, if the resolution has changed

        //testProxy->callVoid("subscribeCameraLocal", camIndex);

        testProxy->callVoid("subscribeCameraRemote", robotIP, port, camIndex);

        //    testProxy->callVoid("readTagConfiguration", configFilename);

        //    testProxy->callVoid("setDefaultTagSize", tagSize);

        //    testProxy->callVoid("resetTagSettings");

        //    std::vector<std::vector<float>> allTags = testProxy->call< std::vector< std::vector<float> > >("estimatePosAllTags");

        givenTag = testProxy->call< std::vector< std::vector<float> > >("estimatePosGivenTag", std::string("8"));

        testProxy->callVoid("unsubscribeCamera");

        for (std::vector<std::vector<float> >::const_iterator i = givenTag.begin(); i != givenTag.end(); ++i)
            std::cout << *i << std::endl;

        //    for (std::vector<std::vector<float>>::const_iterator i = allTags.begin(); i != allTags.end(); ++i)
        //      std::cout << *i << std::endl;

    }
    catch (const AL::ALError& e) {
        std::cerr << e.what() << std::endl;
    }
}
