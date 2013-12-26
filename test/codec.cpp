#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <Codec.hpp>

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
    std::cout << "\n";
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

CV_TEST_MAIN(".")
