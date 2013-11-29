#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <opencv2/highgui/highgui.hpp>
#include <TagDrawer.hpp>

#include "test-metadata.hpp"

#include <DetectChilitags.hpp>
#include <Chilitag.hpp>

#include <iostream>

TEST(Integration, Minimal) {

	chilitags::DetectChilitags tDetectChilitags;

	chilitags::Chilitag tExpectedTag(0);

	chilitags::TagDrawer tDrawer;
	// Tag needs to be > 12 px wide;
	int tZoom = 3;
	cv::Mat tImage = tDrawer(tExpectedTag.GetMarkerId(), tZoom, true);

	tDetectChilitags(tImage);

	ASSERT_TRUE(tExpectedTag.isPresent());

	float tClose = tZoom*2.0f;
	float tFar   = tZoom*12.0f;
	std::vector<cv::Point2f> tExpectedCorners = {
		cv::Point2f(tClose, tClose),
		cv::Point2f(tFar, tClose),
		cv::Point2f(tFar, tFar),
		cv::Point2f(tClose, tFar),
	};

	// A pixel is a 1x1 square around its center
	cv::add(tExpectedCorners, cv::Scalar::all(-0.5), tExpectedCorners);

	auto tActualCorners = tExpectedTag.getCorners();
	for (int i: {0,1,2,3}) {
		EXPECT_GT(0.1, cv::norm(tActualCorners[i] - tExpectedCorners[i]))
			<< "with i=" << i;
	}
}

TEST(Integration, Snapshots) {
	// Initialise the data path with en empty modulename,
	// to get the data from the root of the test data path
	cvtest::TS::ptr()->init("");

	chilitags::DetectChilitags tDetectChilitags;

	int tNewFalseNegatives = 0;
	int tNewTruePositives = 0;
	int tFalseNegatives = 0;
	int tTotal = 0;

	for (const auto & tTestCase : TestMetadata::all) {
		std::string tPath = std::string(cvtest::TS::ptr()->get_data_path())+tTestCase.filename;
		cv::Mat tImage = cv::imread(tPath);

		if(tImage.data) {
			tDetectChilitags(tImage);

			for (int i = 0; i<1024; ++i) {
				// No persistence
				chilitags::Chilitag tTag(i, 0);
				if (tTestCase.isExpected(i)) {
					// We could just add the size of the list of expected tags,
					// but this way we double check that we try them all.
					++tTotal;
					if (!tTag.isPresent()) ++tFalseNegatives;

					if (!tTag.isPresent() && !tTestCase.isKnownToMiss(i)) {
						ADD_FAILURE() << "New false negative\n"
							<< "    File: " << tTestCase.filename << "\n"
							<< "     Tag: " << i << "\n";
						++tNewFalseNegatives;
					} else if (tTag.isPresent() && tTestCase.isKnownToMiss(i)) {
						std::cout << "New true positive\n"
							<< "    File: " << tTestCase.filename << "\n"
							<< "     Tag: " << i << "\n";
						++tNewTruePositives;
					}
				}
				else if (tTag.isPresent()) {
					ADD_FAILURE() << "Falsely positive detection\n"
						<< "    File: " << tTestCase.filename << "\n"
						<< "     Tag: " << i << "\n";
				}
			}
		}
		else {
			ADD_FAILURE()
				<< "Unable to read: " << tPath << "\n"
				<< "Did you correctly set the OPENCV_TEST_DATA_PATH environment variable?\n"
				<< "CMake takes care of this if you set its TEST_DATA variable.\n"
				<< "You can download the test data from\n"
				<< "https://github.com/chili-epfl/chilitags-testdata";
		}
	}

	std::cout << tFalseNegatives << "/" << tTotal << " tags were not detected.\n";
	if (tNewTruePositives > 0) {
		std::cout
			<< "You "<< (tNewFalseNegatives>0?"partially":"")
			<< "improved the detection:\n"
			<< tNewFalseNegatives << " new false negatives (bad) and "
			<< tNewTruePositives  << " new true positives (good)\n"
			<< "Please review, and if necessary, update the test case.\n";
	}
}

CV_TEST_MAIN(".")
