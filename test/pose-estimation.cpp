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

#include <fstream>
#include <string>

#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <opencv2/core/core.hpp>

#include <chilitags.hpp>

namespace {

//As assumed by Chilitags3D
const cv::Size CAMERA_SIZE(640,480);
const float FOCAL_LENGTH = 700.0f;

const cv::Matx44f projectionMatrix = {
    FOCAL_LENGTH,   0,              (float) CAMERA_SIZE.width/2,   0,
    0,              FOCAL_LENGTH,   (float) CAMERA_SIZE.height/2,  0,
    0,              0,              1,                              0,
    0,              0,              1,                              0,
};

cv::Matx44f makeTransformation(
    float rx, float ry, float rz,
    float tx, float ty, float tz){

    static const float DEG2RAD = 3.141593f / 180.f;
    float A = cos(rx * DEG2RAD);
    float B = sin(rx * DEG2RAD);
    float C = cos(ry * DEG2RAD);
    float D = sin(ry * DEG2RAD);
    float E = cos(rz * DEG2RAD);
    float F = sin(rz * DEG2RAD);

    return {
               C*E,        -C*F,       D,      tx,
                B*D*E+A*F,  -B*D*F+A*E, -B*C,   ty,
               -A*D*E+B*F, A*D*F+B*E,  A*C,    tz,
               0.f,        0.f,        0.f,    1.f,
    };
}

chilitags::Quad makeTransformedCorners(cv::Matx44f transformation, float size) {

    cv::Vec4f homogenousPoint0 = {   0,    0, 0.f, 1.f};
    cv::Vec4f homogenousPoint1 = {size,    0, 0.f, 1.f};
    cv::Vec4f homogenousPoint2 = {size, size, 0.f, 1.f};
    cv::Vec4f homogenousPoint3 = {   0, size, 0.f, 1.f};

    cv::Vec4f transformedPoint0 = projectionMatrix*transformation*homogenousPoint0;
    cv::Vec4f transformedPoint1 = projectionMatrix*transformation*homogenousPoint1;
    cv::Vec4f transformedPoint2 = projectionMatrix*transformation*homogenousPoint2;
    cv::Vec4f transformedPoint3 = projectionMatrix*transformation*homogenousPoint3;

    transformedPoint0 /= transformedPoint0(3);
    transformedPoint1 /= transformedPoint1(3);
    transformedPoint2 /= transformedPoint2(3);
    transformedPoint3 /= transformedPoint3(3);
    return {
               (float) transformedPoint0(0), (float) transformedPoint0(1),
               (float) transformedPoint1(0), (float) transformedPoint1(1),
               (float) transformedPoint2(0), (float) transformedPoint2(1),
               (float) transformedPoint3(0), (float) transformedPoint3(1),
    };
}

}

TEST(Estimate3dPose, 2D) {
    chilitags::Chilitags3D chilitags3D(CAMERA_SIZE);
    auto tagImage = chilitags3D.getChilitags().draw(42, 5, true);
    auto tags = chilitags3D.getChilitags().find(tagImage);
    EXPECT_EQ(1, tags.size());
    auto objects = chilitags3D.estimate(tags);
    EXPECT_EQ(1, objects.size());
}

TEST(Estimate3dPose, FreeTags) {
    auto expectedTransformation = makeTransformation(35,45,65,20,40,60);

    float size = 37;
    chilitags::Quad corners = makeTransformedCorners(expectedTransformation, size);

    chilitags::Chilitags3D chilitags3D(CAMERA_SIZE);
    chilitags3D.setDefaultTagSize(size);

    int tagId = 0;
    auto result = chilitags3D.estimate({{tagId,corners}});
    ASSERT_EQ(1, result.size());

    std::string actualID = result.cbegin()->first;
    EXPECT_EQ(cv::format("tag_%d", tagId), actualID);
    cv::Matx44f actualTransformation = result.cbegin()->second;
    EXPECT_GT(1e-3, cv::norm(actualTransformation-expectedTransformation))
        << "\nExpected:\n" << cv::Mat(expectedTransformation)
        << "\nActual:\n" << cv::Mat(actualTransformation);
}

