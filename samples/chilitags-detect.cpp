#include <DetectChilitags.hpp>
#include <Chilitag.hpp>

#include <opencv2/highgui/highgui.hpp> // imread

#include <iostream>

using std::vector;
using std::pair;
using std::string;
using chilitags::Chilitag;

int main(int argc, char* argv[])
{
    const char* help = "Usage: chilitags-detect <image>\n\nReturns the list of detected markers id in the image, one per line.";
 
    if (argc < 2) {
        puts(help);
        return 1;
    }

    cv::Mat tImage;
    chilitags::DetectChilitags tDetectChilitags(&tImage);

    // Tags need to be registered before detection
    // (Chilitag's constructor takes care of that)
    for (int i = 0; i<1024; ++i) Chilitag tTag(i);

    tImage = cv::imread(argv[1]);

    if(tImage.data) {
        tDetectChilitags.update();

        for (int i = 0; i<1024; ++i) {
            Chilitag tTag(i, 0);
            if (tTag.isPresent()) std::cout << i << std::endl;
        }
        return 0;
    }
    else return 1;
}
