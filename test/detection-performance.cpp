#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <opencv2/highgui/highgui.hpp>
#include <TagDrawer.hpp>

#include "test-metadata.hpp"

#include <DetectChilitags.hpp>

#include <iostream>
#include <map>
#include <algorithm>

const static int ITERATIONS = 1;

using namespace std;

double mean(const vector<double>& vals)
{
    double sum = 0.;
    for(auto v : vals) sum += v;
    return sum/vals.size();
}

double variance(const vector<double>& vals)
{
    double current_mean = mean(vals);
    double temp = 0;
    for(auto v : vals)
        temp += (current_mean-v)*(current_mean-v);
    return temp/vals.size();
}

double sigma(const vector<double>& vals)
{
    return sqrt(variance(vals));
}

// TODO
// - perspective transforms
// - luminosity (saturate-adding constants to the image?) and contrast (saturate-multiplying?)
// - sensor noiss with salt and pepper
// - compression artefacts (compress as jpg?)
// - gaussian blur for bad focus,
// - motion blur
// - resolution
// - pinhole camera distortions

TEST(Integration, Minimal) {
	int tExpectedId = 42;
	chilitags::TagDrawer tDrawer;
	// Tag needs to be > 12 px wide;
	int tZoom = 3;
	cv::Mat tImage = tDrawer(tExpectedId, tZoom, true);

	auto tTags = chilitags::DetectChilitags()(tImage);

	ASSERT_EQ(1, tTags.size());

	auto tActualId = tTags.cbegin()->first;
	EXPECT_EQ(tExpectedId, tActualId);

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

	auto tActualCorners = tTags.cbegin()->second;
	for (int i: {0,1,2,3}) {
		EXPECT_GT(0.1, cv::norm(tActualCorners[i] - tExpectedCorners[i]))
			<< "with i=" << i;
	}
}

namespace {
	std::vector<int> my_set_difference(
		const std::vector<int> & v1,
		const std::vector<int> & v2) {
		std::vector<int> tDifference(v1.size());
		auto tDifferenceEnd = std::set_difference(
				v1.cbegin(), v1.cend(),
				v2.cbegin(), v2.cend(),
				tDifference.begin()
				);
		tDifference.resize(tDifferenceEnd - tDifference.begin());
		return tDifference;
	}
}

TEST(Integration, Snapshots) {
	// Initialise the data path with en empty modulename,
	// to get the data from the root of the test data path
	cvtest::TS::ptr()->init("");

	chilitags::DetectChilitags tDetectChilitags;

	int tNewFalseNegatives = 0;
	int tNewTruePositives = 0;
	int tTotalFalseNegatives = 0;
	int tTotal = 0;

    map<int, vector<double>> runs_duration;

	for (auto tTestCase : TestMetadata::all) {
		std::string tPath = std::string(cvtest::TS::ptr()->get_data_path())+tTestCase.filename;
		cv::Mat tImage = cv::imread(tPath);

		if(tImage.data) {
			std::map<int, std::vector<cv::Point2f>> tTags;
            for (int i = 0 ; i < ITERATIONS ; i++) {
                int64 tStartCount = cv::getTickCount();
                tTags = tDetectChilitags(tImage);
                int64 tEndCount = cv::getTickCount();
                runs_duration[tImage.rows*tImage.cols].push_back(((double) tEndCount - tStartCount)*1000/cv::getTickFrequency());
            }

			std::vector<int> tFoundIds;
			for (const auto &tTag: tTags) tFoundIds.push_back(tTag.first);

			std::sort(
				tTestCase.expectedTagIds.begin(),
				tTestCase.expectedTagIds.end());


			std::vector<int> tFalsePositives = my_set_difference(
				tFoundIds, tTestCase.expectedTagIds);

			if(!tFalsePositives.empty())
				ADD_FAILURE()
					<< "    File: " << tTestCase.filename << "\n"
					<< "   Id(s): " << cv::Mat(tFalsePositives) << "\n";


			std::vector<int> tFalseNegatives = my_set_difference(
				tTestCase.expectedTagIds, tFoundIds);

			std::vector<int> tUnexpectedFalseNegatives = my_set_difference(
				tFalseNegatives, tTestCase.knownMissedTagIds);

			if(!tUnexpectedFalseNegatives.empty())
				ADD_FAILURE()
					<< "    File: " << tTestCase.filename << "\n"
					<< "   Id(s): " << cv::Mat(tUnexpectedFalseNegatives) << "\n";

			std::vector<int> tUnexpectedTruePositives = my_set_difference(
				tTestCase.knownMissedTagIds, tFalseNegatives);

			if (!tUnexpectedTruePositives.empty())
				std::cout << "Unexpected true positive(s)"
					<< "    File: " << tTestCase.filename << "\n"
					<< "   Id(s): " << cv::Mat(tUnexpectedTruePositives) << "\n";

			tTotal += tTestCase.expectedTagIds.size();
			tTotalFalseNegatives += tTestCase.expectedTagIds.size() - tFoundIds.size();
			tNewFalseNegatives += tUnexpectedFalseNegatives.size();
			tNewTruePositives += tUnexpectedTruePositives.size();
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
    cout << "Processing times (ms) results, on " << ITERATIONS << " iterations:\n";
    cout << "  n    Pixels   Average        SD\n";
	cout ;
	for (const auto & tDurations : runs_duration) {
		cout
			<< std::setw(3) << tDurations.second.size()/ITERATIONS
			<< std::setw(10) << tDurations.first
			<< std::setw(10) << std::fixed << std::setprecision(1) << mean(tDurations.second)
			<< std::setw(10) << std::fixed << std::setprecision(1) << sigma(tDurations.second)
			<< "\n";
	}

	std::cout << tTotalFalseNegatives << "/" << tTotal << " tags were not detected.\n";
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
