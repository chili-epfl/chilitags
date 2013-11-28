#ifdef OPENCV3
#include <opencv2/ts.hpp>
#include <opencv2/core/utility.hpp> // getTickCount...
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <opencv2/highgui/highgui.hpp>
#include <TagDrawer.hpp>
#include "test-metadata.hpp"

#include <DetectChilitags.hpp>
#include <Chilitag.hpp>

#include <cmath>
#include <iostream>
#include <map>

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


TEST(Integration, Snapshots) {

    using chilitags::Chilitag;

    // Initialise the data path with en empty modulename,
    // to get the data from the root of the test data path
    cvtest::TS::ptr()->init("");

    map<int, vector<double>> runs_duration;

    chilitags::DetectChilitags tDetectChilitags;
    // Tags need to be registered before detection
    // (Chilitag's constructor takes care of that)
    for (int i = 0; i<1024; ++i) Chilitag tTag(i);

    for (const auto & tTestCase : TestMetadata::all) {
        string tPath = string(cvtest::TS::ptr()->get_data_path())+tTestCase.filename;
        cv::Mat tImage = cv::imread(tPath);

        if(tImage.data) {
            for (int i = 0 ; i < ITERATIONS ; i++) {
                int64 tStartCount = cv::getTickCount();
                tDetectChilitags(tImage);
                int64 tEndCount = cv::getTickCount();
                runs_duration[tImage.rows*tImage.cols].push_back(((double) tEndCount - tStartCount)*1000/cv::getTickFrequency());
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
}

CV_TEST_MAIN(".")
