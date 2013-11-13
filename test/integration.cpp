#include <opencv2/ts/ts.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <TagDrawer.hpp>

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
		cv::Point2f(tClose, tFar)};

	// A pixel is a 1x1 square around its center
	cv::add(tExpectedCorners, cv::Scalar::all(-0.5), tExpectedCorners);

	auto tActualCorners = tDetectedTag.getCorners();
	for (int i: {0,1,2,3}) {
		ASSERT_GT(0.1, cv::norm(tActualCorners[i] - tExpectedCorners[i]));
	}
}

TEST(Integration, Snapshots) {

	using std::vector;
	using std::pair;
	using std::string;
	using chilitags::Chilitag;

	// The ids are assumed to be sorted
	vector< pair<string, vector<int>> > tTestMatrix = {
		{"stills/640x480/severin01.jpg",   {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
		{"stills/640x480/severin02.jpg",   {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
		{"stills/640x480/severin03.jpg",   {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
		{"stills/640x480/severin04.jpg",   {      3,        8,9,10,         14               }},
		{"stills/640x480/severin05.jpg",   {0,1,    4,5,6,7,          12,13,14,      17,18   }},
		{"stills/640x480/severin06.jpg",   {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
		{"stills/640x480/nao01.jpg",       {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
		{"stills/640x480/nao02.jpg",       {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
		{"stills/640x480/nao03.jpg",       {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
		{"stills/640x480/nao04.jpg",       {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
		{"stills/640x480/nao05.jpg",       {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
		{"stills/640x480/nao06.jpg",       {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
		{"stills/640x480/occlusion01.jpg", {  1                                     ,17      }},
		{"stills/640x480/occlusion02.jpg", {  1                                     ,17      }},
		{"stills/320x240/nao01.png",       {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
		{"stills/320x240/nao02.png",       {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
		{"stills/320x240/nao03.png",       {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
		{"stills/320x240/nao04.png",       {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
		{"stills/320x240/nao05.png",       {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
		{"stills/320x240/nao06.png",       {46, 50, 51, 55, 59, 62}},
		{"stills/320x240/nao07.png",       {46, 50, 51, 55, 59, 62}},
		{"stills/320x240/nao08.png",       {50, 51, 55, 62}},
	};

	// The game is to lower these numbers
	const int tExpectedFalseNegatives = 156;
	const int tExpectedFalsePositives = 0;

	// Initialise the data path with en empty modulename,
	// to get the data from the root of the test data path
	cvtest::TS::ptr()->init("");

	cv::Mat tImage;
	chilitags::DetectChilitags tDetectChilitags(&tImage);

	// Tags need to be registered before detection
	// (Chilitag's constructor takes care of that)
	for (int i = 0; i<1024; ++i) Chilitag tTag(i);

	int tActualFalseNegatives = 0;
	int tActualFalsePositives = 0;
	for (const auto & tTestCase : tTestMatrix) {
		string tPath = string(cvtest::TS::ptr()->get_data_path())+tTestCase.first;
		tImage = cv::imread(tPath);

		if(tImage.data) {
			tDetectChilitags.update();

 			std::cout << "Missing markers for " << tTestCase.first << ": ";
			// We consider everything false positive,
			// and remove the expected ones later
			auto tExpectedTagIt = tTestCase.second.begin();
			for (int i = 0; i<1024; ++i) {
				// No persistence
				Chilitag tTag(i, 0);
				if (*tExpectedTagIt == i) {
					if (!tTag.isPresent()) {
						++tActualFalseNegatives;
 						std::cout << i << " ";
					}
					++tExpectedTagIt;
				}
				else if (tTag.isPresent()) {
					++tActualFalsePositives;
					ADD_FAILURE() << "Falsely positive detection\n"
						<< "    File: " << tTestCase.first << "\n"
						<< "     Tag: " << i << "\n";
				}
			}
 			std::cout << std::endl;

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

	EXPECT_LE(tExpectedFalseNegatives, tActualFalseNegatives)
		<< "It looks like you actually improved the detection here\n"
		<< "Please review and update this test case to doube check\n";
	EXPECT_EQ(tExpectedFalseNegatives, tActualFalseNegatives);
	EXPECT_EQ(tExpectedFalsePositives, tActualFalsePositives);
}

CV_TEST_MAIN(".")
