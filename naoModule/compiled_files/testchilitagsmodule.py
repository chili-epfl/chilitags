#!/usr/local/bin/python
"""
/*******************************************************************************
*   Copyright (c) 2016-present, Bahar Irfan. All rights reserved.              *
*                                                                              *
*   A sample test file for accessing the ChilitagsModule through Python.       *
*                                                                              *
*   Please cite the following work if using this work:                         *
*                                                                              *
*     Chilitags for NAO Robot. B. Irfan and S. Lemaignan. University of        *
*     Plymouth, UK. https://github.com/birfan/chilitags. 2016.                 *
*                                                                              *
*     Chilitags 2: Robust Fiducial Markers for Augmented Reality. Q. Bonnard,  *
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
"""

__version__ = '0.0.1'

__copyright__ = 'Copyright (c) 2016-present, Bahar Irfan. All rights reserved.'
__author__ = 'Bahar Irfan'
__email__ = 'bahar.irfan@plymouth.ac.uk'


import qi

#robotIP = "127.0.0.1"
robotIP = "192.168.1.115" #IP address of the robot if connecting remotely
port = 9559
camIndex = 0 # 0: top camera, 1: bottom camera
tagNumber = 8 # tag number to detect
configFilename = "tag_configuration_sample.yml";

connectAddress = "tcp://" + robotIP + ":" + str(port)

qiapp = qi.Application(url=connectAddress)
qiapp.start()
session = qi.Session()
session.connect(connectAddress)
chilitags = session.service("ChilitagsModule")

#chilitags.setCameraResolution640x480() # comment this line to set the camera resolution to default (320x240)

#chilitags.setCameraResolution320x240() # default but needed to reset again, if the resolution has changed

#chilitags.subscribeCameraDefault() # subscribes and starts the bottom camera (camIndex = 1)

#chilitags.subscribeCameraLocal(camIndex) # comment the line above and uncomment this line to use the top camera instead (camIndex = 0)

chilitags.subscribeCameraRemote(robotIP, port, camIndex) # comment the line above and uncomment this line to connect to the robot remotely

chilitags.setDefaultTagSize(20)

#chilitags.readTagConfiguration(configFilename)

#chilitags.resetTagSettings()

givenTag = chilitags.estimatePosGivenTag(str(tagNumber)) # estimate the position of a given tag

allTags = chilitags.estimatePosAllTags() # estimate the position of all tags

print("Transformation matrix from given tag " + str(tagNumber))
for i in range(0, len(givenTag)):
    for j in range(0, len(givenTag[i])):
       print(givenTag[i][j])

print("Transformation matrices for all visible tags")
for i in range(0, len(allTags)):
    for j in range(0, len(allTags[i])):
       print(allTags[i][j])

chilitags.unsubscribeCamera() # unsubscribes the camera (necessary before subscribing again)

qiapp.stop()
