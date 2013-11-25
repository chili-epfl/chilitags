#include <iostream>

#include <DetectChilitags.hpp>
#include <Chilitag.hpp>
#include <Objects.hpp>

#include <opencv2/core/core.hpp> // for cv::Mat
#include <opencv2/highgui/highgui.hpp> // for camera capture


using namespace std;
using namespace cv;

/*******************************************************/
/*   Helper to parse OpenCV camera calibration files   */
/*******************************************************/
static bool readCameraMatrix(const string& filename,
                             Mat& cameraMatrix, Mat& distCoeffs,
                             Size& calibratedImageSize )
{
    cout << "Reading camera calibration from " << filename << "..." << endl;
    FileStorage fs(filename, FileStorage::READ);
    fs["image_width"] >> calibratedImageSize.width;
    fs["image_height"] >> calibratedImageSize.height;
    fs["distortion_coefficients"] >> distCoeffs;
    fs["camera_matrix"] >> cameraMatrix;

    if( distCoeffs.type() != CV_64F )
        distCoeffs = Mat_<double>(distCoeffs);
    if( cameraMatrix.type() != CV_64F )
        cameraMatrix = Mat_<double>(cameraMatrix);

    return true;
}


int main(int argc, char* argv[])
{
    /*****************************/
    /*   Read command-line       */
    /*****************************/
    const char* help = "Usage: objects -c <markers configuration (YAML)> -i <camera calibration (YAML)>\n";
 
    char* intrinsicsFilename = 0;
    char* configFilename = 0;

    for( int i = 1; i < argc; i++ )
    {
        if( strcmp(argv[i], "-c") == 0 )
            configFilename = argv[++i];
        else if( strcmp(argv[i], "-i") == 0 )
            intrinsicsFilename = argv[++i];
    }
    if (intrinsicsFilename == 0 || configFilename == 0)
    {
        puts(help);
        return 0;
    }

    int tCameraIndex = 0;

    /*****************************/
    /* Read camera calibration   */
    /*****************************/
    Mat cameraMatrix, distCoeffs;
    Size calibratedImageSize;
    readCameraMatrix(intrinsicsFilename, cameraMatrix, distCoeffs, calibratedImageSize );


    /*****************************/
    /*    Init camera capture    */
    /*****************************/
     cv::VideoCapture capture(tCameraIndex);
    if (!capture.isOpened())
    {
        std::cerr << "Unable to initialise video capture." << std::endl;
        return 1;
    }
#ifdef OPENCV3
    capture.set(cv::CAP_PROP_FRAME_WIDTH, calibratedImageSize.width);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, calibratedImageSize.height);
#else
    capture.set(CV_CAP_PROP_FRAME_WIDTH, calibratedImageSize.width);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, calibratedImageSize.height);
#endif

    /*****************************/
    /*             Go!           */
    /*****************************/
    cout << "I'm now looking for objects..." << endl;
    cv::Mat tInputImage;
    chilitags::DetectChilitags detector(&tInputImage);

    chilitags::Objects objects(cameraMatrix, distCoeffs,
                               configFilename,
                               30);  //default size

    for (; 'q' != (char) cv::waitKey(10); ) {

        capture.read(tInputImage);
        detector.update();

        for (auto& kv : objects.all()) {
            cout << kv.first;
            cout << " at " << Mat(kv.second) << endl;
        }

    }

    capture.release();

    return 0;
}

