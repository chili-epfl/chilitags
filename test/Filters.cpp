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
        {7.f, 8.f},
    }}};
    const std::map<int, std::vector<cv::Point2f>> ONLY_TAG_43_1 = {{43, {
        {11.f, 12.f},
        {13.f, 14.f},
        {15.f, 16.f},
        {17.f, 18.f},
    }}};

    const std::map<std::string, cv::Matx44d> ONLY_OBJECT_42_1 = {{"42", {
         1.f,  2.f,  3.f,  4.f,
         5.f,  6.f,  7.f,  8.f,
         9.f, 10.f, 11.f, 12.f,
        13.f, 14.f, 15.f, 16.f,
    }}};
    const std::map<std::string, cv::Matx44d> ONLY_OBJECT_43_1 = {{"43", {
        101.f, 102.f, 103.f, 104.f,
        105.f, 106.f, 107.f, 108.f,
        109.f, 110.f, 111.f, 112.f,
        113.f, 114.f, 115.f, 116.f,
    }}};
}


TEST(KalmanFilter2D, Coverage) {
    FindOutdated2D findOutdated(2);
    Kalman2D filter(findOutdated);

    auto result = filter(ONLY_TAG_42_1);
    auto expected = ONLY_TAG_42_1;
    ASSERT_EQ(expected.size(), result.size());
    auto resultIt = result.cbegin();
    for (const auto &expectedElem : expected) {
        EXPECT_EQ(expectedElem.first, resultIt->first);
        EXPECT_EQ(expectedElem.second, resultIt->second)
            << "For " << resultIt->first << std::endl;
        ++resultIt;
    }

    result = filter(ONLY_TAG_42_1);
    ASSERT_EQ(expected.size(), result.size());
    resultIt = result.cbegin();
    for (const auto &expectedElem : expected) {
        EXPECT_EQ(expectedElem.first, resultIt->first);
        EXPECT_EQ(expectedElem.second, resultIt->second)
            << "For " << resultIt->first << std::endl;
        ++resultIt;
    }

    result = filter(ONLY_TAG_43_1);
    expected.insert(ONLY_TAG_43_1.cbegin(), ONLY_TAG_43_1.cend());
    ASSERT_EQ(expected.size(), result.size());
    resultIt = result.cbegin();
    for (const auto &expectedElem : expected) {
        EXPECT_EQ(expectedElem.first, resultIt->first);
        EXPECT_EQ(expectedElem.second, resultIt->second)
            << "For " << resultIt->first << std::endl;
        ++resultIt;
    }

    result = filter(EMPTY_TAG_LIST);
    ASSERT_EQ(expected.size(), result.size());
    resultIt = result.cbegin();
    for (const auto &expectedElem : expected) {
        EXPECT_EQ(expectedElem.first, resultIt->first);
        EXPECT_EQ(expectedElem.second, resultIt->second)
            << "For " << resultIt->first << std::endl;
        ++resultIt;
    }
}

TEST(KalmanFilter3D, Coverage) {
    FindOutdated3D findOutdated(2);
    Kalman3D filter(findOutdated);

    auto result = filter(ONLY_OBJECT_42_1);
    auto expected = ONLY_OBJECT_42_1;
    ASSERT_EQ(expected.size(), result.size());
    auto resultIt = result.cbegin();
    for (const auto &expectedElem : expected) {
        EXPECT_EQ(expectedElem.first, resultIt->first);
        EXPECT_EQ(expectedElem.second, resultIt->second)
            << "For " << resultIt->first << std::endl;
        ++resultIt;
    }

    result = filter(ONLY_OBJECT_42_1);
    ASSERT_EQ(expected.size(), result.size());
    resultIt = result.cbegin();
    for (const auto &expectedElem : expected) {
        EXPECT_EQ(expectedElem.first, resultIt->first);
        EXPECT_EQ(expectedElem.second, resultIt->second)
            << "For " << resultIt->first << std::endl;
        ++resultIt;
    }

    result = filter(ONLY_OBJECT_43_1);
    expected.insert(ONLY_OBJECT_43_1.cbegin(), ONLY_OBJECT_43_1.cend());
    ASSERT_EQ(expected.size(), result.size());
    resultIt = result.cbegin();
    for (const auto &expectedElem : expected) {
        EXPECT_EQ(expectedElem.first, resultIt->first);
        EXPECT_EQ(expectedElem.second, resultIt->second)
            << "For " << resultIt->first << std::endl;
        ++resultIt;
    }

    result = filter(EMPTY_OBJECT_LIST);
    ASSERT_EQ(expected.size(), result.size());
    resultIt = result.cbegin();
    for (const auto &expectedElem : expected) {
        EXPECT_EQ(expectedElem.first, resultIt->first);
        EXPECT_EQ(expectedElem.second, resultIt->second)
            << "For " << resultIt->first << std::endl;
        ++resultIt;
    }
}

TEST(KalmanFilter, Noise) {
    chilitags::FindOutdated<int> findOutdated(100);
    chilitags::KalmanFilter<int> filter(findOutdated);

    std::vector<cv::Point2f> expected = {
        {1.f, 2.f},
        {3.f, 4.f},
        {5.f, 6.f},
        {7.f, 8.f},
    };

    auto coordinates = expected;

    std::map<int, std::vector<cv::Point2f>> tags;
    std::vector<cv::Point2f> result;

    cv::RNG rng;
    float noise = .1f;
    for (int i = 0; i < 10; ++i) {
        float delta = rng.uniform(-noise,noise);
        coordinates = cv::Mat(cv::Mat(expected) + delta);
        tags = {{0, coordinates}};
        result = filter(tags)[0];
        EXPECT_GT(2*noise, cv::norm(cv::Mat(result)-cv::Mat(expected)));
    }

}

TEST(KalmanFilter, Extrapolate) {
    chilitags::FindOutdated<int> findOutdated(100);
    chilitags::KalmanFilter<int, 2> filter(findOutdated);

    std::vector<cv::Point2f> coordinates = {
        {1.f, 2.f},
        {3.f, 4.f},
        {5.f, 6.f},
        {7.f, 8.f},
    };

    std::map<int, std::vector<cv::Point2f>> tags;
    std::vector<cv::Point2f> result;

    float delta = 10.f;

    tags = {{0, coordinates}};
    result = filter(tags)[0];
    //EXPECT_GT(1e-6, cv::norm(cv::Mat(result)-cv::Mat(coordinates)));

    coordinates = cv::Mat(cv::Mat(coordinates) + delta); 

    tags = {{0, coordinates}};
    result = filter(tags)[0];
    //EXPECT_GT(1e-6, cv::norm(cv::Mat(result)-cv::Mat(coordinates)));

    coordinates = cv::Mat(cv::Mat(coordinates) + delta); 

    //tags = {};
    tags = {{0, coordinates}};
    result = filter(tags)[0];
    //EXPECT_GT(1e-6, cv::norm(cv::Mat(result)-cv::Mat(coordinates)));

    coordinates = cv::Mat(cv::Mat(coordinates) + delta); 

    //tags = {};
    tags = {{0, coordinates}};
    result = filter(tags)[0];
    //EXPECT_GT(1e-6, cv::norm(cv::Mat(result)-cv::Mat(coordinates)));
}

CV_TEST_MAIN(".")
