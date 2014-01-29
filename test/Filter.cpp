#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <Filter.hpp>
#include <iostream>

namespace {
    typedef chilitags::FindOutdated<int>
            FindOutdated2D;

    typedef chilitags::FindOutdated<std::string>
            FindOutdated3D;

    typedef cv::Matx<float, 4, 2> Quad;

    const std::map<int, Quad> EMPTY_TAG_LIST;
    const std::map<int, Quad> ONLY_TAG_42 = {{42, {}}};
    const std::map<int, Quad> ONLY_TAG_43 = {{43, {}}};

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

TEST(Filter, ZeroGain) {
    chilitags::Filter<int, Quad> filter(0, 0.);
    Quad coordinates {
        1.,2.,
        3.,4.,
        5.,6.,
        7.,8.,
    };
    Quad expected;
    std::map<int, Quad> tags;
    std::map<int, Quad> results;
    
    tags = {{0, coordinates}};
    results = filter(tags);
    expected = coordinates;
    EXPECT_EQ(results.size(), tags.size());
    EXPECT_EQ(0., cv::norm(cv::Mat(expected) - cv::Mat(results[0])));
    
    coordinates = cv::Mat(cv::Mat(coordinates) + 9.);
    tags = {{0, coordinates}};
    results = filter(tags);
    expected = coordinates;
    EXPECT_EQ(results.size(), tags.size());
    EXPECT_EQ(0., cv::norm(cv::Mat(expected) - cv::Mat(results[0])));
}

TEST(Filter, NonZeroGain) {
    chilitags::Filter<int, Quad> filter(0, 0.1);
    Quad coordinates {
        1.,2.,
        3.,4.,
        5.,6.,
        7.,8.,
    };
    Quad expected;
    std::map<int, Quad> tags;
    std::map<int, Quad> results;
    
    tags = {{0, coordinates}};
    results = filter(tags);
    expected = coordinates;
    EXPECT_EQ(results.size(), tags.size());
    EXPECT_EQ(0., cv::norm(cv::Mat(expected) - cv::Mat(results[0])));
    
    Quad coordinates2 = cv::Mat(cv::Mat(coordinates) + 9.);
    tags = {{0, coordinates2}};
    results = filter(tags);
    expected = cv::Mat(0.1*cv::Mat(coordinates)+.9*cv::Mat(coordinates2));
    EXPECT_EQ(results.size(), tags.size());
    EXPECT_EQ(0., cv::norm(cv::Mat(expected) - cv::Mat(results[0])));
}

CV_TEST_MAIN(".")
