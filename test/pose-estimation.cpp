#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <opencv2/core/core.hpp>

#include <chilitags.hpp>

namespace {

cv::Size CAMERA_SIZE(640,480);

cv::Matx44d makeTransformation(
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
            C*E        ,        -C*F ,    D , tx,
            B*D*E+A*F  ,  -B*D*F+A*E , -B*C , ty,
            -A*D*E+B*F , A*D*F+B*E   ,  A*C , tz,
            0.f        ,         0.f ,  0.f ,  1.f,
    };
}

cv::Point2f applyTransform(cv::Matx44d pTransformation, cv::Point2f pPoint) {
    cv::Vec4d tHomogenousPoint = {pPoint.x, pPoint.y, 0.f, 1.f};

    //As assumed by Chilitags3D
    double FOCAL_LENGTH = 700.;

    static const cv::Matx44d tProjectionMatrix = {
        FOCAL_LENGTH ,            0 , (double) CAMERA_SIZE.width/2 , 0 , 
                   0 , FOCAL_LENGTH , (double) CAMERA_SIZE.height/2, 0 , 
                   0 ,            0 , 1                            , 0 ,
                   0 ,            0 , 1                            , 0 ,
    };
    cv::Vec4d tTransformedPoint = tProjectionMatrix*pTransformation*tHomogenousPoint;

    return cv::Point2f(
        tTransformedPoint[0]/tTransformedPoint[3],
        tTransformedPoint[1]/tTransformedPoint[3]);
}

}

TEST(Estimate3dPose, 2D) {
    chilitags::Chilitags3D tChilitags3D(CAMERA_SIZE);
    auto tTagImage = tChilitags3D.getChilitags().draw(42, 5, true);
    auto tTags = tChilitags3D.getChilitags().find(tTagImage);
    EXPECT_EQ(1, tTags.size());
    auto tObjects = tChilitags3D.estimate(tTags);
    EXPECT_EQ(1, tObjects.size());
}

TEST(Estimate3dPose, FreeTags) {
    auto tExpectedTransformation = makeTransformation(35,45,65,20,40,60);

    float tSize = 37;
    std::vector<cv::Point2f> tCorners = {
        applyTransform(tExpectedTransformation, cv::Point2f(0.f, 0.f   )),
        applyTransform(tExpectedTransformation, cv::Point2f(tSize, 0.f   )),
        applyTransform(tExpectedTransformation, cv::Point2f(tSize, tSize )),
        applyTransform(tExpectedTransformation, cv::Point2f(0.f, tSize )),
    };

    chilitags::Chilitags3D tChilitags3D(CAMERA_SIZE);
    tChilitags3D.setDefaultTagSize(tSize);

    int tTagId = 0;
    auto tResult = tChilitags3D.estimate({{tTagId,tCorners}});
    ASSERT_EQ(1, tResult.size());

    std::string tActualID = tResult.cbegin()->first;
    EXPECT_EQ(cv::format("tag_%d", tTagId), tActualID);
    cv::Matx44d tActualTransformation = tResult.cbegin()->second;
    EXPECT_GT(1e-3, cv::norm(tActualTransformation-tExpectedTransformation))
    << "\nExpected:\n" << cv::Mat(tExpectedTransformation)
    << "\nActual:\n" << cv::Mat(tActualTransformation);
}

TEST(Estimate3dPose, Configurations) {
    auto tObjectTransformation = makeTransformation(135, 145, 155, 201, 401, 601);

    std::vector<int> tIds = {2, 3};
    std::vector<float> tSizes = {20,30};
    std::vector<cv::Matx44d> tTagTransformations = {
        tObjectTransformation*makeTransformation(0, 0, 0, -50, -100, 0),
        tObjectTransformation*makeTransformation(0, 0, 0, +50, -100, 0),
    };

    std::map<int, std::vector<cv::Point2f> > tTags;
    for (std::size_t i = 0; i<tIds.size(); ++i) {
        tTags[tIds[i]] = {
            applyTransform(tTagTransformations[i], cv::Point2f(0.f, 0.f      )),
            applyTransform(tTagTransformations[i], cv::Point2f(tSizes[i], 0.f      )),
            applyTransform(tTagTransformations[i], cv::Point2f(tSizes[i], tSizes[i])),
            applyTransform(tTagTransformations[i], cv::Point2f(0.f, tSizes[i])),
        };
    }

    chilitags::Chilitags3D tChilitags3D(CAMERA_SIZE);
    tChilitags3D.setDefaultTagSize(20.f);
    tChilitags3D.readTagConfiguration(
        cvtest::TS::ptr()->get_data_path()
        +"misc/tag_configuration_sample.yml");

    auto tResult = tChilitags3D.estimate(tTags);
    EXPECT_EQ(2, tResult.size());


    std::map<std::string, cv::Matx44d> tExpected = {
        {    "tag_2", tTagTransformations[0]},
        {"myobject3", tObjectTransformation },
    };

    EXPECT_EQ(tExpected.size(), tResult.size());
    for (auto tExpectedIt = tExpected.cbegin();
         tExpectedIt != tExpected.cend();
         ++tExpectedIt) {
        auto tResultIt = tResult.find(tExpectedIt->first);

        if (tResult.cend() == tResultIt) {
            ADD_FAILURE() << "Missing:" << tExpectedIt->first;
        } else {
            EXPECT_GT(1e-3, cv::norm(tResultIt->second - tExpectedIt->second))
                << "For:" << tExpectedIt->first
                << "\nExpected:\n" << cv::Mat(tExpectedIt->second)
                << "\nActual:\n"   << cv::Mat(tResultIt->second);

            ++tResultIt;
        }
    }
}

CV_TEST_MAIN(".")
