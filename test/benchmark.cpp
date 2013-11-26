#ifdef OPENCV3
#include <opencv2/ts.hpp>
#include <opencv2/core/utility.hpp> // getTickCount...
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <opencv2/highgui/highgui.hpp>
#include <TagDrawer.hpp>

#include <DetectChilitags.hpp>
#include <Chilitag.hpp>

#include <cmath>
#include <iostream>

const static int ITERATIONS = 20;

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

    // The ids are assumed to be sorted
    vector< pair<string, vector<int>> > tTestMatrix = {
        {"stills/640x480/severin01.jpg",   {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
        {"stills/640x480/severin06.jpg",   {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
        {"stills/640x480/nao03.jpg",       {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
        {"stills/640x480/nao04.jpg",       {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
        {"stills/640x480/nao05.jpg",       {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}},
    };

    // The game is to lower these numbers
#ifdef OPENCV3
	const int tExpectedFalseNegatives = 3;
#else
	const int tExpectedFalseNegatives = 5;
#endif
    const int tExpectedFalsePositives = 0;

    // Initialise the data path with en empty modulename,
    // to get the data from the root of the test data path
    cvtest::TS::ptr()->init("");

    cv::Mat tImage;

    vector<double> runs_duration;

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
            for (int i = 0 ; i < ITERATIONS ; i++) {
                int64 tStartCount = cv::getTickCount();
                tDetectChilitags.update();
                runs_duration.push_back(((double)cv::getTickCount() - tStartCount)*1000/cv::getTickFrequency());
            }

            //cout << "Missing markers for " << tTestCase.first << ": ";
            // We consider everything false positive,
            // and remove the expected ones later
            auto tExpectedTagIt = tTestCase.second.begin();
            for (int i = 0; i<1024; ++i) {
                // No persistence
                Chilitag tTag(i, 0);
                if (*tExpectedTagIt == i) {
                    if (!tTag.isPresent()) {
                        ++tActualFalseNegatives;
                        //cout << i << " ";
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
            //cout << endl;

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
    cout << "Benchmark results, on " << ITERATIONS << " iterations:" << endl;
    cout << "\t- Time to update markers: " << mean(runs_duration) << "ms" << endl;
    cout << "\t- Standard deviation: " << sigma(runs_duration) << "ms" << endl;


    EXPECT_LE(tExpectedFalseNegatives, tActualFalseNegatives)
        << "It looks like you actually improved the detection here\n"
        << "Please review and update this test case to doube check\n";
    EXPECT_EQ(tExpectedFalseNegatives, tActualFalseNegatives);
    EXPECT_EQ(tExpectedFalsePositives, tActualFalsePositives);
}

CV_TEST_MAIN(".")