TEST(Estimate3dPose, Configurations) {
    auto objectTransformation = makeTransformation(135, 145, 155, 201, 401, 601);

    std::vector<int> ids = {2, 3};
    std::vector<float> sizes = {20,30};
    std::vector<cv::Matx44f> tagTransformations = {
        objectTransformation*makeTransformation(0, 0, 0, -50, -100, 0),
        objectTransformation*makeTransformation(0, 0, 0, +50, -100, 0),
    };

    chilitags::TagCornerMap tags;
    for (std::size_t i = 0; i<ids.size(); ++i) {
        tags[ids[i]] = makeTransformedCorners(tagTransformations[i], sizes[i]);
    }

    chilitags::Chilitags3D::TagPoseMap expected = {
        {    "tag_2", tagTransformations[0]},
        {"myobject3", objectTransformation },
    };

    //Test config from file
    {
        chilitags::Chilitags3D chilitags3D(CAMERA_SIZE);
        chilitags3D.setDefaultTagSize(20.f);
        if(chilitags3D.readTagConfiguration(cvtest::TS::ptr()->get_data_path() + "misc/tag_configuration_sample.yml",true)) {
            auto result = chilitags3D.estimate(tags);

            EXPECT_EQ(expected.size(), result.size());
            for (auto expectedIt = expected.cbegin(); expectedIt != expected.cend(); ++expectedIt) {
                auto resultIt = result.find(expectedIt->first);

                if (result.cend() == resultIt) {
                    ADD_FAILURE() << "Missing:" << expectedIt->first;
                } else {
                    EXPECT_GT(1e-3, cv::norm(resultIt->second - expectedIt->second))
                        << "For:" << expectedIt->first
                        << "\nExpected:\n" << cv::Mat(expectedIt->second)
                        << "\nActual:\n"   << cv::Mat(resultIt->second);

                    ++resultIt; //?
                }
            }
        }
        else{
            ADD_FAILURE()
                << "Unable to read: " << cvtest::TS::ptr()->get_data_path() + "misc/tag_configuration_sample.yml" << "\n"
                << "Did you correctly set the OPENCV_TEST_DATA_PATH environment variable?\n"
                << "CMake takes care of this if you set its TEST_DATA variable.\n"
                << "You can download the test data from\n"
                << "https://github.com/chili-epfl/chilitags-testdata";
        }
    }

    //Test config from string
    {
        chilitags::Chilitags3D chilitags3D(CAMERA_SIZE);
        chilitags3D.setDefaultTagSize(20.f);
        std::ifstream configfile(cvtest::TS::ptr()->get_data_path() + "misc/tag_configuration_sample.yml");
        std::string str((std::istreambuf_iterator<char>(configfile)), //DO NOT REMOVE EXTRA PARENTHESIS!
                        std::istreambuf_iterator<char>());
        if(chilitags3D.readTagConfiguration(str,true,true)) {
            auto result = chilitags3D.estimate(tags);

            EXPECT_EQ(expected.size(), result.size());
            for (auto expectedIt = expected.cbegin(); expectedIt != expected.cend(); ++expectedIt) {
                auto resultIt = result.find(expectedIt->first);

                if (result.cend() == resultIt) {
                    ADD_FAILURE() << "Missing:" << expectedIt->first;
                } else {
                    EXPECT_GT(1e-3, cv::norm(resultIt->second - expectedIt->second))
                        << "For:" << expectedIt->first
                        << "\nExpected:\n" << cv::Mat(expectedIt->second)
                        << "\nActual:\n"   << cv::Mat(resultIt->second);

                    ++resultIt; //?
                }
            }
        }
        else{
            ADD_FAILURE()
                << "Unable to read: " << cvtest::TS::ptr()->get_data_path() + "misc/tag_configuration_sample.yml" << "\n"
                << "Did you correctly set the OPENCV_TEST_DATA_PATH environment variable?\n"
                << "CMake takes care of this if you set its TEST_DATA variable.\n"
                << "You can download the test data from\n"
                << "https://github.com/chili-epfl/chilitags-testdata";
        }
    }
}

CV_TEST_MAIN(".")
