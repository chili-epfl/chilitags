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

#include <Filter.hpp>
#include <chilitags.hpp>

#include <iostream>

namespace {
const chilitags::TagCornerMap EMPTY_TAG_LIST;
const chilitags::TagCornerMap ONLY_TAG_42 = {{42, {}}};
const chilitags::TagCornerMap ONLY_TAG_43 = {{43, {}}};
}

TEST(FindOutdated, ZeroPersistence) {
    chilitags::FindOutdated findOutdated(0);

    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, findOutdated(ONLY_TAG_42).size());
    EXPECT_EQ(1, findOutdated(EMPTY_TAG_LIST).size());
}

TEST(FindOutdated, InvalidateOne) {
    chilitags::FindOutdated findOutdated(3);

    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, findOutdated(ONLY_TAG_42).size());
    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(1, findOutdated(EMPTY_TAG_LIST).size());
}

TEST(FindOutdated, InvalidateFirst) {
    chilitags::FindOutdated findOutdated(2);

    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, findOutdated(ONLY_TAG_42).size());
    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(1, findOutdated(ONLY_TAG_43).size());
}

TEST(FindOutdated, ChangePersistence) {
    chilitags::FindOutdated findOutdated(2);

    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(0, findOutdated(ONLY_TAG_42).size());
    findOutdated.setPersistence(1);
    EXPECT_EQ(0, findOutdated(EMPTY_TAG_LIST).size());
    EXPECT_EQ(1, findOutdated(EMPTY_TAG_LIST).size());
}

TEST(Filter, ZeroGain) {
    chilitags::Filter filter(0, 0.0f);
    chilitags::Quad coordinates {
        1.0f,2.0f,
        3.0f,4.0f,
        5.0f,6.0f,
        7.0f,8.0f,
    };
    chilitags::Quad expected;
    chilitags::TagCornerMap tags;
    chilitags::TagCornerMap results;

    tags = {{0, coordinates}};
    results = filter(tags);
    expected = coordinates;
    EXPECT_EQ(results.size(), tags.size());
    EXPECT_EQ(0.0f, cv::norm(cv::Mat(expected) - cv::Mat(results[0])));

    coordinates = cv::Mat(cv::Mat(coordinates) + 9.0f);
    tags = {{0, coordinates}};
    results = filter(tags);
    expected = coordinates;
    EXPECT_EQ(results.size(), tags.size());
    EXPECT_EQ(0.0f, cv::norm(cv::Mat(expected) - cv::Mat(results[0])));
}

TEST(Filter, NonZeroGain) {
    chilitags::Filter filter(0, 0.1f);
    chilitags::Quad coordinates {
        1.0f,2.0f,
        3.0f,4.0f,
        5.0f,6.0f,
        7.0f,8.0f,
    };
    chilitags::Quad expected;
    chilitags::TagCornerMap tags;
    chilitags::TagCornerMap results;

    tags = {{0, coordinates}};
    results = filter(tags);
    expected = coordinates;
    EXPECT_EQ(results.size(), tags.size());
    EXPECT_EQ(0.0f, cv::norm(cv::Mat(expected) - cv::Mat(results[0])));

    chilitags::Quad coordinates2 = cv::Mat(cv::Mat(coordinates) + 9.0f);
    tags = {{0, coordinates2}};
    results = filter(tags);
    expected = cv::Mat(0.1f*cv::Mat(coordinates)+0.9f*cv::Mat(coordinates2));
    EXPECT_EQ(results.size(), tags.size());
    EXPECT_EQ(0.0f, cv::norm(cv::Mat(expected) - cv::Mat(results[0])));
}

CV_TEST_MAIN(".")
