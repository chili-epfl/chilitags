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

cv::Point2f applyTransform(cv::Matx44d transformation, cv::Point2f point) {
    cv::Vec4d homogenousPoint = {point.x, point.y, 0.f, 1.f};

    //As assumed by Chilitags3D
    double FOCAL_LENGTH = 700.;

    static const cv::Matx44d projectionMatrix = {
        FOCAL_LENGTH ,            0 , (double) CAMERA_SIZE.width/2 , 0 , 
                   0 , FOCAL_LENGTH , (double) CAMERA_SIZE.height/2, 0 , 
                   0 ,            0 , 1                            , 0 ,
                   0 ,            0 , 1                            , 0 ,
    };
    cv::Vec4d transformedPoint = projectionMatrix*transformation*homogenousPoint;

    return cv::Point2f(
        transformedPoint[0]/transformedPoint[3],
        transformedPoint[1]/transformedPoint[3]);
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
    std::vector<cv::Point2f> corners = {
        applyTransform(expectedTransformation, cv::Point2f(0.f, 0.f   )),
        applyTransform(expectedTransformation, cv::Point2f(size, 0.f   )),
        applyTransform(expectedTransformation, cv::Point2f(size, size )),
        applyTransform(expectedTransformation, cv::Point2f(0.f, size )),
    };

    chilitags::Chilitags3D chilitags3D(CAMERA_SIZE);
    chilitags3D.setDefaultTagSize(size);

    int tagId = 0;
    auto result = chilitags3D.estimate({{tagId,corners}});
    ASSERT_EQ(1, result.size());

    std::string actualID = result.cbegin()->first;
    EXPECT_EQ(cv::format("tag_%d", tagId), actualID);
    cv::Matx44d actualTransformation = result.cbegin()->second;
    EXPECT_GT(1e-3, cv::norm(actualTransformation-expectedTransformation))
    << "\nExpected:\n" << cv::Mat(expectedTransformation)
    << "\nActual:\n" << cv::Mat(actualTransformation);
}

TEST(Estimate3dPose, Configurations) {
    auto objectTransformation = makeTransformation(135, 145, 155, 201, 401, 601);

    std::vector<int> ids = {2, 3};
    std::vector<float> sizes = {20,30};
    std::vector<cv::Matx44d> tagTransformations = {
        objectTransformation*makeTransformation(0, 0, 0, -50, -100, 0),
        objectTransformation*makeTransformation(0, 0, 0, +50, -100, 0),
    };

    std::map<int, std::vector<cv::Point2f> > tags;
    for (std::size_t i = 0; i<ids.size(); ++i) {
        tags[ids[i]] = {
            applyTransform(tagTransformations[i], cv::Point2f(0.f, 0.f      )),
            applyTransform(tagTransformations[i], cv::Point2f(sizes[i], 0.f      )),
            applyTransform(tagTransformations[i], cv::Point2f(sizes[i], sizes[i])),
            applyTransform(tagTransformations[i], cv::Point2f(0.f, sizes[i])),
        };
    }

    chilitags::Chilitags3D chilitags3D(CAMERA_SIZE);
    chilitags3D.setDefaultTagSize(20.f);
    chilitags3D.readTagConfiguration(
        cvtest::TS::ptr()->get_data_path()
        +"misc/tag_configuration_sample.yml");

    auto result = chilitags3D.estimate(tags);
    EXPECT_EQ(2, result.size());


    std::map<std::string, cv::Matx44d> expected = {
        {    "tag_2", tagTransformations[0]},
        {"myobject3", objectTransformation },
    };

    EXPECT_EQ(expected.size(), result.size());
    for (auto expectedIt = expected.cbegin();
         expectedIt != expected.cend();
         ++expectedIt) {
        auto resultIt = result.find(expectedIt->first);

        if (result.cend() == resultIt) {
            ADD_FAILURE() << "Missing:" << expectedIt->first;
        } else {
            EXPECT_GT(1e-3, cv::norm(resultIt->second - expectedIt->second))
                << "For:" << expectedIt->first
                << "\nExpected:\n" << cv::Mat(expectedIt->second)
                << "\nActual:\n"   << cv::Mat(resultIt->second);

            ++resultIt;
        }
    }
}

CV_TEST_MAIN(".")
