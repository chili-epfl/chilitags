#include <DetectChilitags.hpp>
#include <Chilitag.hpp>
using chilitags::Chilitag;

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

    // Tags need to be registered before detection
    // (Chilitag's constructor takes care of that)
    for (int i = 0; i<1024; ++i) Chilitag tTag(i);

    cv::Mat tImage = cv::imread(argv[1]);

    if(tImage.data) {
        tDetectChilitags(tImage);

        for (int i = 0; i<1024; ++i) {
            if (Chilitag(i, 0).isPresent()) cout << i << "\n";
        }
        return 0;
    }

    return 1;
}
