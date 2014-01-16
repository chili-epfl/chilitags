#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <Filters.hpp>
#include <iostream>

namespace {
    typedef chilitags::FindOutdated<int>
            FindOutdated2D;

    typedef chilitags::FindOutdated<std::string>
            FindOutdated3D;

    const std::map<int, std::vector<cv::Point2f>> EMPTY_TAG_LIST;
    const std::map<int, std::vector<cv::Point2f>> ONLY_TAG_42 = {{42, {}}};
    const std::map<int, std::vector<cv::Point2f>> ONLY_TAG_43 = {{43, {}}};

    const std::map<std::string, cv::Matx44d> EMPTY_OBJECT_LIST;
    const std::map<std::string, cv::Matx44d> ONLY_OBJECT_42 = {{"42", {}}};
    const std::map<std::string, cv::Matx44d> ONLY_OBJECT_43 = {{"43", {}}};
}

TEST(FindOutdated2D, ZeroPersistence) {
    FindOutdated2D findOutdated(0);

    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, findOutdated(ONLY_TAG_42).size());
    EXPECT_EQ(1, findOutdated(EMPTY_TAG_LIST).size());
}

TEST(FindOutdated2D, InvalidateOne) {
    FindOutdated2D findOutdated(3);

    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, findOutdated(ONLY_TAG_42).size());
    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(1, findOutdated(EMPTY_TAG_LIST).size());
}

TEST(FindOutdated2D, InvalidateFirst) {
    FindOutdated2D findOutdated(2);

    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, findOutdated(ONLY_TAG_42).size());
    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(1, findOutdated(ONLY_TAG_43).size());
}

TEST(FindOutdated2D, ChangePersistence) {
    FindOutdated2D findOutdated(2);

    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, findOutdated(ONLY_TAG_42).size());
    findOutdated.setPersistence(1);
    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(1, findOutdated(EMPTY_TAG_LIST).size());
}

TEST(FindOutdated3D, ZeroPersistence) {
    FindOutdated3D findOutdated(0);

    EXPECT_EQ(0, findOutdated(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(0, findOutdated(ONLY_OBJECT_42).size());
    EXPECT_EQ(1, findOutdated(EMPTY_OBJECT_LIST).size());

}

TEST(FindOutdated3D, InvalidateOne) {
    FindOutdated3D findOutdated(3);

    EXPECT_EQ(0, findOutdated(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(0, findOutdated(ONLY_OBJECT_42).size());
    EXPECT_EQ(0, findOutdated(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(0, findOutdated(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(0, findOutdated(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(1, findOutdated(EMPTY_OBJECT_LIST).size());
}

TEST(FindOutdated3D, InvalidateFirst) {
    FindOutdated3D findOutdated(2);

    EXPECT_EQ(0, findOutdated(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(0, findOutdated(ONLY_OBJECT_42).size());
    EXPECT_EQ(0, findOutdated(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(0, findOutdated(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(1, findOutdated(ONLY_OBJECT_43).size());
}

TEST(FindOutdated3D, ChangePersistence) {
    FindOutdated3D findOutdated(2);

    EXPECT_EQ(0, findOutdated(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(0, findOutdated(ONLY_OBJECT_42).size());
    findOutdated.setPersistence(1);
    EXPECT_EQ(0, findOutdated(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(1, findOutdated(EMPTY_OBJECT_LIST).size());
}

namespace {
    typedef chilitags::KalmanFilter<int>
            Kalman2D;

    typedef chilitags::KalmanFilter<std::string>
            Kalman3D;

    const std::map<int, std::vector<cv::Point2f>> ONLY_TAG_42_1 = {{42, {
        {1.f, 2.f},
        {3.f, 4.f},
        {5.f, 6.f},
        {6.f, 8.f},
    }}};

    const std::map<std::string, cv::Matx44d> ONLY_OBJECT_42_1 = {{"42", {
         1.f,  2.f,  3.f,  4.f,
         5.f,  6.f,  7.f,  8.f,
         9.f, 10.f, 11.f, 12.f,
        13.f, 14.f, 15.f, 16.f,
    }}};
}


TEST(KalmanFilter2D, ConstantPosition) {
    FindOutdated2D findOutdated(2);
    Kalman2D filter(findOutdated);
    
    auto result = filter(ONLY_TAG_42_1);
    const auto &expected = ONLY_TAG_42_1;
    ASSERT_EQ(expected.size(), result.size());
    auto resultIt = result.cbegin();
    for (const auto &expectedElem : expected) {
        EXPECT_EQ(expectedElem.first, resultIt->first);
        EXPECT_EQ(expectedElem.second, resultIt->second);
        ++resultIt;
    }

    filter(ONLY_TAG_42_1);
    ASSERT_EQ(expected.size(), result.size());
    resultIt = result.cbegin();
    for (const auto &expectedElem : expected) {
        EXPECT_EQ(expectedElem.first, resultIt->first);
        EXPECT_EQ(expectedElem.second, resultIt->second);
        ++resultIt;
    }

    filter(EMPTY_TAG_LIST);
    ASSERT_EQ(expected.size(), result.size());
    resultIt = result.cbegin();
    for (const auto &expectedElem : expected) {
        EXPECT_EQ(expectedElem.first, resultIt->first);
        EXPECT_EQ(expectedElem.second, resultIt->second);
        ++resultIt;
    }
}

TEST(KalmanFilter3D, ConstantPosition) {
    FindOutdated3D findOutdated(2);
    Kalman3D filter(findOutdated);
    
    const auto result = filter(ONLY_OBJECT_42_1);
    const auto &expected = ONLY_OBJECT_42_1;
    ASSERT_EQ(expected.size(), result.size());
    auto resultIt = result.cbegin();
    for (const auto &expectedElem : expected) {
        EXPECT_EQ(expectedElem.first, resultIt->first);
        EXPECT_EQ(expectedElem.second, resultIt->second);
        ++resultIt;
    }

    filter(ONLY_OBJECT_42_1);
    ASSERT_EQ(expected.size(), result.size());
    resultIt = result.cbegin();
    for (const auto &expectedElem : expected) {
        EXPECT_EQ(expectedElem.first, resultIt->first);
        EXPECT_EQ(expectedElem.second, resultIt->second);
        ++resultIt;
    }
    
    filter(EMPTY_OBJECT_LIST);
    ASSERT_EQ(expected.size(), result.size());
    resultIt = result.cbegin();
    for (const auto &expectedElem : expected) {
        EXPECT_EQ(expectedElem.first, resultIt->first);
        EXPECT_EQ(expectedElem.second, resultIt->second);
        ++resultIt;
    }
}

CV_TEST_MAIN(".")
