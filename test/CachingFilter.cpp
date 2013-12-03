#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <CachingFilter.hpp>
#include <iostream>

TEST(CachingFilter, Cache) {
	chilitags::CachingFilter tFilter(1);
	std::vector<cv::Point2f> tCorners = {
		{1.0f, 5.0f},
		{2.0f, 6.0f},
		{3.0f, 7.0f},
		{4.0f, 8.0f},
	};

	EXPECT_EQ(0, tFilter({}).size());
	EXPECT_EQ(1, tFilter({{42, tCorners}}).size());
	auto tFiltered = tFilter({});
	ASSERT_EQ(1, tFiltered.size());
	auto tActualId      = tFiltered.begin()->first;
	std::vector<cv::Point2f> tActualCorners = tFiltered.begin()->second;
	EXPECT_EQ(42, tActualId);
	for (int i : {0,1,2,3})
		EXPECT_EQ(tCorners[i], tActualCorners[i])
			<< "with i=" << i;

}

TEST(CachingFilter, ZeroPersistence) {
	chilitags::CachingFilter tFilter(0);

	EXPECT_EQ(0, tFilter({}).size());
	EXPECT_EQ(1, tFilter({{42,{}}}).size());
	EXPECT_EQ(0, tFilter({}).size());

}

TEST(CachingFilter, InvalidateOne) {
	chilitags::CachingFilter tFilter(3);

	EXPECT_EQ(0, tFilter({}).size());
	EXPECT_EQ(1, tFilter({{42,{}}}).size());
	EXPECT_EQ(1, tFilter({}).size());
	EXPECT_EQ(1, tFilter({}).size());
	EXPECT_EQ(1, tFilter({}).size());
	EXPECT_EQ(0, tFilter({}).size());
}

TEST(CachingFilter, InvalidateFirst) {
	chilitags::CachingFilter tFilter(2);

	EXPECT_EQ(0, tFilter({}).size());
	EXPECT_EQ(1, tFilter({{42,{}}}).size());
	EXPECT_EQ(1, tFilter({}).size());
	EXPECT_EQ(1, tFilter({}).size());
	EXPECT_EQ(1, tFilter({{43,{}}}).size());
}

CV_TEST_MAIN(".")
