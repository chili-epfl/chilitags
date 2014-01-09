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

CV_TEST_MAIN(".")
