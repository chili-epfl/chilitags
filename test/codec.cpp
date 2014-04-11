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

#include <Codec.hpp>
#include <chilitags.hpp>

#include "HardcodedIds.hpp"

using namespace cv;
using namespace cvtest;
using namespace std;

TEST(Codec, Code) {
    chilitags::Codec codec;

    HardcodedIds hardcodedIds;

    for (int i = 0; i<1024; ++i) {
        unsigned char bits[36];
        codec.getTagEncodedId(i, bits);
        for (int j = 0; j<36; ++j) {
            ASSERT_EQ(hardcodedIds.id[i][j], bits[j]);
        }
    }
}

TEST(Codec, DecodeNoError) {
    chilitags::Codec codec;

    HardcodedIds hardcodedIds;

    for (int i = 0; i<1024; ++i) {
        unsigned char bits[36];
        for (int j = 0; j<36; ++j) {
            bits[j] = hardcodedIds.id[i][j];
        }

        int decodedId;

        ASSERT_TRUE(codec.decode(bits, decodedId));
        ASSERT_EQ(i, decodedId);
    }
}

TEST(Codec, Decode1Error) {
    chilitags::Codec codec;

    HardcodedIds hardcodedIds;

    for (int i = 0; i<1024; ++i) {
        unsigned char bits[36];
        for (int j = 0; j<36; ++j) {
            bits[j] = hardcodedIds.id[i][j];
        }

        for (int error1 = 0; error1<36; ++error1) {
            bits[error1] = 1-bits[error1];

            int decodedId;
            ASSERT_TRUE(codec.decode(bits, decodedId));
            ASSERT_EQ(i, decodedId);

            bits[error1] = 1-bits[error1];
        }
    }
}

TEST(Codec, Decode2Errors) {
    chilitags::Codec codec;

    HardcodedIds hardcodedIds;

    for (int i = 0; i<1024; ++i) {
        unsigned char bits[36];
        for (int j = 0; j<36; ++j) {
            bits[j] = hardcodedIds.id[i][j];
        }

        for (int error1 = 0; error1<36; ++error1) {
            bits[error1] = 1-bits[error1];

            for (int error2 = error1+1; error2<36; ++error2) {
                bits[error2] = 1-bits[error2];

                int decodedId;
                ASSERT_TRUE(codec.decode(bits, decodedId));
                ASSERT_EQ(i, decodedId);

                bits[error2] = 1-bits[error2];
            }

            bits[error1] = 1-bits[error1];
        }
    }
}

TEST(Codec, InterfaceWrapper) {
    chilitags::Chilitags chilitags;
    cv::Matx<unsigned char, 6, 6> matrix = chilitags.encode(42);
    EXPECT_EQ(42, chilitags.decode(matrix));
}

CV_TEST_MAIN(".")
