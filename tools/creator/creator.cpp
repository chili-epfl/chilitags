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

#include <cstdlib>
#include <string>
#include <chilitags.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char **argv)
{
    if (argc <= 1) {
        std::cout << "Usage: " << argv[0] << " tagID [zoom [margin [red green blue]]]\n";
        std::cout << " - tagId is the id of the tag to draw, between 0 and 1023,\n";
        std::cout << " - zoom is a non null integer indicating the length in pixel\n";
        std::cout << "   of each bit of the tag matrix (default: 1).\n";
        std::cout << " - margin is n if no white rectangle should be drawn around the tag,\n";
        std::cout << "   (make sure the black borders of the tag\n";
        std::cout << "   still contrast with where it is placed),\n";
        std::cout << " - red, green and blue define the color with which to draw the tag.\n";
        std::cout << "   The darker, the better. Black is default and optimal.\n";
        return 1;
    }

    std::string outputFilename = std::string(argv[1])+".png";
    int tagId = std::atoi(argv[1]);
    int zoom = (argc > 2) ? std::atoi(argv[2]) : 1;
    bool noMargin = (argc > 3 && argv[3][0] == 'n');
    cv::Scalar color = (argc > 6 ? cv::Scalar(std::atoi(argv[4]), std::atoi(argv[5]), std::atoi(argv[6])) : cv::Scalar(0,0,0));

    cv::imwrite(outputFilename, chilitags::Chilitags().draw(tagId, zoom, !noMargin, color));

    return 0;
}
