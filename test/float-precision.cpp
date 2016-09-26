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

TEST(FloatPrecision, Snapshots) {

    // Initialise the data path with en empty modulename,
    // to get the data from the root of the test data path
    cvtest::TS::ptr()->init("");

    chilitags::Chilitags3Df chilitagsf;
    chilitagsf.getChilitags().setPerformance(chilitags::Chilitags::ROBUST);
    chilitagsf.enableFilter(false);

    chilitags::Chilitags3Dd chilitagsd;
    chilitagsd.getChilitags().setPerformance(chilitags::Chilitags::ROBUST);
    chilitagsd.enableFilter(false);

    for (auto testCase : TestMetadata::all) {
        std::string path = std::string(cvtest::TS::ptr()->get_data_path())+testCase.filename;
        cv::Mat image = cv::imread(path);

        if(image.data) {

            auto tagsd = chilitagsd.estimate(image, chilitags::Chilitags::DETECT_ONLY);
            auto tagsf = chilitagsf.estimate(image, chilitags::Chilitags::DETECT_ONLY);

            ASSERT_EQ(tagsf.size(), tagsd.size()) <<
                "Single precision found " << tagsf.size() <<
                " tags while double precision found " << tagsd.size() << " tags in " << testCase.filename;

            double diff;
            for(const auto& tag : tagsf) {
                const auto& matf = tag.second;
                const auto& matd = tagsd[tag.first];

                //Test rotation component
                double failThreshold = 1e-5; //TODO: What does this threshold actually mean?
                for(int i=0; i<3; i++)
                    for(int j=0; j<3; j++) {
                        diff = (double)matf(i,j) - matd(i,j);
                        if(!std::isnan(diff))
                            ASSERT_LT(diff, failThreshold) <<
                                tag.first << "'s single and double precision transforms differ more than " << failThreshold << "%% in ("
                                                           << i << "," << j << ");" << std::endl << " Single precision transform: " << matf << std::endl
                                                           << "Double precision transform:" << matd;
                    }

                //Test translation component
                failThreshold = 1e-1; //Tenth of a millimeter
                for(int i=0; i<3; i++) {
                    diff = (double)matf(i,3) - matd(i,3);
                    if(!std::isnan(diff))
                        ASSERT_LT(diff, failThreshold) <<
                            tag.first << "'s single and double precision transforms differ more than " << failThreshold << "%% in ("
                                                       << i << "," << "3);" << std::endl << " Single precision transform: " << matf << std::endl
                                                       << "Double precision transform:" << matd;
                }

                //Test last row
                ASSERT_EQ(matf(3,0), 0.0f); ASSERT_EQ(matf(3,1), 0.0f); ASSERT_EQ(matf(3,2), 0.0f); ASSERT_EQ(matf(3,3), 1.0f);
                ASSERT_EQ(matd(3,0), 0.0);  ASSERT_EQ(matd(3,1), 0.0);  ASSERT_EQ(matd(3,2), 0.0);  ASSERT_EQ(matd(3,3), 1.0);
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
