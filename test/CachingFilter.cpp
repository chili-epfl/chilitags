#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <CachingFilter.hpp>
#include <iostream>

TEST(CachingFilter, Cache) {
    chilitags::CachingFilter filter(1);
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

TEST(CachingFilter, ZeroPersistence) {
    chilitags::CachingFilter filter(0);

    EXPECT_EQ(0, filter({}).size());
    EXPECT_EQ(1, filter({{42,{}}}).size());
    EXPECT_EQ(0, filter({}).size());

}

TEST(CachingFilter, InvalidateOne) {
    chilitags::CachingFilter filter(3);

    EXPECT_EQ(0, filter({}).size());
    EXPECT_EQ(1, filter({{42,{}}}).size());
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(0, filter({}).size());
}

TEST(CachingFilter, InvalidateFirst) {
    chilitags::CachingFilter filter(2);

    EXPECT_EQ(0, filter({}).size());
    EXPECT_EQ(1, filter({{42,{}}}).size());
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(1, filter({{43,{}}}).size());
}

TEST(CachingFilter, ChangePersistence) {
    chilitags::CachingFilter filter(2);

    EXPECT_EQ(0, filter({}).size());
    EXPECT_EQ(1, filter({{42,{}}}).size());
    filter.setPersistence(1);
    EXPECT_EQ(1, filter({}).size());
    EXPECT_EQ(0, filter({}).size());
}

CV_TEST_MAIN(".")
