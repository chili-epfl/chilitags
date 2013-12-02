#include <DetectChilitags.hpp>

#include <opencv2/highgui/highgui.hpp> // imread

#include <iostream>
using std::cout;


int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout
			<< "Usage: chilitags-detect <image>\n\n"
			<< "Returns the list of detected markers id in the image, one per line.\n";
        return 1;
    }

    chilitags::DetectChilitags tDetectChilitags;

    cv::Mat tImage = cv::imread(argv[1]);

    if(tImage.data) {
        tDetectChilitags(tImage);

		auto tTags = tDetectChilitags.Tags();
		for (const auto &tTag: tTags) cout << tTag.first << "\n";

        return 0;
    }

    return 1;
}
