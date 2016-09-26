/*******************************************************************************
*   Copyright 2013-2014 EPFL                                                   *
*   Copyright 2013-2014 Quentin Bonnard                                        *
*                                                                              *
*   This file is part of chilitags.                                            *
*                                                                              *
*   Chilitags is free software: you can redistribute it and/or modify          *
*   it under the terms of the Lesser GNU General Public License as             *
*   published by the Free Software Foundation, either version 3 of the         *
*   License, or (at your option) any later version.                            *
*                                                                              *
*   Chilitags is distributed in the hope that it will be useful,               *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of             *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
*   GNU Lesser General Public License for more details.                        *
*                                                                              *
*   You should have received a copy of the GNU Lesser General Public License   *
*   along with Chilitags.  If not, see <http://www.gnu.org/licenses/>.         *
*******************************************************************************/

#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <chilitags.hpp>

#include "HardcodedIds.hpp"

namespace {
cv::Vec3b WHITE(255,255,255);
cv::Vec3b BLACK(0,0,0);
}

TEST(Drawer, Defaults) {
    chilitags::Chilitags chilitags;
    cv::Mat image = chilitags.draw(0);
    ASSERT_EQ(CV_8UC3, image.type());
    ASSERT_EQ(10,image.cols);
    ASSERT_EQ(10,image.rows);
}

TEST(Drawer, DrawCode) {
    HardcodedIds hardcodedIds;
    chilitags::Chilitags chilitags;

    for (int t = 0; t<1024; ++t) {
        cv::Mat image = chilitags.draw(t);
        ASSERT_EQ(CV_8UC3, image.type());
        ASSERT_EQ(10,image.cols);
        ASSERT_EQ(10,image.rows);

        int contentStart = 2;
        for (int y = 0; y<image.rows; ++y) {
            for (int x = 0; x<image.cols; ++x) {

                if (x < contentStart || x >= image.cols-contentStart
                    || y < contentStart || y >= image.rows-contentStart) {
                    ASSERT_EQ(BLACK, image.at<cv::Vec3b>(y,x));
                }
            }
        }

        for (int i = 0; i<6; ++i) {
            for (int j = 0; j<6; ++j) {
                ASSERT_EQ(
                    hardcodedIds.id[t][6*i+j] ? WHITE : BLACK,
                    image.at<cv::Vec3b>(2+i,2+j));
            }
        }
    }
}

TEST(Drawer, WithMargin) {
    HardcodedIds hardcodedIds;
    chilitags::Chilitags chilitags;

    for (int t = 0; t<1024; ++t) {
        cv::Mat image = chilitags.draw(t,1,true);
        ASSERT_EQ(CV_8UC3, image.type());
        ASSERT_EQ(14,image.cols);
        ASSERT_EQ(14,image.rows);

        for (int i = 0; i<6; ++i) {
            for (int j = 0; j<6; ++j) {
                ASSERT_EQ(
                    hardcodedIds.id[t][6*i+j] ? WHITE : BLACK,
                    image.at<cv::Vec3b>(4+i,4+j));
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
        ASSERT_EQ(CV_8UC3, image.type());
        ASSERT_EQ(100,image.cols);
        ASSERT_EQ(100,image.rows);

        int contentStart = zoom*2;
        for (int y = 0; y<image.rows; ++y) {
            for (int x = 0; x<image.cols; ++x) {

                if (x < contentStart || x >= image.cols-contentStart
                    || y < contentStart || y >= image.rows-contentStart) {
                    ASSERT_EQ(BLACK, image.at<cv::Vec3b>(y,x));
                }
            }
        }

        for (int i = 0; i<6; ++i) {
            for (int j = 0; j<6; ++j) {
                for (int y = zoom*(2+i); y<zoom*(2+i+1); ++y) {
                    for (int x = zoom*(2+j); x<zoom*(2+j+1); ++x) {
                        ASSERT_EQ(
                            hardcodedIds.id[t][6*i+j] ? WHITE : BLACK,
                            image.at<cv::Vec3b>(y,x));
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
        ASSERT_EQ(CV_8UC3, image.type());
        ASSERT_EQ(140,image.cols);
        ASSERT_EQ(140,image.rows);
        for (int i = 0; i<6; ++i) {
            for (int j = 0; j<6; ++j) {
                for (int y = zoom*(4+i); y<zoom*(4+i+1); ++y) {
                    for (int x = zoom*(4+j); x<zoom*(4+j+1); ++x) {
                        ASSERT_EQ(
                            hardcodedIds.id[t][6*i+j] ? WHITE : BLACK,
                            image.at<cv::Vec3b>(y,x));
                    }
                }
            }
        }
    }
}

CV_TEST_MAIN(".")
