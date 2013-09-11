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
	chilitags::Codec tCodec;

	HardcodedIds tHardcodedIds;

	for (int i = 0; i<1024; ++i) {
		unsigned char tBits[36];
		tCodec.getTagEncodedId(i, tBits);
		for (int j = 0; j<36; ++j) {
			ASSERT_EQ(tHardcodedIds.id[i][j], tBits[j]);
		}
	}
}

TEST(Codec, DecodeNoError) {
	chilitags::Codec tCodec;

	HardcodedIds tHardcodedIds;

	for (int i = 0; i<1024; ++i) {
		unsigned char tBits[36];
		for (int j = 0; j<36; ++j) {
			tBits[j] = tHardcodedIds.id[i][j];
		}
		tCodec.addTagToTrackingList(i);

		int tDecodedId;
		ASSERT_TRUE(tCodec.decode(tBits, tDecodedId));
		ASSERT_EQ(i, tDecodedId);
	}
}

TEST(Codec, Decode1Error) {
	chilitags::Codec tCodec;

	HardcodedIds tHardcodedIds;

	for (int i = 0; i<1024; ++i) {
		unsigned char tBits[36];
		for (int j = 0; j<36; ++j) {
			tBits[j] = tHardcodedIds.id[i][j];
		}
		tCodec.addTagToTrackingList(i);

		for (int error1 = 0; error1<36; ++error1) {
			tBits[error1] = 1-tBits[error1];

			int tDecodedId;
			ASSERT_TRUE(tCodec.decode(tBits, tDecodedId));
			ASSERT_EQ(i, tDecodedId);

			tBits[error1] = 1-tBits[error1];
		}
	}
}

TEST(Codec, Decode2Errors) {
	chilitags::Codec tCodec;

	HardcodedIds tHardcodedIds;

	for (int i = 0; i<1024; ++i) {
		unsigned char tBits[36];
		for (int j = 0; j<36; ++j) {
			tBits[j] = tHardcodedIds.id[i][j];
		}
		tCodec.addTagToTrackingList(i);

		for (int error1 = 0; error1<36; ++error1) {
			tBits[error1] = 1-tBits[error1];

			for (int error2 = error1+1; error2<36; ++error2) {
				tBits[error2] = 1-tBits[error2];

				int tDecodedId;
				ASSERT_TRUE(tCodec.decode(tBits, tDecodedId));
				ASSERT_EQ(i, tDecodedId);

				tBits[error2] = 1-tBits[error2];
			}

			tBits[error1] = 1-tBits[error1];
		}
	}
}

CV_TEST_MAIN(".")
