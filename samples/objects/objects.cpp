#include <iostream>

#include <DetectChilitags.hpp>
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
	cout
		<< "Usage: "<< argv[0]
		<< " [-c <markers configuration (YAML)>] -i [<camera calibration (YAML)>]\n";
 
    const char* intrinsicsFilename = 0;
    const char* configFilename = "";

    for( int i = 1; i < argc; i++ )
    {
        if( strcmp(argv[i], "-c") == 0 )
            configFilename = argv[++i];
        else if( strcmp(argv[i], "-i") == 0 )
            intrinsicsFilename = argv[++i];
    }

    /*****************************/
    /*    Init camera capture    */
    /*****************************/
    int tCameraIndex = 0;
     cv::VideoCapture capture(tCameraIndex);
    if (!capture.isOpened())
    {
        cerr << "Unable to initialise video capture.\n";
        return 1;
    }

    /******************************/
    /* Setting up pose estimation */
    /******************************/
    chilitags::Objects objects(30, configFilename);

    if (intrinsicsFilename) {
		Mat cameraMatrix, distCoeffs;
		Size calibratedImageSize;
		readCameraMatrix(intrinsicsFilename, cameraMatrix, distCoeffs, calibratedImageSize );
		objects.setCalibration(cameraMatrix, distCoeffs);
#ifdef OPENCV3
		capture.set(cv::CAP_PROP_FRAME_WIDTH, calibratedImageSize.width);
		capture.set(cv::CAP_PROP_FRAME_HEIGHT, calibratedImageSize.height);
#else
		capture.set(CV_CAP_PROP_FRAME_WIDTH, calibratedImageSize.width);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT, calibratedImageSize.height);
#endif
	}

    /*****************************/
    /*             Go!           */
    /*****************************/
    cout << "I'm now looking for objects...\n";
    cv::Mat tInputImage;
    chilitags::DetectChilitags detector;

    for (; 'q' != (char) cv::waitKey(10); ) {
        capture.read(tInputImage);

        for (auto& kv : objects(detector(tInputImage))) {
            cout << kv.first << " at " << Mat(kv.second) << "\n";
        }
    }

    capture.release();

    return 0;
}

