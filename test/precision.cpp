/********************************************************************************
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

#include<fstream>
#include<string>

#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <chilitags.hpp>
#include "LocalisationTestCase.hpp"
#include "TestUtils.hpp"

void run(const chilitags::LocalisationTestCase &testCase)
{

    chilitags::Chilitags chilitags;
    chilitags.setPerformance(chilitags::Chilitags::ROBUST);
    chilitags.setFilter(0, 0.f);

    cvtest::TS::ptr()->init("");
    std::string path = std::string(cvtest::TS::ptr()->get_data_path())+testCase.file;
    cv::Mat inputImage = cv::imread(path);
    if(!inputImage.data) {
        ADD_FAILURE()
            << "Unable to read: " << path << "\n"
            << "Did you correctly set the OPENCV_TEST_DATA_PATH environment variable?\n"
            << "CMake takes care of this if you set its TEST_DATA variable.\n"
            << "You can download the test data from\n"
            << "https://github.com/chili-epfl/chilitags-testdata";
        return;
    }

    auto tags = chilitags.find(inputImage, chilitags::Chilitags::DETECT_ONLY);

    std::vector<cv::Point2f> imagePoints;
    std::vector<cv::Point3f> objectPoints;
    for (auto & tag : tags) {
        const int id = tag.first;
        const cv::Mat_<cv::Point2f> corners(tag.second);

        for (size_t i = 0; i < 4; ++i) {
            objectPoints.push_back(testCase.cornerPositionInObject(id, i));
            imagePoints.push_back(corners(i));
        }
    }

    static const cv::Size CAMERA_SIZE(640, 480);
    static const float FOCAL_LENGTH = 700.0f;
    static const cv::Matx33f cameraMatrix = {
        FOCAL_LENGTH , 0            , (float) CAMERA_SIZE.width /2,
        0            , FOCAL_LENGTH , (float) CAMERA_SIZE.height/2,
        0            , 0            , 1
    };
    static cv::Mat distCoeffs;

    cv::Mat rotation;
    cv::Mat translation;

    cv::solvePnP(objectPoints,
                 imagePoints,
                 cameraMatrix, distCoeffs,
                 rotation, translation, false,
#ifdef OPENCV3
                 cv::SOLVEPNP_ITERATIVE);
#else
                 cv::ITERATIVE);
#endif

    std::vector<cv::Point2f> projectedPoints;
    projectPoints(cv::Mat(objectPoints), rotation, translation,
                  cameraMatrix, distCoeffs, projectedPoints);

    auto nPoints = imagePoints.size();
    std::vector<float> errors;
    for (std::size_t i = 0; i<nPoints; ++i) {
        errors.push_back(cv::norm(imagePoints[i] - projectedPoints[i]));
    }

    float relativeMeanError = TestUtils::mean(errors)/testCase.tagSize;
    float relativeSigma = TestUtils::variance(errors)/testCase.tagSize;

    EXPECT_GT(0.01f, relativeMeanError);
    EXPECT_GT(0.005f, relativeSigma);
}


TEST(Precision, Screenshot) {
    for (const auto &testCase : chilitags::LocalisationTestCase::all) {
        run(testCase);
    }
}

CV_TEST_MAIN(".")
