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

cv::Scalar COLOR = cv::Scalar(0, 0, 255);

void drawTags(cv::Mat outputImage, std::map<int, chilitags::Quad> const& tags);

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

    chilitags::Chilitags chilitags;
    chilitags.setFilter(0, 0.);

    cv::namedWindow("DisplayChilitags");

    char keyPressed;
    const char* trigName = "DETECT_PERIODICALLY";
    chilitags::Chilitags::DetectionTrigger trig = chilitags::Chilitags::DETECT_PERIODICALLY;
    while ('q' != (keyPressed = (char) cv::waitKey(1))) {

        // toggle the processing mode, according to user input
        if(keyPressed == 't') {
            if(trig == chilitags::Chilitags::DETECT_PERIODICALLY) {
                trig = chilitags::Chilitags::ASYNC_DETECT_PERIODICALLY;
                trigName = "ASYNC_DETECT_PERIODICALLY";
            }
            else if(trig == chilitags::Chilitags::ASYNC_DETECT_PERIODICALLY) {
                trig = chilitags::Chilitags::ASYNC_DETECT_ALWAYS;
                trigName = "ASYNC_DETECT_ALWAYS";
            }
            else{
                trig = chilitags::Chilitags::DETECT_PERIODICALLY;
                trigName = "DETECT_PERIODICALLY";
            }
        }

        capture.read(inputImage);

        cv::Mat outputImage = inputImage.clone();

        auto tags = chilitags.find(inputImage, trig);
        drawTags(outputImage, tags);

        //Print detection trigger
        cv::putText(outputImage,
                    cv::format("Detection trigger: %s (press 't' to toggle)", trigName),
                    cv::Point(8,yRes - 24),
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, COLOR);

        cv::putText(outputImage,
                    cv::format("Run 'top -H -p `pgrep async-detection`' to see running threads", trigName),
                    cv::Point(8,yRes - 8),
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, COLOR);

        cv::imshow("DisplayChilitags", outputImage);
    }

    cv::destroyWindow("DisplayChilitags");
    capture.release();

    return 0;
}

void drawTags(
    cv::Mat outputImage,
    const std::map<int, chilitags::Quad> &tags)
{
    for(const auto& tag : tags) {

        const cv::Mat_<cv::Point2f> corners(tag.second);

        for(size_t i = 0; i < 4; ++i) {
            const int SHIFT = 16;
            const float PRECISION = 1 << SHIFT;
            cv::line(
                outputImage,
                PRECISION*corners(i),
                PRECISION*corners((i+1)%4),
#ifdef OPENCV3
                COLOR, 3, cv::LINE_AA, SHIFT);
#else
                COLOR, 3, CV_AA, SHIFT);
#endif
        }

        cv::Point2f center = 0.5*(corners(0) + corners(2));
        cv::putText(outputImage, cv::format("%d", tag.first), center,
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, COLOR);
    }
}
