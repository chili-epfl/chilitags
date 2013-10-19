#include <opencv2/ts/ts.hpp>
#include <Codec.hpp>

#include "HardcodedIds.hpp"

#include <iostream>

TEST(Codec, Code) {
	chilitags::Codec tCodec(10, 16, 10, "1010101010", "10001000000100001");
	unsigned char tBits[36];

	HardcodedIds tHardcodedIds;

	for (int i = 0; i<1024; ++i) {
		tCodec.getTagEncodedId(i, tBits);
		for (int j = 0; j<36; ++j) {
			ASSERT_EQ(tHardcodedIds.id[i][j], tBits[j]);
		}
	}
}

TEST(Codec, DecodeNoError) {
	chilitags::Codec tCodec(10, 16, 10, "1010101010", "10001000000100001");
	unsigned char tBits[36];

	HardcodedIds tHardcodedIds;

	chilitags::tag_info_t *tTagInfo = nullptr;

	for (int i = 0; i<1024; ++i) {
		unsigned char tBits[36];
		for (int j = 0; j<36; ++j) {
			tBits[j] = tHardcodedIds.id[i][j];
		}
		tCodec.addTagToTrackingList(i);

		tCodec.decode(tBits, &tTagInfo);
		ASSERT_NE(nullptr, tTagInfo);
		ASSERT_EQ(i, tTagInfo->id);

	}
}

TEST(Codec, Decode1Error) {
	chilitags::Codec tCodec(10, 16, 10, "1010101010", "10001000000100001");
	unsigned char tBits[36];

	HardcodedIds tHardcodedIds;

	chilitags::tag_info_t *tTagInfo = nullptr;

	for (int i = 0; i<1024; ++i) {
		unsigned char tBits[36];
		for (int j = 0; j<36; ++j) {
			tBits[j] = tHardcodedIds.id[i][j];
		}
		tCodec.addTagToTrackingList(i);

		for (int error1 = 0; error1<36; ++error1) {
			tBits[error1] = 1-tBits[error1];

			tCodec.decode(tBits, &tTagInfo);
			ASSERT_NE(nullptr, tTagInfo);
			ASSERT_EQ(i, tTagInfo->id);

			tBits[error1] = 1-tBits[error1];
		}
	}
}

TEST(Codec, Decode2Error) {
	chilitags::Codec tCodec(10, 16, 10, "1010101010", "10001000000100001");
	unsigned char tBits[36];

	HardcodedIds tHardcodedIds;

	chilitags::tag_info_t *tTagInfo = nullptr;

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

				tCodec.decode(tBits, &tTagInfo);
				ASSERT_NE(nullptr, tTagInfo);
				ASSERT_EQ(i, tTagInfo->id);

				tBits[error2] = 1-tBits[error2];
			}

			tBits[error1] = 1-tBits[error1];
		}
	}
}
