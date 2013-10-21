#include <opencv2/ts/ts.hpp>
#include <TagDrawer.hpp>

#include <DetectChilitags.hpp>
#include <Chilitag.hpp>

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

CV_TEST_MAIN(".")
