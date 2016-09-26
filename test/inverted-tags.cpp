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

#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <opencv2/highgui/highgui.hpp>

#include "test-metadata.hpp"

#include <chilitags.hpp>

#include <cfloat>
#include <cmath>

TEST(InvertedTags, Screen) {

    // Initialise the data path with en empty modulename,
    // to get the data from the root of the test data path
    cvtest::TS::ptr()->init("");

    chilitags::Chilitags chilitags;

    std::string path = std::string(cvtest::TS::ptr()->get_data_path())
                       +"stills/640x480/inverted.jpg";

    cv::Mat image = cv::imread(path);

    if(image.data) {
        auto tags = chilitags.find(image);
        ASSERT_EQ(1, tags.size());
        ASSERT_EQ(0, tags.begin()->first);
    }
    else {
        ADD_FAILURE()
            << "Unable to read: " << path << "\n"
            << "Did you correctly set the OPENCV_TEST_DATA_PATH environment variable?\n"
            << "CMake takes care of this if you set its TEST_DATA variable.\n"
            << "You can download the test data from\n"
            << "https://github.com/chili-epfl/chilitags-testdata";
    }
}

CV_TEST_MAIN(".")
