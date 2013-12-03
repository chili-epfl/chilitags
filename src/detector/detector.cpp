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
#include <DetectChilitags.hpp>

// This one contains a simple filter to avoid a "flickering" detection
#include <CachingFilter.hpp>

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

	cv::namedWindow("DisplayChilitags");

	// The time at which run was last called, to compute the fps.
	int64 tTickCount = cv::getTickCount();

	// The tag detection happens in the DetectChilitags class.
	// All it needs is a pointer to a OpenCv Image, i.e. a cv::Mat *
	// and a call to its update() method every time the image is updated.
	cv::Mat tInputImage;
	chilitags::DetectChilitags tDetectChilitags;

	// The detection is raw, i.e. if a tag is not detected during one frame,
	// the tag will "disappear", which can result in flickering
	// To address this, the CachingFilter "cheats" by keeping tags for n frames
	// at the same position. When tags disappear for more than 5 frames,
	// CachingFilter actually removes it.
	// The default of CachingFilter is to keep tags for n=5 frames.
	// Here, we set it to 4.
	chilitags::CachingFilter tFilter(4);

	// Main loop, exiting when 'q is pressed'
	for (; 'q' != (char) cv::waitKey(1); ) {

		// Capture a new image.
		tCapture.read(tInputImage);

		// Detect tags on the current image (and time the detection);
		// DetectChilitags and CachingFilter are functors, which means that
		// they are objects used like function.
		// Here, we "call" tDetectChilitags with the captured image
		// and the result is provided to tFilter, which gives us a map
		// describing the tags.
		// The map associates ids (between 0 and 1023) to four 2D points
		// corresponding to the corners of the tag in the picture.
	    int64 tStartTime = cv::getTickCount();
		std::map<int, std::vector<cv::Point2f>> tTags = 
			tFilter(
				tDetectChilitags(tInputImage));
	    int64 tEndTime = cv::getTickCount();
		double tProcessingTime = 1000.0*((double) tEndTime - tStartTime)/cv::getTickFrequency();


		// Now we start using the result of the detection.

		// The color (magenta) that will be used for all information
		// overlaid on the captured image
		const static cv::Scalar scColor(255, 0, 255);

		// These constants will be given to OpenCv for drawing with
		// sub-pixel accuracy with fixed point precision coordinates
		static const int scShift = 16;
		static const float scPrecision = 1<<scShift;

		// We dont want to draw directly on the input image, so we clone it
		cv::Mat tOutputImage = tInputImage.clone();

		for (const std::pair<int, std::vector<cv::Point2f>> & tTag : tTags) {

			int tId = tTag.first;
			const std::vector<cv::Point2f> &tCorners = tTag.second;

			// We start by drawing the corners
			for (size_t i = 0; i < 4; ++i) {
				cv::line(
					tOutputImage,
					scPrecision*tCorners[i],
					scPrecision*tCorners[(i+1)%4],
					scColor, 1, CV_AA, scShift);
			}

			// Other points an be computed from the four corners of the Quad.
			// Chilitags are oriented. It means that the points 0,1,2,3 of
			// the Quad coordinates are consistently the top-left, top-right,
			// bottom-right and bottom-left
			// (i.e. clockwise, starting from top-left)
			// Using this, we can compute (an approximation of) the center of
			// tag.
			cv::Point2f tCenter = 0.5*(tCorners[0] + tCorners[2]);
			cv::putText(tOutputImage, cv::format("%d", tId), tCenter,
				cv::FONT_HERSHEY_SIMPLEX, 0.5, scColor);
		}
		
		// Some stats on the current frame (resolution and processing time)
		cv::putText(tOutputImage,
			cv::format("%dx%d %4.0f ms (press q to quit)",
				tOutputImage.cols, tOutputImage.rows,
				tProcessingTime),
			cv::Point(32,32),
			cv::FONT_HERSHEY_SIMPLEX, 0.5, scColor);

		// Finally...
		cv::imshow("DisplayChilitags", tOutputImage);
	}

	cv::destroyWindow("DisplayChilitags");
	tCapture.release();

	return 0;
}
