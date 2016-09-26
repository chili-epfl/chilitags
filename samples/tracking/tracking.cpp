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

#include <chilitags.hpp>

#ifdef OPENCV3
#include <opencv2/core/utility.hpp> // getTickCount...
#include <opencv2/imgproc/imgproc.hpp>
#endif

#include <opencv2/core/core_c.h> // CV_AA

#include <opencv2/highgui/highgui.hpp>

#include <iostream>

// Not much interesting here, move along
void drawTags(
    cv::Mat outputImage,
    const chilitags::TagCornerMap &tags,
    int64 startTime,
    int64 endTime,
    bool detection
    );

int main(int argc, char* argv[])
{
    // Initialising input video
    int xRes = 640;
    int yRes = 480;
    int cameraIndex = 0;
    if (argc > 2) {
        xRes = std::atoi(argv[1]);
        yRes = std::atoi(argv[2]);
    }
    if (argc > 3) {
        cameraIndex = std::atoi(argv[3]);
    }

    // The source of input images
    cv::VideoCapture capture(cameraIndex);
    if (!capture.isOpened())
    {
        std::cerr << "Unable to initialise video capture." << std::endl;
        return 1;
    }
#ifdef OPENCV3
    capture.set(cv::CAP_PROP_FRAME_WIDTH, xRes);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, yRes);
#else
    capture.set(CV_CAP_PROP_FRAME_WIDTH, xRes);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, yRes);
#endif
    cv::Mat inputImage;

    // We need separate Chilitags if we want to compare find() with different
    // detection/tracking parameters on the same image

    // This one is the reference Chilitags
    chilitags::Chilitags detectedChilitags;
    detectedChilitags.setFilter(0, 0.0f);

    // This one will be called with JUST_TRACK when it has previously detected
    // something
    chilitags::Chilitags trackedChilitags;
    trackedChilitags.setFilter(0, 0.0f);

    cv::namedWindow("DisplayChilitags");

    // Do we want to run and show the reference detection ?
    bool showReference = true;
    // Do we want to run and show the tracking-based detection ?
    bool showTracking = true;

    // In the tracking-based detection, we need to know whether there is
    // something to track
    bool tracking = false;

    char keyPressed;
    while ('q' != (keyPressed = (char) cv::waitKey(1))) {

        // toggle the processing, according to user input
        if (keyPressed == 't') showTracking = !showTracking;
        if (keyPressed == 'd') showReference = !showReference;

        capture.read(inputImage);

        cv::Mat outputImage = inputImage.clone();

        // nothing new here
        if (showReference) {
            int64 startTime = cv::getTickCount();
            auto tags = detectedChilitags.find(inputImage);
            int64 endTime = cv::getTickCount();
            drawTags(outputImage, tags, startTime, endTime, true);
        }

        if (showTracking) {
            int64 startTime = cv::getTickCount();
            // Tracking needs something to track; it is initialised with a
            // regular detection (find()). When something is detected, tracking
            // will take over and return tags processed from the previous call
            // to track() as long as there is something returned.
            // When nothing is returned, we are back to regular detection.
            auto tags =
                trackedChilitags.find(inputImage, tracking ? chilitags::Chilitags::TRACK_ONLY : chilitags::Chilitags::TRACK_AND_DETECT);
            int64 endTime = cv::getTickCount();
            drawTags(outputImage, tags, startTime, endTime, false);
            tracking = !tags.empty();
        }

        cv::imshow("DisplayChilitags", outputImage);
    }

    cv::destroyWindow("DisplayChilitags");
    capture.release();

    return 0;
}

void drawTags(
    cv::Mat outputImage,
    const chilitags::TagCornerMap &tags,
    int64 startTime,
    int64 endTime,
    bool detection
    ){
    cv::Scalar COLOR = detection ?
                       cv::Scalar(0, 0, 255) :
                       cv::Scalar(255, 0, 0);

    for (const auto & tag : tags) {

        const cv::Mat_<cv::Point2f> corners(tag.second);

        for (size_t i = 0; i < 4; ++i) {
            static const int SHIFT = 16;
            static const float PRECISION = 1<<SHIFT;
            cv::line(
                outputImage,
                PRECISION*corners(i),
                PRECISION*corners((i+1)%4),
#ifdef OPENCV3
                COLOR, detection ? 3 : 1, cv::LINE_AA, SHIFT);
#else
                COLOR, detection ? 3 : 1, CV_AA, SHIFT);
#endif
        }

        cv::Point2f center = 0.5f*(corners(0) + corners(2));
        cv::putText(outputImage, cv::format("%d", tag.first), center,
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, COLOR);
    }

    float processingTime = 1000.0f*((float) endTime - startTime)/cv::getTickFrequency();
    cv::putText(outputImage,
                cv::format("%dx%d %4.0f ms (press '%c' to toggle %s)",
                           outputImage.cols, outputImage.rows,
                           processingTime,
                           detection ? 'd' : 't',
                           detection ? "simple detection" : "tracking"
                           ),
                cv::Point(32,detection ? 32 : 64),
                cv::FONT_HERSHEY_SIMPLEX, 0.5f, COLOR);
}
