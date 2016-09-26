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

TEST(Integration, Minimal) {
    int expectedId = 42;
    chilitags::Chilitags chilitags;
    // Tag needs to be > 12 px wide;
    int zoom = 3;
    cv::Mat image = chilitags.draw(expectedId, zoom, true);

    auto tags = chilitags.find(image);

    ASSERT_EQ(1, tags.size());

    auto actualId = tags.cbegin()->first;
    EXPECT_EQ(expectedId, actualId);

    float close = zoom*2.0f;
    float far   = zoom*12.0f;
    chilitags::Quad expectedCorners = {
        close, close,
        far, close,
        far, far,
        close, far
    };

    // A pixel is a 1x1 square around its center
    cv::add(expectedCorners, cv::Scalar::all(-0.5f), expectedCorners);

    auto actualCorners = tags.cbegin()->second;
    for (int i : {0,1,2,3}) {
        EXPECT_GT(0.1f, cv::norm(actualCorners.row(i) - expectedCorners.row(i)))
            << "with i=" << i;
    }
}

TEST(Integration, MaxWidth) {
    int expectedId = 42;
    chilitags::Chilitags chilitags;
    int zoom = 300;
    cv::Mat image = chilitags.draw(expectedId, zoom, true);
    int tagSize = 2+10+2;
    ASSERT_EQ(image.cols, tagSize*zoom);

    //"burn" the input (initialiaze buffers, read from disk...)
    chilitags.find(image);

    //without setMaxInputWidth
    auto startCount = cv::getTickCount();
    auto tagsWithout = chilitags.find(image);
    auto endCount = cv::getTickCount();
    auto timeWithout = endCount - startCount;

    //with setMaxInputWidth
    int smallerImageSize = image.cols/10;
    chilitags.setMaxInputWidth(smallerImageSize);
    startCount = cv::getTickCount();
    auto tagsWith = chilitags.find(image);
    endCount = cv::getTickCount();
    auto timeWith = endCount - startCount;

    EXPECT_GT(timeWithout, timeWith);

    ASSERT_EQ(tagsWith.size(), tagsWithout.size());

    for (auto withIt = tagsWith.cbegin(), withoutIt = tagsWithout.cbegin();
         withIt != tagsWith.cend();
         ++withIt, ++withoutIt) {

        EXPECT_EQ(withIt->first, withoutIt->first);

        for (int i : {0,1,2,3}) {
            EXPECT_GT(3.0f, cv::norm(
                          withIt->second.row(i) -
                          withoutIt->second.row(i)))
                << "with i=" << i
                << ",\n withIt[i]=" << withIt->second.row(i)
                << ",\n withoutIt[i]=" << withoutIt->second.row(i);
        }
    }
}

CV_TEST_MAIN(".")
