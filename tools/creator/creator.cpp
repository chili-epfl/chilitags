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

#include <cstdlib>
#include <string>
#include <Codec.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char **argv)
{
	if (argc <= 1) {
		std::cout << "Usage: " << argv[0] << " tagID [zoom [margin]]\n";
		std::cout << " - tagId is the id of the tag to draw, between 0 and 1023,\n";
		std::cout << " - zoom is a non null integer indicating the length in pixel\n";
		std::cout << "   of each bit of the tag matrix (default: 1).\n";
		std::cout << " - margin is n if no white rectangle should be drawn around the tag,\n";
		std::cout << "   (make sure the black borders of the tag\n";
		std::cout << "   still contrast with where it is placed),\n";
		return 1;
	}

	std::string tOutputFilename = std::string(argv[1])+".png";
	int tTagId = std::atoi(argv[1]);
	int tZoom = (argc > 2) ? std::atoi(argv[2]) : 1;
	bool tNoMargin = (argc > 3 && argv[3][0] == 'n');

	// Creating the image of the bit matrix
	cv::Size tDataSize(6,6);
	unsigned char *tDataMatrix = new unsigned char[tDataSize.area()];
	chilitags::Codec tCodec(10, 16, 10, "1010101010", "10001000000100001");
	tCodec.getTagEncodedId(tTagId, tDataMatrix);
	cv::Mat tDataImage(tDataSize, CV_8U, tDataMatrix);
	tDataImage *= 255;

	// Adding the black border around the bit matrix
	cv::Size tBorderSize(2,2);
	cv::Mat tTagImage(tDataImage.size()+tBorderSize*2, CV_8U, cv::Scalar(0));
	tDataImage.copyTo(tTagImage(cv::Rect(tBorderSize, tDataImage.size())));

	// Adding the optionnal white margin
	cv::Size tMarginSize(0,0);
	if (!tNoMargin) tMarginSize += tBorderSize;
	cv::Mat tOutlinedImage(tTagImage.size()+tMarginSize*2, CV_8U, cv::Scalar(255));
	tTagImage.copyTo(tOutlinedImage(cv::Rect(tMarginSize, tTagImage.size())));

	// Resizing to specified zoom
	cv::Mat tOutputImage(tOutlinedImage.size()*tZoom, CV_8U);
	cv::resize(tOutlinedImage, tOutputImage, tOutputImage.size(), 0, 0, cv::INTER_NEAREST);

	cv::imwrite(tOutputFilename, tOutputImage);

	delete []tDataMatrix;

	return 0;
}
