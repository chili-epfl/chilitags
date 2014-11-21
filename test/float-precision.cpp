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

#include "DetectionTestCase.hpp"

#include <chilitags.hpp>

#include <cfloat>
#include <cmath>

TEST(FloatPrecision, Snapshots) {

    //Percent difference between single and double precision greater than this value will not be tolerated
    const double DIFF_FAIL_TRHESH = 1e-5;

    // Initialise the data path with en empty modulename,
    // to get the data from the root of the test data path
    cvtest::TS::ptr()->init("");

    chilitags::Chilitags3Df chilitagsf;
    chilitagsf.getChilitags().setPerformance(chilitags::Chilitags::ROBUST);
    chilitagsf.setFilter(0, 0.0f);

    chilitags::Chilitags3Dd chilitagsd;
    chilitagsd.getChilitags().setPerformance(chilitags::Chilitags::ROBUST);
    chilitagsd.setFilter(0, 0.0f);

    for (auto testCase : chilitags::DetectionTestCase::all) {
        std::string path = std::string(cvtest::TS::ptr()->get_data_path())+testCase.filename;
        cv::Mat image = cv::imread(path);

        if(image.data) {

            auto tagsd = chilitagsd.estimate(image, chilitags::Chilitags::DETECT_ONLY);
            auto tagsf = chilitagsf.estimate(image, chilitags::Chilitags::DETECT_ONLY);

            ASSERT_EQ(tagsf.size(), tagsd.size()) <<
                "Single precision found " << tagsf.size() <<
                " tags while double precision found " << tagsd.size() << " tags in " << testCase.filename;

            double diff;
            for(const auto& tag : tagsf){
                const auto& matf = tag.second;
                const auto& matd = tagsd[tag.first];
                for(int i=0;i<4;i++)
                    for(int j=0;j<4;j++){
                        diff = ((double)matf(i,j) - matd(i,j))/matd(i,j);
                        if(!std::isnan(diff))
                            ASSERT_LT(diff, DIFF_FAIL_TRHESH) <<
                                tag.first << "'s single and double precision transforms differ more than " << DIFF_FAIL_TRHESH*100 << "%% in ("
                                << i << "," << j << ");" << std::endl << " Single precision transform: " << matf << std::endl
                                << "Double precision transform:" << matd;
                    }
            }
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
}

CV_TEST_MAIN(".")
