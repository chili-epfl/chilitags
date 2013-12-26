#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <opencv2/highgui/highgui.hpp>

#include "test-metadata.hpp"

#include <chilitags.hpp>

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
// - sensor noise with salt and pepper
// - compression artefacts (compress as jpg?)
// - gaussian blur for bad focus,
// - motion blur
// - resolution
// - pinhole camera distortions

TEST(Integration, Minimal) {
    int expectedId = 42;
    chilitags::Chilitags chilitags;
    // Tag needs to be > 12 px wide;
    int zoom = 3;
    cv::Mat image = chilitags.draw(expectedId, zoom, true);

    auto tags = chilitags.find(image);

    ASSERT_EQ(1, tags.size());

    auto actualId = tags.cbegin()->first;
    EXPECT_EQ(expectedId, actualId);

    float close = zoom*2.0f;
    float far   = zoom*12.0f;
    std::vector<cv::Point2f> expectedCorners = {
        cv::Point2f(close, close),
        cv::Point2f(far, close),
        cv::Point2f(far, far),
        cv::Point2f(close, far),
    };

    // A pixel is a 1x1 square around its center
    cv::add(expectedCorners, cv::Scalar::all(-0.5), expectedCorners);

    auto actualCorners = tags.cbegin()->second;
    for (int i : {0,1,2,3}) {
        EXPECT_GT(0.1, cv::norm(actualCorners[i] - expectedCorners[i]))
        << "with i=" << i;
    }
}

namespace {
std::vector<int> my_set_difference(
    const std::vector<int> & v1,
    const std::vector<int> & v2) {
    std::vector<int> difference(v1.size());
    auto differenceEnd = std::set_difference(
        v1.cbegin(), v1.cend(),
        v2.cbegin(), v2.cend(),
        difference.begin()
        );
    difference.resize(differenceEnd - difference.begin());
    return difference;
}
}

TEST(Integration, Snapshots) {
    // Initialise the data path with en empty modulename,
    // to get the data from the root of the test data path
    cvtest::TS::ptr()->init("");

    chilitags::Chilitags chilitags;
    // We do not want any persistence, to measure the taw performances
    chilitags.setPersistence(0);

    int newFalseNegatives = 0;
    int newTruePositives = 0;
    int totalFalseNegatives = 0;
    int total = 0;

    map<int, vector<double> > runs_duration;

    for (auto testCase : TestMetadata::all) {
        std::string path = std::string(cvtest::TS::ptr()->get_data_path())+testCase.filename;
        cv::Mat image = cv::imread(path);

        if(image.data) {
            std::map<int, std::vector<cv::Point2f> > tags;
            for (int i = 0; i < ITERATIONS; i++) {
                int64 startCount = cv::getTickCount();
                tags = chilitags.find(image);
                int64 endCount = cv::getTickCount();
                runs_duration[image.rows*image.cols].push_back(((double) endCount - startCount)*1000/cv::getTickFrequency());
            }

            std::vector<int> foundIds;
            for (const auto &tag : tags) foundIds.push_back(tag.first);

            std::sort(
                testCase.expectedTagIds.begin(),
                testCase.expectedTagIds.end());


            std::vector<int> falsePositives = my_set_difference(
                foundIds, testCase.expectedTagIds);

            if(!falsePositives.empty())
                ADD_FAILURE()
                << "    File: " << testCase.filename << "\n"
                << "   Id(s): " << cv::Mat(falsePositives) << "\n";


            std::vector<int> falseNegatives = my_set_difference(
                testCase.expectedTagIds, foundIds);

            std::vector<int> unexpectedFalseNegatives = my_set_difference(
                falseNegatives, testCase.knownMissedTagIds);

            if(!unexpectedFalseNegatives.empty())
                ADD_FAILURE()
                << "    File: " << testCase.filename << "\n"
                << "   Id(s): " << cv::Mat(unexpectedFalseNegatives) << "\n";

            std::vector<int> unexpectedTruePositives = my_set_difference(
                testCase.knownMissedTagIds, falseNegatives);

            if (!unexpectedTruePositives.empty())
                std::cout << "Unexpected true positive(s)"
                          << "    File: " << testCase.filename << "\n"
                          << "   Id(s): " << cv::Mat(unexpectedTruePositives) << "\n";

            total += testCase.expectedTagIds.size();
            totalFalseNegatives += testCase.expectedTagIds.size() - foundIds.size();
            newFalseNegatives += unexpectedFalseNegatives.size();
            newTruePositives += unexpectedTruePositives.size();
        }
        else {
            ADD_FAILURE()
            << "Unable to read: " << path << "\n"
            << "Did you correctly set the OPENCV_TEST_DATA_PATH environment variable?\n"
            << "CMake takes care of this if you set its TEST_DATA variable.\n"
            << "You can download the test data from\n"
            << "https://github.com/chili-epfl/chilitags-testdata";
        }
    }
    cout << "Processing times (ms) results, on " << ITERATIONS << " iterations:\n";
    cout << "  n    Pixels   Average        SD\n";

    for (const auto & durations : runs_duration) {
        cout
        << std::setw(3) << durations.second.size()/ITERATIONS
        << std::setw(10) << durations.first
        << std::setw(10) << std::fixed << std::setprecision(1) << mean(durations.second)
        << std::setw(10) << std::fixed << std::setprecision(1) << sigma(durations.second)
        << "\n";
    }

    std::cout << totalFalseNegatives << "/" << total << " tags were not detected.\n";
    if (newTruePositives > 0) {
        std::cout
        << "You "<< (newFalseNegatives>0 ? "partially" : "")
        << "improved the detection:\n"
        << newFalseNegatives << " new false negatives (bad) and "
        << newTruePositives  << " new true positives (good)\n"
        << "Please review, and if necessary, update the test case.\n";
    }
}

CV_TEST_MAIN(".")
