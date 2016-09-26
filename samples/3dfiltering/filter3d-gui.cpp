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

#include <iostream>

#include <chilitags.hpp>

#include <opencv2/core/core.hpp> // for cv::Mat
#include <opencv2/core/core_c.h> // CV_AA
#include <opencv2/highgui/highgui.hpp> // for camera capture
#include <opencv2/imgproc/imgproc.hpp> // for camera capture

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    cout
        << "Usage: "<< argv[0]
        << " [-c <tag configuration (YAML)>] [-i <camera calibration (YAML)>]\n";

    const char* intrinsicsFilename = 0;
    const char* configFilename = 0;

    for( int i = 1; i < argc; i++ )
    {
        if( strcmp(argv[i], "-c") == 0 )
            configFilename = argv[++i];
        else if( strcmp(argv[i], "-i") == 0 )
            intrinsicsFilename = argv[++i];
    }

    /*****************************/
    /*    Init camera capture    */
    /*****************************/
    int cameraIndex = 0;
    cv::VideoCapture capture(cameraIndex);
    if (!capture.isOpened())
    {
        cerr << "Unable to initialise video capture.\n";
        return 1;
    }

    /******************************/
    /* Setting up pose estimation */
    /******************************/
#ifdef OPENCV3
    double inputWidth  = capture.get(cv::CAP_PROP_FRAME_WIDTH);
    double inputHeight = capture.get(cv::CAP_PROP_FRAME_HEIGHT);
#else
    double inputWidth  = capture.get(CV_CAP_PROP_FRAME_WIDTH);
    double inputHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
#endif

    chilitags::Chilitags3D chilitags3D(Size(inputWidth, inputHeight));

    if (configFilename) chilitags3D.readTagConfiguration(configFilename);

    if (intrinsicsFilename) {
        Size calibratedImageSize = chilitags3D.readCalibration(intrinsicsFilename);
#ifdef OPENCV3
        capture.set(cv::CAP_PROP_FRAME_WIDTH, calibratedImageSize.width);
        capture.set(cv::CAP_PROP_FRAME_HEIGHT, calibratedImageSize.height);
#else
        capture.set(CV_CAP_PROP_FRAME_WIDTH, calibratedImageSize.width);
        capture.set(CV_CAP_PROP_FRAME_HEIGHT, calibratedImageSize.height);
#endif
    }

    cv::Mat projectionMat = cv::Mat::zeros(4,4,CV_64F);
    chilitags3D.getCameraMatrix().copyTo(projectionMat(cv::Rect(0,0,3,3)));
    cv::Matx44d projection = projectionMat;
    projection(3,2) = 1;

    /*****************************/
    /*             Go!           */
    /*****************************/
    cv::namedWindow("Pose Estimation");

    char keyPressed;
    bool filterEnabled = true;

    cv::Mat Q = (cv::Mat_<float>(7,7) <<
                 1e-3f,  0,      0,      0,      0,      0,      0,
                 0,      1e-3f,  0,      0,      0,      0,      0,
                 0,      0,      1e-3f,  0,      0,      0,      0,
                 0,      0,      0,      1e-4f,  0,      0,      0,
                 0,      0,      0,      0,      1e-4f,  0,      0,
                 0,      0,      0,      0,      0,      1e-4f,  0,
                 0,      0,      0,      0,      0,      0,      1e-4f);
    float alphaQ = 1.0f;

    cv::Mat R = (cv::Mat_<float>(7,7) <<
                 1e-3f,  0,      0,      0,      0,      0,      0,
                 0,      1e-3f,  0,      0,      0,      0,      0,
                 0,      0,      1e-1f,  0,      0,      0,      0,
                 0,      0,      0,      1e-3f,  0,      0,      0,
                 0,      0,      0,      0,      1e-2f,  0,      0,
                 0,      0,      0,      0,      0,      1e-2f,  0,
                 0,      0,      0,      0,      0,      0,      1e-5f);
    float alphaR = 1.0f;

    while ('q' != (keyPressed = (char) cv::waitKey(1))) {

        switch(keyPressed) {
        case 'f':
            filterEnabled = !filterEnabled;
            chilitags3D.enableFilter(filterEnabled);
            break;
        case 'w':
            alphaQ *= 10.0f;
            chilitags3D.setFilterProcessNoiseCovariance(alphaQ*Q);
            break;
        case 's':
            alphaQ /= 10.0f;
            chilitags3D.setFilterProcessNoiseCovariance(alphaQ*Q);
            break;
        case 'e':
            alphaR *= 10.0f;
            chilitags3D.setFilterObservationNoiseCovariance(alphaR*R);
            break;
        case 'd':
            alphaR /= 10.0f;
            chilitags3D.setFilterObservationNoiseCovariance(alphaR*R);
            break;
        }

        cv::Mat inputImage;
        capture.read(inputImage);
        cv::Mat outputImage = inputImage.clone();

        cv::putText(outputImage, cv::format("Filtering %s, press 'f' to toggle",filterEnabled ? "ENABLED" : "DISABLED"),
                    cv::Point(8,20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255));

        cv::putText(outputImage, cv::format("Process covariance multiplier: %f, press 'w' or 's' to modify", alphaQ),
                    cv::Point(8,36), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255));

        cv::putText(outputImage, cv::format("Observation covariance multiplier: %f, press 'e' or 'd' to modify", alphaR),
                    cv::Point(8,52), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255));

        for (auto& kv : chilitags3D.estimate(inputImage, chilitags::Chilitags::DETECT_PERIODICALLY)) {

            static const float DEFAULT_SIZE = 20.f;
            static const cv::Vec4d UNITS[4] {
                {0.f, 0.f, 0.f, 1.f},
                {DEFAULT_SIZE, 0.f, 0.f, 1.f},
                {0.f, DEFAULT_SIZE, 0.f, 1.f},
                {0.f, 0.f, DEFAULT_SIZE, 1.f},
            };

            cv::Matx44d transformation = kv.second;
            cv::Vec4f referential[4] = {
                projection*transformation*UNITS[0],
                projection*transformation*UNITS[1],
                projection*transformation*UNITS[2],
                projection*transformation*UNITS[3],
            };

            std::vector<cv::Point2f> t2DPoints;
            for (auto homogenousPoint : referential)
                t2DPoints.push_back(cv::Point2f(
                                        homogenousPoint[0]/homogenousPoint[3],
                                        homogenousPoint[1]/homogenousPoint[3]));

            static const int SHIFT = 16;
            static const float PRECISION = 1<<SHIFT;
            static const std::string AXIS_NAMES[3] = { "x", "y", "z" };
            static const cv::Scalar AXIS_COLORS[3] = {
                {0,0,255},{0,255,0},{255,0,0},
            };
            for (int i : {1,2,3}) {
                cv::line(
                    outputImage,
                    PRECISION*t2DPoints[0],
                    PRECISION*t2DPoints[i],
                    AXIS_COLORS[i-1],
#ifdef OPENCV3
                    2, cv::LINE_AA, SHIFT);
#else
                    2, CV_AA, SHIFT);
#endif
            }
        }
        cv::imshow("Pose Estimation", outputImage);
    }

    cv::destroyWindow("Pose Estimation");
    capture.release();

    return 0;
}

