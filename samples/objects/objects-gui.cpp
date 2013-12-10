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
	static const float DEFAULT_SIZE = 20.f;
    chilitags::Objects objects(DEFAULT_SIZE, configFilename);

	Mat cameraMatrix;
	Mat distCoeffs;
    if (intrinsicsFilename) {
		Size calibratedImageSize;
		readCameraMatrix(intrinsicsFilename, cameraMatrix, distCoeffs, calibratedImageSize );
#ifdef OPENCV3
		capture.set(cv::CAP_PROP_FRAME_WIDTH, calibratedImageSize.width);
		capture.set(cv::CAP_PROP_FRAME_HEIGHT, calibratedImageSize.height);
#else
		capture.set(CV_CAP_PROP_FRAME_WIDTH, calibratedImageSize.width);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT, calibratedImageSize.height);
#endif
	} else {
		double tFocalLength = 817.;
		cameraMatrix = (cv::Mat_<double>(3,3) << tFocalLength,0,0, 0,tFocalLength,0, 0,0,1);
		distCoeffs = cv::Mat::zeros(5, 1, CV_64F);
	}
	objects.setCalibration(cameraMatrix, distCoeffs);

	cv::Mat tProjectionMat = cv::Mat::zeros(4,4,CV_64F);
	cameraMatrix.copyTo(tProjectionMat(cv::Rect(0,0,3,3)));
	cv::Matx44d tProjection = tProjectionMat;
	tProjection(3,2) = 1;

    /*****************************/
    /*             Go!           */
    /*****************************/
	cv::namedWindow("Pose Estimation");

    chilitags::DetectChilitags detector;

    for (; 'q' != (char) cv::waitKey(10); ) {
		cv::Mat tInputImage;
        capture.read(tInputImage);
		cv::Mat tOutputImage(tInputImage.size(), CV_8UC3, cv::Scalar(0,0,0));

        for (auto& kv : objects(detector(tInputImage))) {

			static const cv::Vec4d UNITS[4] {
				{0.f, 0.f, 0.f, 1.f},
				{DEFAULT_SIZE, 0.f, 0.f, 1.f},
				{0.f, DEFAULT_SIZE, 0.f, 1.f},
				{0.f, 0.f, DEFAULT_SIZE, 1.f},
			};

			cv::Matx44d tTransformation = kv.second;
			cv::Vec4f tReferential[4] = {
				tProjection*tTransformation*UNITS[0],
				tProjection*tTransformation*UNITS[1],
				tProjection*tTransformation*UNITS[2],
				tProjection*tTransformation*UNITS[3],
			};

			std::vector<cv::Point2f> t2DPoints;
			for (auto tHomogenousPoint : tReferential)
				t2DPoints.push_back(cv::Point2f(
					tHomogenousPoint[0]/tHomogenousPoint[3],
					tHomogenousPoint[1]/tHomogenousPoint[3]
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

