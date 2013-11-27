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

	// Tag needs to be > 20 px wide;
	int tZoom = 3;

	// Tags need to be registered before detection
	// (Chilitag's constructor takes care of that)
	chilitags::Chilitag tDetectedTag(0);

	chilitags::TagDrawer tDrawer;
	cv::Mat tImage = tDrawer(tDetectedTag.GetMarkerId(), tZoom, true);

	chilitags::DetectChilitags tDetectChilitags(&tImage);
	tDetectChilitags.update();

	ASSERT_TRUE(tDetectedTag.isPresent());

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

	auto tActualCorners = tDetectedTag.getCorners();
	for (int i: {0,1,2,3}) {
		EXPECT_GT(0.1, cv::norm(tActualCorners[i] - tExpectedCorners[i]))
			<< "with i=" << i;
	}
}

TEST(Integration, Snapshots) {
	// Initialise the data path with en empty modulename,
	// to get the data from the root of the test data path
	cvtest::TS::ptr()->init("");

	cv::Mat tImage;
	chilitags::DetectChilitags tDetectChilitags(&tImage);

	// Tags need to be registered before detection
	// (Chilitag's constructor takes care of that)
	for (int i = 0; i<1024; ++i) chilitags::Chilitag tTag(i);

	int tNewFalseNegatives = 0;
	int tNewTruePositives = 0;

	for (const auto & tTestCase : TestMetadata::all) {
		std::string tPath = std::string(cvtest::TS::ptr()->get_data_path())+tTestCase.filename;
		tImage = cv::imread(tPath);

		if(tImage.data) {
			tDetectChilitags.update();

			for (int i = 0; i<1024; ++i) {
				// No persistence
				chilitags::Chilitag tTag(i, 0);
				if (tTestCase.isExpected(i)) {
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
