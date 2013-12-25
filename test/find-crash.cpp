/*******************************************************************************
*   Copyright 2013 EPFL                                                        *
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
    int tXRes = 640;
    int tYRes = 480;
    int tCameraIndex = 0;
    if (argc > 2) {
        tXRes = std::atoi(argv[1]);
        tYRes = std::atoi(argv[2]);
    }
    if (argc > 3) {
        tCameraIndex = std::atoi(argv[3]);
    }

    // The source of input images
    cv::VideoCapture tCapture(tCameraIndex);
    if (!tCapture.isOpened())
    {
        std::cerr << "Unable to initialise video capture." << std::endl;
        return 1;
    }
#ifdef OPENCV3
    tCapture.set(cv::CAP_PROP_FRAME_WIDTH, tXRes);
    tCapture.set(cv::CAP_PROP_FRAME_HEIGHT, tYRes);
#else
    tCapture.set(CV_CAP_PROP_FRAME_WIDTH, tXRes);
    tCapture.set(CV_CAP_PROP_FRAME_HEIGHT, tYRes);
#endif

    cv::Mat tInputImage;
    chilitags::Chilitags tChilitags;
    for (;;) {
        tCapture.read(tInputImage);
        cv::imwrite("lastimage.png", tInputImage);
        tChilitags.find(tInputImage);
    }
    tCapture.release();

    return 0;
}
