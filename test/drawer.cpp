#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <chilitags.hpp>

#include "HardcodedIds.hpp"

TEST(Drawer, Defaults) {
    chilitags::Chilitags chilitags;
    cv::Mat image = chilitags.draw(0);
    ASSERT_EQ(CV_8U, image.type());
    ASSERT_EQ(10,image.cols);
    ASSERT_EQ(10,image.rows);
}

TEST(Drawer, DrawCode) {
    HardcodedIds hardcodedIds;
    chilitags::Chilitags chilitags;

    for (int t = 0; t<1024; ++t) {
        cv::Mat image = chilitags.draw(t);
        ASSERT_EQ(CV_8U, image.type());
        ASSERT_EQ(10,image.cols);
        ASSERT_EQ(10,image.rows);

        int contentStart = 2;
        for (int y = 0; y<image.rows; ++y) {
            for (int x = 0; x<image.cols; ++x) {

                if (x < contentStart || x >= image.cols-contentStart
                    || y < contentStart || y >= image.rows-contentStart) {
                    ASSERT_EQ(0, image.at<unsigned char>(y,x));
                }
            }
        }

        for (int i = 0; i<6; ++i) {
            for (int j = 0; j<6; ++j) {
                ASSERT_EQ(
                    hardcodedIds.id[t][6*i+j]*255,
                    image.at<unsigned char>(2+i,2+j));
            }
        }
    }
}

TEST(Drawer, WithMargin) {
    HardcodedIds hardcodedIds;
    chilitags::Chilitags chilitags;

    for (int t = 0; t<1024; ++t) {
        cv::Mat image = chilitags.draw(t,1,true);
        ASSERT_EQ(CV_8U, image.type());
        ASSERT_EQ(14,image.cols);
        ASSERT_EQ(14,image.rows);

        for (int i = 0; i<6; ++i) {
            for (int j = 0; j<6; ++j) {
                ASSERT_EQ(
                    hardcodedIds.id[t][6*i+j]*255,
                    image.at<unsigned char>(4+i,4+j));
            }
        }
    }
}

TEST(Drawer, Zoom) {
    HardcodedIds hardcodedIds;
    chilitags::Chilitags chilitags;

    int zoom = 10;
    for (int t = 0; t<1024; ++t) {
        cv::Mat image = chilitags.draw(t, zoom);
        ASSERT_EQ(CV_8U, image.type());
        ASSERT_EQ(100,image.cols);
        ASSERT_EQ(100,image.rows);

        int contentStart = zoom*2;
        for (int y = 0; y<image.rows; ++y) {
            for (int x = 0; x<image.cols; ++x) {

                if (x < contentStart || x >= image.cols-contentStart
                    || y < contentStart || y >= image.rows-contentStart) {
                    ASSERT_EQ(0, image.at<unsigned char>(y,x));
                }
            }
        }

        for (int i = 0; i<6; ++i) {
            for (int j = 0; j<6; ++j) {
                for (int y = zoom*(2+i); y<zoom*(2+i+1); ++y) {
                    for (int x = zoom*(2+j); x<zoom*(2+j+1); ++x) {
                        ASSERT_EQ(
                            hardcodedIds.id[t][6*i+j]*255,
                            image.at<unsigned char>(y,x));
                    }
                }
            }
        }
    }
}

TEST(Drawer, ZoomWithMargin) {
    HardcodedIds hardcodedIds;
    chilitags::Chilitags chilitags;

    int zoom = 10;
    for (int t = 0; t<1024; ++t) {
        cv::Mat image = chilitags.draw(t, zoom, true);
        ASSERT_EQ(CV_8U, image.type());
        ASSERT_EQ(140,image.cols);
        ASSERT_EQ(140,image.rows);
        for (int i = 0; i<6; ++i) {
            for (int j = 0; j<6; ++j) {
                for (int y = zoom*(4+i); y<zoom*(4+i+1); ++y) {
                    for (int x = zoom*(4+j); x<zoom*(4+j+1); ++x) {
                        ASSERT_EQ(
                            hardcodedIds.id[t][6*i+j]*255,
                            image.at<unsigned char>(y,x));
                    }
                }
            }
        }
    }
}

CV_TEST_MAIN(".")
