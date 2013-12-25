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


// The Chilitags header
#include <chilitags.hpp>

#ifdef OPENCV3
#include <opencv2/core/utility.hpp> // getTickCount...
#endif

#include <opencv2/core/core_c.h> // CV_AA

// OpenCV goodness for I/O
#include <opencv2/highgui/highgui.hpp>

#include <iostream>


int main(int argc, char* argv[])
{
    // Simple parsing of the parameters related to the image acquisition
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

    // The tag detection happens in the Chilitags class.
    chilitags::Chilitags tChilitags;

    // The detection is not perfect, so if a tag is not detected during one frame,
    // the tag will shortly disappears, which results in flickering.
    // To address this, Chilitags "cheats" by keeping tags for n frames
    // at the same position. When tags disappear for more than 5 frames,
    // Chilitags actually removes it.
    // Here, we cancel this to show the raw detection results.
    tChilitags.setPersistence(0);

    cv::namedWindow("DisplayChilitags");
    // Main loop, exiting when 'q is pressed'
    for (; 'q' != (char) cv::waitKey(1); ) {

        // Capture a new image.
        tCapture.read(tInputImage);

        // Start measuring the time needed for the detection
        int64 tStartTime = cv::getTickCount();

        // Detect tags on the current image (and time the detection);
        // The resulting map associates tag ids (between 0 and 1023)
        // to four 2D points corresponding to the corners positions
        // in the picture.
        std::map<int, std::vector<cv::Point2f> > tTags = tChilitags.find(tInputImage);

        // Measure the processing time needed for the detection
        int64 tEndTime = cv::getTickCount();
        double tProcessingTime = 1000.0*((double) tEndTime - tStartTime)/cv::getTickFrequency();


        // Now we start using the result of the detection.

        // First, we set up some constants related to the information overlaid
        // on the captured image
        const static cv::Scalar COLOR(255, 0, 255);
        // OpenCv can draw with sub-pixel precision with fixed point coordinates
        static const int SHIFT = 16;
        static const float PRECISION = 1<<SHIFT;

        // We dont want to draw directly on the input image, so we clone it
        cv::Mat tOutputImage = tInputImage.clone();

        for (const std::pair<int, std::vector<cv::Point2f> > & tTag : tTags) {

            int tId = tTag.first;
            const std::vector<cv::Point2f> &tCorners = tTag.second;

            // We start by drawing the borders of the tag
            for (size_t i = 0; i < 4; ++i) {
                cv::line(
                    tOutputImage,
                    PRECISION*tCorners[i],
                    PRECISION*tCorners[(i+1)%4],
                    COLOR, 1, CV_AA, SHIFT);
            }

            // Other points can be computed from the four corners of the Quad.
            // Chilitags are oriented. It means that the points 0,1,2,3 of
            // the Quad coordinates are consistently the top-left, top-right,
            // bottom-right and bottom-left corners.
            // (i.e. clockwise, starting from top-left)
            // Using this, we can compute (an approximation of) the center of
            // tag.
            cv::Point2f tCenter = 0.5*(tCorners[0] + tCorners[2]);
            cv::putText(tOutputImage, cv::format("%d", tId), tCenter,
                        cv::FONT_HERSHEY_SIMPLEX, 0.5, COLOR);
        }

        // Some stats on the current frame (resolution and processing time)
        cv::putText(tOutputImage,
                    cv::format("%dx%d %4.0f ms (press q to quit)",
                               tOutputImage.cols, tOutputImage.rows,
                               tProcessingTime),
                    cv::Point(32,32),
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, COLOR);

        // Finally...
        cv::imshow("DisplayChilitags", tOutputImage);
    }

    cv::destroyWindow("DisplayChilitags");
    tCapture.release();

    return 0;
}
