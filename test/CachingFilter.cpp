#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <PersistenceManager.hpp>
#include <iostream>

namespace {
    typedef chilitags::PersistenceManager<int>
            PersistenceManager2D;

    typedef chilitags::PersistenceManager<std::string>
            PersistenceManager3D;

    const std::map<int, std::vector<cv::Point2f>> EMPTY_TAG_LIST;
    const std::map<int, std::vector<cv::Point2f>> ONLY_TAG_42 = {{42, {}}};
    const std::map<int, std::vector<cv::Point2f>> ONLY_TAG_43 = {{43, {}}};

    const std::map<std::string, cv::Matx44d> EMPTY_OBJECT_LIST;
    const std::map<std::string, cv::Matx44d> ONLY_OBJECT_42 = {{"42", {}}};
    const std::map<std::string, cv::Matx44d> ONLY_OBJECT_43 = {{"43", {}}};
}

TEST(PersistenceManager2D, ZeroPersistence) {
    PersistenceManager2D filter(0);

    EXPECT_EQ(0, filter(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, filter(ONLY_TAG_42).size());
    EXPECT_EQ(1, filter(EMPTY_TAG_LIST).size());
}

TEST(PersistenceManager2D, InvalidateOne) {
    PersistenceManager2D filter(3);

    EXPECT_EQ(0, filter(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, filter(ONLY_TAG_42).size());
    EXPECT_EQ(0, filter(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, filter(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, filter(EMPTY_TAG_LIST).size());
    EXPECT_EQ(1, filter(EMPTY_TAG_LIST).size());
}

TEST(PersistenceManager2D, InvalidateFirst) {
    PersistenceManager2D filter(2);

    EXPECT_EQ(0, filter(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, filter(ONLY_TAG_42).size());
    EXPECT_EQ(0, filter(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, filter(EMPTY_TAG_LIST).size());
    EXPECT_EQ(1, filter(ONLY_TAG_43).size());
}

TEST(PersistenceManager2D, ChangePersistence) {
    PersistenceManager2D filter(2);

    EXPECT_EQ(0, filter(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, filter(ONLY_TAG_42).size());
    filter.setPersistence(1);
    EXPECT_EQ(0, filter(EMPTY_TAG_LIST).size());
    EXPECT_EQ(1, filter(EMPTY_TAG_LIST).size());
}

TEST(PersistenceManager3D, ZeroPersistence) {
    PersistenceManager3D filter(0);

    EXPECT_EQ(0, filter(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(0, filter(ONLY_OBJECT_42).size());
    EXPECT_EQ(1, filter(EMPTY_OBJECT_LIST).size());

}

TEST(PersistenceManager3D, InvalidateOne) {
    PersistenceManager3D filter(3);

    EXPECT_EQ(0, filter(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(0, filter(ONLY_OBJECT_42).size());
    EXPECT_EQ(0, filter(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(0, filter(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(0, filter(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(1, filter(EMPTY_OBJECT_LIST).size());
}

TEST(PersistenceManager3D, InvalidateFirst) {
    PersistenceManager3D filter(2);

    EXPECT_EQ(0, filter(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(0, filter(ONLY_OBJECT_42).size());
    EXPECT_EQ(0, filter(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(0, filter(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(1, filter(ONLY_OBJECT_43).size());
}

TEST(PersistenceManager3D, ChangePersistence) {
    PersistenceManager3D filter(2);

    EXPECT_EQ(0, filter(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(0, filter(ONLY_OBJECT_42).size());
    filter.setPersistence(1);
    EXPECT_EQ(0, filter(EMPTY_OBJECT_LIST).size());
    EXPECT_EQ(1, filter(EMPTY_OBJECT_LIST).size());
}

CV_TEST_MAIN(".")
