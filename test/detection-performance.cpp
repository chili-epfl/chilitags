/*******************************************************************************
*   Copyright 2013-2014 EPFL                                                   *
*   Copyright 2013-2014 Quentin Bonnard                                        *
*                                                                              *
*   This file is part of chilitags.                                            *
*                                                                              *
*   Chilitags is free software: you can redistribute it and/or modify          *
*   it under the terms of the Lesser GNU General Public License as             *
*   published by the Free Software Foundation, either version 3 of the         *
*   License, or (at your option) any later version.                            *
*                                                                              *
*   Chilitags is distributed in the hope that it will be useful,               *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of             *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
*   GNU Lesser General Public License for more details.                        *
*                                                                              *
*   You should have received a copy of the GNU Lesser General Public License   *
*   along with Chilitags.  If not, see <http://www.gnu.org/licenses/>.         *
*******************************************************************************/

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

// TODO
// - perspective transforms
// - luminosity (saturate-adding constants to the image?) and contrast (saturate-multiplying?)
// - sensor noise with salt and pepper
// - compression artefacts (compress as jpg?)
// - gaussian blur for bad focus,
// - motion blur
// - resolution
// - pinhole camera distortions

const static int ITERATIONS = 1;

using namespace std;

namespace {

float mean(const vector<float>& vals)
{
    float sum = 0.0f;
    for(auto v : vals) sum += v;
    return sum/vals.size();
}

float variance(const vector<float>& vals)
{
    float current_mean = mean(vals);
    float temp = 0;
    for(auto v : vals)
        temp += (current_mean-v)*(current_mean-v);
    return temp/vals.size();
}

float sigma(const vector<float>& vals)
{
    return sqrt(variance(vals));
}

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
    // We measure chilitags at its best, and compare optimisations later
    chilitags.setPerformance(chilitags::Chilitags::ROBUST);
    // We do not want any filtering, to measure the raw performances
    chilitags.setFilter(0, 0.0f);

    map<int, std::string> resolution;

    int newFalseNegatives = 0;
    int newTruePositives = 0;
    int totalFalsePositives = 0;
    int totalFalseNegatives = 0;
    int total = 0;

    map<int, vector<float> > referenceDuration;
    map<int, int> referenceFalseNegatives;

    for (auto testCase : TestMetadata::all) {
        std::string path = std::string(cvtest::TS::ptr()->get_data_path())+testCase.filename;
        cv::Mat image = cv::imread(path);

        if(image.data) {
            chilitags::TagCornerMap tags;
            resolution[image.cols*image.rows] = cv::format("%dx%d", image.cols, image.rows);
            for (int i = 0; i < ITERATIONS; i++) {
                int64 startCount = cv::getTickCount();
                tags = chilitags.find(image);
                int64 endCount = cv::getTickCount();
                referenceDuration[image.rows*image.cols].push_back(
                    ((float) endCount - startCount)*1000/cv::getTickFrequency());
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
                    << "False positive !\n"
                    << "    File: " << testCase.filename << "\n"
                    << "   Id(s): " << cv::Mat(falsePositives) << "\n";


            std::vector<int> falseNegatives = my_set_difference(
                testCase.expectedTagIds, foundIds);
            referenceFalseNegatives[image.cols*image.rows] += falseNegatives.size();

            std::vector<int> unexpectedFalseNegatives = my_set_difference(
                falseNegatives, testCase.knownMissedTagIds);

            if(!unexpectedFalseNegatives.empty())
                ADD_FAILURE()
                    << "False negative !\n"
                    << "    File: " << testCase.filename << "\n"
                    << "   Id(s): " << cv::Mat(unexpectedFalseNegatives) << "\n";

            std::vector<int> unexpectedTruePositives = my_set_difference(
                testCase.knownMissedTagIds, falseNegatives);

            if (!unexpectedTruePositives.empty())
                std::cout << "Unexpected true positive(s)"
                          << "    File: " << testCase.filename << "\n"
                          << "   Id(s): " << cv::Mat(unexpectedTruePositives) << "\n";

            total += testCase.expectedTagIds.size();
            totalFalsePositives += falsePositives.size();
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

    for (const auto & durations : referenceDuration) {
        cout
            << std::setw(3) << durations.second.size()/ITERATIONS
            << std::setw(10) << resolution[durations.first]
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
    if (totalFalsePositives > 0) {
        std::cout << "There are " << totalFalsePositives << " false positives.\n";

    }

    //chilitags.setCornerRefinement(false);
    //chilitags.setMaxInputWidth(640);
    //chilitags.setMinInputWidth(0);
    chilitags.setPerformance(chilitags::Chilitags::FAST);

    map<int, vector<float> > perfDurations;
    map<int, int > perfFalseNegatives;
    int perfTotalFalseNegatives = 0;
    for (auto testCase : TestMetadata::all) {
        std::string path = std::string(cvtest::TS::ptr()->get_data_path())+testCase.filename;
        cv::Mat image = cv::imread(path);

        if(image.data) {
            chilitags::TagCornerMap tags;
            for (int i = 0; i < ITERATIONS; i++) {
                int64 startCount = cv::getTickCount();
                tags = chilitags.find(image);
                int64 endCount = cv::getTickCount();
                perfDurations[image.rows*image.cols].push_back(((float) endCount - startCount)*1000/cv::getTickFrequency());
            }

            std::vector<int> foundIds;

            perfFalseNegatives[image.rows*image.cols] += testCase.expectedTagIds.size() - tags.size();
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

    cout << "\nPerformance-tuned processing compared to default\n";
    cout << "  n    Pixels   Processing time   False negatives\n";
    auto perfDurationsIt = perfDurations.begin();
    auto perfFalseNegativesIt = perfFalseNegatives.begin();
    auto referenceFalseNegativesIt = referenceFalseNegatives.begin();
    int totalNewFalseNegatives = 0;
    for (const auto & durations : referenceDuration) {
        std::transform(
            perfDurationsIt->second.begin(), perfDurationsIt->second.end(),
            durations.second.begin(),
            perfDurationsIt->second.begin(),
            [](float a, float b){
            return 100.0f*(a-b)/b;
        });

        bool increased = perfFalseNegativesIt->second > referenceFalseNegativesIt->second;
        cout
            << std::setw(3) << durations.second.size()/ITERATIONS
            << std::setw(10) << resolution[durations.first]
            << std::setw(17) << std::fixed << std::setprecision(0) <<
            mean(perfDurationsIt->second) << "%"
            << std::setw(11) << perfFalseNegativesIt->second
            << " vs "
            << std::setw(3) << referenceFalseNegativesIt->second
            << (increased ? " (+" : " (")
            << perfFalseNegativesIt->second - referenceFalseNegativesIt->second
            << ")"
            << "\n";
        totalNewFalseNegatives += perfFalseNegativesIt->second;
        ++perfDurationsIt;
        ++perfFalseNegativesIt;
        ++referenceFalseNegativesIt;
    }
    std::cout << totalNewFalseNegatives << "/" << total << " tags were not detected with the tuned processing.\n";
}

CV_TEST_MAIN(".")
