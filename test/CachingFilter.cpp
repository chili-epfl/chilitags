#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <CachingFilter.hpp>
#include <iostream>

namespace {
    typedef chilitags::CachingFilter<int, std::vector<cv::Point2f> >
            CachingFilter2D;
    typedef chilitags::CachingFilter<std::string, cv::Matx44d>
            CachingFilter3D;
}

TEST(CachingFilter2D, Cache) {
    CachingFilter2D filter(1);
    std::vector<cv::Point2f> corners = {
        {1.0f, 5.0f},
        {2.0f, 6.0f},
        {3.0f, 7.0f},
        {4.0f, 8.0f},
    };

    EXPECT_EQ(0, filter({}).size());
    EXPECT_EQ(1, filter({{42, corners}}).size());
    auto filtered = filter({});
    ASSERT_EQ(1, filtered.size());
    auto actualId      = filtered.begin()->first;
    std::vector<cv::Point2f> actualCorners = filtered.begin()->second;
    EXPECT_EQ(42, actualId);
    for (int i : {0,1,2,3})
        EXPECT_EQ(corners[i], actualCorners[i])
            << "with i=" << i;

}

TEST(CachingFilter2D, ZeroPersistence) {
    CachingFilter2D filter(0);

    EXPECT_EQ(0, filter({}).size());
    EXPECT_EQ(1, filter({{42,{}}}).size());
    EXPECT_EQ(0, filter({}).size());

}

TEST(CachingFilter2D, InvalidateOne) {
    CachingFilter2D filter(3);

    EXPECT_EQ(0, filter({}).size());
    EXPECT_EQ(1, filter({{42,{}}}).size());
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(0, filter({}).size());
}

TEST(CachingFilter2D, InvalidateFirst) {
    CachingFilter2D filter(2);

    EXPECT_EQ(0, filter({}).size());
    EXPECT_EQ(1, filter({{42,{}}}).size());
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(1, filter({{43,{}}}).size());
}

TEST(CachingFilter2D, ChangePersistence) {
    CachingFilter2D filter(2);

    EXPECT_EQ(0, filter({}).size());
    EXPECT_EQ(1, filter({{42,{}}}).size());
    filter.setPersistence(1);
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(0, filter({}).size());
}


TEST(CachingFilter3D, Cache) {
    CachingFilter3D filter(1);
    cv::Matx44d matrix = {
        1., 5.,  9., 13.,
        2., 6., 10., 14.,
        3., 7., 11., 15.,
        4., 8., 12., 16.,
    };

    EXPECT_EQ(0, filter({}).size());
    EXPECT_EQ(1, filter({{"42", matrix}}).size());
    auto filtered = filter({});
    ASSERT_EQ(1, filtered.size());
    auto actualId      = filtered.begin()->first;
    auto actualMatrix  = filtered.begin()->second;
    EXPECT_EQ("42", actualId);
    for (int i : {0,1,2,3})
        for (int j : {0,1,2,3})
            EXPECT_EQ(matrix(i,j), actualMatrix(i,j))
                << "with (i,j)=(" << i << "," << j << ")";

}

TEST(CachingFilter3D, ZeroPersistence) {
    CachingFilter3D filter(0);

    EXPECT_EQ(0, filter({}).size());
    EXPECT_EQ(1, filter({{"42",{}}}).size());
    EXPECT_EQ(0, filter({}).size());

}

TEST(CachingFilter3D, InvalidateOne) {
    CachingFilter3D filter(3);

    EXPECT_EQ(0, filter({}).size());
    EXPECT_EQ(1, filter({{"42",{}}}).size());
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(0, filter({}).size());
}

TEST(CachingFilter3D, InvalidateFirst) {
    CachingFilter3D filter(2);

    EXPECT_EQ(0, filter({}).size());
    EXPECT_EQ(1, filter({{"42",{}}}).size());
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(1, filter({{"43",{}}}).size());
}

TEST(CachingFilter3D, ChangePersistence) {
    CachingFilter3D filter(2);

    EXPECT_EQ(0, filter({}).size());
    EXPECT_EQ(1, filter({{"42",{}}}).size());
    filter.setPersistence(1);
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(0, filter({}).size());
}

CV_TEST_MAIN(".")
