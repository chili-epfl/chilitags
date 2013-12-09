#include <iostream>

#include <DetectChilitags.hpp>
#include <Objects.hpp>

#include <opencv2/core/core.hpp> // for cv::Mat
#include <opencv2/core/core_c.h> // CV_AA
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
    const char* help = "Usage: objects-gui -c <markers configuration (YAML)> -i <camera calibration (YAML)>\n";
 
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
	cv::namedWindow("Pose Estimation");

	static const float DEFAULT_SIZE = 20.f;
    chilitags::DetectChilitags detector;
    chilitags::Objects objects(cameraMatrix, distCoeffs,
                               configFilename,
                               DEFAULT_SIZE);  //default size

    for (; 'q' != (char) cv::waitKey(10); ) {
		cv::Mat tInputImage;
        capture.read(tInputImage);
		static const float OUTPUT_SIZE = 1000.f;
		cv::Mat tOutputImage(cv::Size(OUTPUT_SIZE,OUTPUT_SIZE), CV_8UC3, cv::Scalar(0,0,0));

        for (auto& kv : objects(detector(tInputImage))) {

			static const cv::Matx44f PROJECTION = {
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,1,0,
			};
			static const cv::Vec4f UNITS[4] {
				{0.f, 0.f, 0.f, 1.f},
				{DEFAULT_SIZE, 0.f, 0.f, 1.f},
				{0.f, DEFAULT_SIZE, 0.f, 1.f},
				{0.f, 0.f, DEFAULT_SIZE, 1.f},
			};

			cv::Matx44f tTransformation = kv.second;
			cv::Vec4f tReferential[4] = {
				PROJECTION*tTransformation*UNITS[0],
				PROJECTION*tTransformation*UNITS[1],
				PROJECTION*tTransformation*UNITS[2],
				PROJECTION*tTransformation*UNITS[3],
			};

			std::vector<cv::Point2f> t2DPoints;
			for (auto tHomogenousPoint : tReferential)
				t2DPoints.push_back(cv::Point2f(
					OUTPUT_SIZE*(.5+tHomogenousPoint[0]/tHomogenousPoint[3]),
					OUTPUT_SIZE*(.5+tHomogenousPoint[1]/tHomogenousPoint[3])
				));

			static const int SHIFT = 16;
			static const float PRECISION = 1<<SHIFT;
			static const std::string AXIS_NAMES[3] = { "x", "y", "z" };
			static const cv::Scalar AXIS_COLORS[3] = {
				{0,0,255},{0,255,0},{255,0,0},
			};
			for (int i: {1,2,3}) {
				cv::line(
					tOutputImage,
					PRECISION*t2DPoints[0],
					PRECISION*t2DPoints[i],
					AXIS_COLORS[i-1],
					1, CV_AA, SHIFT);
				cv::putText(tOutputImage, AXIS_NAMES[i-1], t2DPoints[i],
					cv::FONT_HERSHEY_SIMPLEX, 0.5, AXIS_COLORS[i-1]);
			}

			cv::putText(tOutputImage, kv.first, t2DPoints[0],
				cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255,255,255));
        }

		cv::imshow("Pose Estimation", tOutputImage);
    }

	cv::destroyWindow("Pose Estimation");
    capture.release();

    return 0;
}

