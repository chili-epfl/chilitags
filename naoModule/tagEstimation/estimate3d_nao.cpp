/*******************************************************************************
*   Copyright (c) 2016-present, Bahar Irfan. All rights reserved.              *
*                                                                              *
*   This file is based on EstimatePose3D.cpp adapted for the NAO robot.        *
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

#include "estimate3d_nao.hpp"

EstimateTag::EstimateTag(){
    tagSize = 30.f;
    readConfigFile = false;
}
void EstimateTag::estimateTagsNao(bool givenTagToDetect, std::string givenTagName, std::vector<std::vector<float> >& tagsVec){

    /******************************/
    /* Setting up pose estimation */
    /******************************/

    chilitags::Chilitags3D chilitags3D(Size(inputWidth, inputHeight));

    cv::Mat mCameraMatrix = (cv::Mat_<float>(3,3) <<
                             focalLength,            0,              inputWidth/2,
                             0,              focalLength,            inputHeight/2,
                             0,              0,              1
                             );

    if(readConfigFile) {
        chilitags3D.readTagConfiguration(configFilename);
    }

    chilitags3D.setDefaultTagSize(tagSize);

    chilitags3D.setCalibration(mCameraMatrix, noArray());

    cv::Mat cameraMatrix, distCoeffs;

    cv::Mat imgHeader = cv::Mat(cv::Size(inputWidth,inputHeight), CV_8UC3);

    /*****************************/
    /*             Go!           */
    /*****************************/
    std::cout << "I'm now looking for objects...\n";
    AL::ALValue img;

    std::string delimiter = "tag_";
    bool tagDetected = false;
    std::vector<float> tv;

    tagsVec.clear();
    while(!tagDetected) {
        img = camProxy->call<AL::ALValue>("getImageRemote",clientName);

        /** Access the image buffer (6th field) and assign it to the opencv image
         * container. */
        imgHeader.data = (uchar*) img[6].GetBinary();
        cv::Size imageSize = imgHeader.size();

        for (auto& kv : chilitags3D.estimate(imgHeader)) {
            tv.clear();
            std::string tagName = kv.first;
            tagName.erase(0, tagName.find(delimiter) + delimiter.length());

            if(!givenTagToDetect || tagName.compare(givenTagName) == 0) {
                tagDetected = true;
                tv.push_back(std::stof(tagName));
                cv::Mat transformCVMat = cv::Mat(kv.second);
                for(int i=0; i<3; i++) {
                    transformCVMat.at<float>(i,3) /= 1000;
                }

                for (int i = 0; i < transformCVMat.rows; ++i) {
                    tv.insert(tv.end(), transformCVMat.ptr<float>(i), transformCVMat.ptr<float>(i)+transformCVMat.cols);
                }
                tagsVec.push_back(tv);
            }
        }
        camProxy->callVoid("releaseImage", clientName);

        //	        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

bool EstimateTag::setCameraResolution(int cam_res_index){

    if( cam_res_index == 0) {
        inputWidth = 320;
        inputHeight = 240;
        cameraRes = AL::kQVGA;
        if(camIndex == 0)      //top camera
            //      focalLength = 420;
            focalLength = 280;
        else
            //     focalLength = 410;
            focalLength = 275;
    }
    else if(cam_res_index == 1) {
        inputWidth = 640;
        inputHeight = 480;
        cameraRes = AL::kVGA;
        if(camIndex == 0)     //top camera
//                      focalLength = 830;
            focalLength = 380;
        else
//                      focalLength = 820;
            focalLength = 400;
    }
    else{
        std::cerr << "Wrong resolution for NAO camera. Possible values: cam_res_index = 0 for 320x240 (default), cam_res_index = 1 for 640x480\n";
        return false;
    }
    return true;
}

bool EstimateTag::subscribeCamera(std::string robot_ip, int robot_port, int cam_index){
    // A broker needs a name, an IP and a port to listen:
    const std::string brokerName = "chiliBroker";

    camIndex = cam_index;

    setCameraResolution(0); //320x240 by default


    // Create your own broker
    boost::shared_ptr<AL::ALBroker> broker =
        AL::ALBroker::createBroker(brokerName, "0.0.0.0", 54000, robot_ip, robot_port);

    camProxy = boost::shared_ptr<AL::ALProxy>(new AL::ALProxy(broker, "ALVideoDevice"));

    /** Subscribe a client image requiring 320*240 and BGR colorspace.*/
    clientName = camProxy->call<std::string>("subscribeCamera", "cam", cam_index, cameraRes, AL::kBGRColorSpace, 30);

    /*****************************/
    /*    Init camera capture    */
    /*****************************/

    if (!camProxy->call<bool>("openCamera",cam_index) || !camProxy->call<bool>("startCamera",cam_index))
    {
        std::cerr << "Unable to initialise video capture.\n";
        return false;
    }

    return true;
}

void EstimateTag::unsubscribeCamera(){
    camProxy->callVoid("unsubscribe", clientName);
}

void EstimateTag::setDefaultTagSize(float tag_size){
    tagSize = tag_size;
}

void EstimateTag::readTagConfiguration(std::string config_filename){
    readConfigFile = true;
    configFilename = config_filename;
}

void EstimateTag::resetTagSettings(){
    tagSize = 30.f;
    readConfigFile = false;
}
EstimateTag::~EstimateTag(){

}

/*
 * int main(int argc, char* argv[])
 *{
 *	std::cout
 *	<< "Usage: "<< argv[0]
 *						<< " [-pip <robotIP>] [-pport <port>] [-cam <camera index (0 for top camera, 1 for bottom (default))>] [-c <tag configuration (YAML)>] [-i <camera calibration (YAML)>]\n";
 *
 *	const char* intrinsicsFilename = 0;
 *	const char* configFilename = 0;
 *	std::string robotIp = "127.0.0.1";
 *	int robotPort = 9559;
 *	int camIndex = 1; //bottom camera
 *
 *	for( int i = 1; i < argc; i++ )
 *	{
 *		if( strcmp(argv[i], "-pip") == 0 )
 *			robotIp = std::string(argv[++i]);
 *		else if( strcmp(argv[i], "-pport") == 0 )
 *			robotPort = atoi(argv[++i]);
 *		else if( strcmp(argv[i], "-cam") == 0 )
 *			camIndex = atoi(argv[++i]);
 *		else if( strcmp(argv[i], "-c") == 0 )
 *			configFilename = argv[++i];
 *		else if( strcmp(argv[i], "-i") == 0 )
 *			intrinsicsFilename = argv[++i];
 *	}
 *	std::vector<std::vector<float>> tagsVec;
 *
 *	EstimateTag ET;
 *
 *	if(ET.subscribeCamera(robotIp, robotPort, camIndex)){
 *		ET.estimateTagsNao(false, "8", tagsVec);
 *		ET.unsubscribeCamera();
 *	}
 *	return 0;
 *}
 */
