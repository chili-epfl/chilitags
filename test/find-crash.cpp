/*******************************************************************************
*   Copyright 2013-2014 EPFL                                                   *
*   Copyright 2013-2014 Quentin Bonnard                                        *
*                                                                              *
*   This file is part of chilitags.                                            *
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
*   You should have received a copy of the GNU Lesser General Public License   *
*   along with Chilitags.  If not, see <http://www.gnu.org/licenses/>.         *
*******************************************************************************/

// This file serves as an illustration of how to use Chilitags


// This header contains the detection part
#include <chilitags.hpp>

// OpenCV goodness for I/O
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

int main(int argc, char* argv[])
{
    int xRes = 640;
    int yRes = 480;
    int cameraIndex = 0;
    bool fromFile = argc == 2;
    if (argc > 2) {
        xRes = std::atoi(argv[1]);
        yRes = std::atoi(argv[2]);
    }
    if (argc > 3) {
        cameraIndex = std::atoi(argv[3]);
    }

    // The source of input images
    cv::VideoCapture capture;
    if (fromFile) {
        capture.open(argv[1]);
    }
    else {
        capture.open(cameraIndex);
    }

    if (!capture.isOpened())
    {
        std::cerr << "Unable to initialise video capture." << std::endl;
        return 1;
    }

    if (!fromFile) {
#ifdef OPENCV3
        capture.set(cv::CAP_PROP_FRAME_WIDTH, xRes);
        capture.set(cv::CAP_PROP_FRAME_HEIGHT, yRes);
#else
        capture.set(CV_CAP_PROP_FRAME_WIDTH, xRes);
        capture.set(CV_CAP_PROP_FRAME_HEIGHT, yRes);
#endif
    }

    cv::Mat inputImage;
    chilitags::Chilitags chilitags;

    std::cout
        << "The input of Chilitags::find() is saved as ./lastimage.png\n"
        << "If the program crashes, this file can be used to reproduce the crash.\n"
        << "\n"
        << "Usage: " << argv[0] << " videofile\n"
        << "       to use a video file as input.\n"
        << "       " << argv[0] << " [x-res y-res [camera-index]]\n"
        << "       to use the live feed of a camera as input.\n"
        << "\n"
        << "Hit Ctrl-C to stop the program.\n"
    ;
    while(capture.read(inputImage)) {
        cv::imwrite("lastimage.png", inputImage);
        chilitags.find(inputImage);
    }
    capture.release();
    std::cout << "Done.\n";

    return 0;
}
