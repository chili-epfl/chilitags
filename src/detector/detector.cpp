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
// This header provides an easy way to use the tag detection information
#include <Chilitag.hpp>

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
	tCapture.set(CV_CAP_PROP_FRAME_WIDTH, tXRes);
	tCapture.set(CV_CAP_PROP_FRAME_HEIGHT, tYRes);

	cv::namedWindow("DisplayChilitags");

	// The time at which run was last called, to compute the fps.
	int64 tTickCount = cv::getTickCount();

	// The tag detection happens in the DetectChilitags class.
	// All it needs is a pointer to a OpenCv Image, i.e. a cv::Mat *
	// and a call to its update() method every time the image is updated.
	cv::Mat tInputImage;
	chilitags::DetectChilitags tDetectChilitags(&tInputImage);

	// Main loop, exiting when 'q is pressed'
	for (; 'q' != (char) cv::waitKey(1); ) {

		// Capture a new image.
		tCapture.read(tInputImage);

		// Detect tags on the current image.
		tDetectChilitags.update();

		// The color (magenta) that will be used for all information
		// overlaid on the captured image
		const static cv::Scalar scColor(255, 0, 255);

		// These constants will be given to OpenCv for drawing with
		// sub-pixel accuracy with fixed point precision coordinates
		static const int scShift = 16;
		static const float scPrecision = 1<<scShift;

		// We dont want to draw directly on the input image, so we clone it
		cv::Mat tOutputImage = tInputImage.clone();

		// We iterate over the 1024 possible tags (from #0 to #1023)
		for (int tTagId = 0; tTagId < 1024; ++tTagId) {

			// The Chilitag class is a convenience handle to acces information
			// related to a given tag.
			// The object itself is lightweight, so we can create and delete it
			// frequently (we don't need to store it as member for example)
			chilitags::Chilitag tTag(tTagId);

			// Chilitag allows us to easily access the two main pieces of data
			// First, the isPresent() method tells us whether the related tag
			// has been detected in the last frame.
			// This is a first and necessary step to access further information
			// about the tag, as a "absent" tag will have obsolete information.
			if (tTag.isPresent()) {
				
				// Second, now that we know that the tag has been updated, the
				// getCorners() method returns the coordinates of the
				// quadrilateral containing the tag on the input picture.
				chilitags::Quad tCorners = tTag.getCorners();

				// We start by drawing this quadrilateral
				for (size_t i = 0; i < chilitags::Quad::scNPoints; ++i) {
					cv::line(
						tOutputImage,
						scPrecision*tCorners[i],
						scPrecision*tCorners[(i+1)%4],
						scColor, 1, CV_AA, scShift);
				}

				// The quadrilateral is given under the form of a Quad class,
				// which provide a minimal set of geometrical functionalities,
				// such as getCenter()
				cv::Point2f tCenter = tCorners.getCenter();

				// We will print the identifier of the tag at its center
				cv::putText(tOutputImage, cv::format("%d", tTagId), tCenter,
					cv::FONT_HERSHEY_SIMPLEX, 0.5, scColor);

				// Other points an be computed from the four corners of the Quad.
				// Chilitags are oriented. It means that the points 0,1,2,3 of
				// the Quad coordinates are consistently the top-left, top-right,
				// bottom-right and bottom-left
				// (i.e. clockwise, starting from top-left)
				// Using this, we can compute (an approximation of) the middle of
				// the top side of the tag...
				cv::Point2f tTop = 0.5f*(tCorners[0]+tCorners[1]);
				// and of its right side
				cv::Point2f tRight = 0.5f*(tCorners[1]+tCorners[2]);

				// We display the length in pixel of these sides
				cv::putText(tOutputImage,
					cv::format("The top border is %.2fpx long.",
						cv::norm(tCorners[0] - tCorners[1])), tTop,
					cv::FONT_HERSHEY_SIMPLEX, 0.5, scColor);

				cv::putText(tOutputImage,
					cv::format("The right border is %.2fpx long.",
						cv::norm(tCorners[1] - tCorners[2])), tRight,
					cv::FONT_HERSHEY_SIMPLEX, 0.5, scColor);

				// And we draw a line from the center to the midlle of these sides,
				// to show the orientation of the tag.
				cv::line(tOutputImage,
					scPrecision*tCenter,
					scPrecision*tTop,
					scColor, 1, CV_AA, scShift);
				cv::line(tOutputImage,
					scPrecision*tCenter,
					scPrecision*tRight,
					scColor, 1, CV_AA, scShift);
			}
		}
		
		// Some stats on the current frame (resolution and framerate)
		int64 tNewTickCount = cv::getTickCount();
		cv::putText(tOutputImage,
			cv::format("%dx%d@%.0f fps (press q to quit)",
				tOutputImage.cols, tOutputImage.rows,
				cv::getTickFrequency() / ((double) (tNewTickCount-tTickCount))),
			cv::Point(32,32),
			cv::FONT_HERSHEY_SIMPLEX, 0.5, scColor);
		tTickCount = tNewTickCount;

		// Finally...
		cv::imshow("DisplayChilitags", tOutputImage);
	}

	cv::destroyWindow("DisplayChilitags");
	tCapture.release();

	return 0;
}
