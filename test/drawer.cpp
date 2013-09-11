#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <TagDrawer.hpp>

#include "HardcodedIds.hpp"

TEST(Drawer, Defaults) {
	chilitags::TagDrawer tDrawer;
	cv::Mat tImage = tDrawer(0);
	ASSERT_EQ(CV_8U, tImage.type());
	ASSERT_EQ(10,tImage.cols);
	ASSERT_EQ(10,tImage.rows);
}

TEST(Drawer, DrawCode) {
	HardcodedIds tHardcodedIds;
	chilitags::TagDrawer tDrawer;

	for (int t = 0; t<1024; ++t) {
		cv::Mat tImage = tDrawer(t);
		ASSERT_EQ(CV_8U, tImage.type());
		ASSERT_EQ(10,tImage.cols);
		ASSERT_EQ(10,tImage.rows);

		int tContentStart = 2;
		for (int y = 0; y<tImage.rows; ++y) {
			for (int x = 0; x<tImage.cols; ++x) {
				
				if (x < tContentStart || x >= tImage.cols-tContentStart
					|| y < tContentStart || y >= tImage.rows-tContentStart) {
					ASSERT_EQ(0, tImage.at<unsigned char>(y,x));
				}
			}
		}

		for (int i = 0; i<6; ++i) {
			for (int j = 0; j<6; ++j) {
				ASSERT_EQ(
					tHardcodedIds.id[t][6*i+j]*255,
					tImage.at<unsigned char>(2+i,2+j));
			}
		}
	}
}

TEST(Drawer, WithMargin) {
	HardcodedIds tHardcodedIds;
	chilitags::TagDrawer tDrawer;

	for (int t = 0; t<1024; ++t) {
		cv::Mat tImage = tDrawer(t,1,true);
		ASSERT_EQ(CV_8U, tImage.type());
		ASSERT_EQ(14,tImage.cols);
		ASSERT_EQ(14,tImage.rows);

		for (int i = 0; i<6; ++i) {
			for (int j = 0; j<6; ++j) {
				ASSERT_EQ(
					tHardcodedIds.id[t][6*i+j]*255,
					tImage.at<unsigned char>(4+i,4+j));
			}
		}
	}
}

TEST(Drawer, Zoom) {
	HardcodedIds tHardcodedIds;
	chilitags::TagDrawer tDrawer;

	int tZoom = 10;
	for (int t = 0; t<1024; ++t) {
		cv::Mat tImage = tDrawer(t, tZoom);
		ASSERT_EQ(CV_8U, tImage.type());
		ASSERT_EQ(100,tImage.cols);
		ASSERT_EQ(100,tImage.rows);

		int tContentStart = tZoom*2;
		for (int y = 0; y<tImage.rows; ++y) {
			for (int x = 0; x<tImage.cols; ++x) {
				
				if (x < tContentStart || x >= tImage.cols-tContentStart
					|| y < tContentStart || y >= tImage.rows-tContentStart) {
					ASSERT_EQ(0, tImage.at<unsigned char>(y,x));
				}
			}
		}

		for (int i = 0; i<6; ++i) {
			for (int j = 0; j<6; ++j) {
				for (int y = tZoom*(2+i); y<tZoom*(2+i+1); ++y) {
					for (int x = tZoom*(2+j); x<tZoom*(2+j+1); ++x) {
						ASSERT_EQ(
							tHardcodedIds.id[t][6*i+j]*255,
							tImage.at<unsigned char>(y,x));
					}
				}
			}
		}
	}
}

TEST(Drawer, ZoomWithMargin) {
	HardcodedIds tHardcodedIds;
	chilitags::TagDrawer tDrawer;

	int tZoom = 10;
	for (int t = 0; t<1024; ++t) {
		cv::Mat tImage = tDrawer(t, tZoom, true);
		ASSERT_EQ(CV_8U, tImage.type());
		ASSERT_EQ(140,tImage.cols);
		ASSERT_EQ(140,tImage.rows);
		for (int i = 0; i<6; ++i) {
			for (int j = 0; j<6; ++j) {
				for (int y = tZoom*(4+i); y<tZoom*(4+i+1); ++y) {
					for (int x = tZoom*(4+j); x<tZoom*(4+j+1); ++x) {
						ASSERT_EQ(
							tHardcodedIds.id[t][6*i+j]*255,
							tImage.at<unsigned char>(y,x));
					}
				}
			}
		}
	}
}

CV_TEST_MAIN(".")
