#include <chilitags.hpp>

#include <opencv2/highgui/highgui.hpp> // imread

#include <iostream>
using std::cout;


int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout
            << "Usage: chilitags-detect <image>\n\n"
            << "Returns the list of detected tag id's in the image, one per line.\n";
        return 1;
    }

    cv::Mat image = cv::imread(argv[1]);
    if(image.data) {
        for (const auto &tag : chilitags::Chilitags().find(image))
            cout << tag.first << "\n";

        return 0;
    }
    return 1;
}
