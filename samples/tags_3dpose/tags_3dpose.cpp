// This file serves as an illustration of how to use cv::solvePnP to estimate the 6D pose of a marker.
// It requires the chilitags library for 2D tag recognition.


// This header contains the detection part
#include <DetectChilitags.hpp>
// This header provides an easy way to use the tag detection information
#include <Chilitag.hpp>

#include <opencv2/core/core_c.h>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

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
    const char* help = "Usage: tags3dpose -s <square_size> -i <camera calibration (YAML)>\n";
 
    char* intrinsicsFilename = 0;
    double squareSize = 0.;

    for( int i = 1; i < argc; i++ )
    {
        if( strcmp(argv[i], "-i") == 0 )
            intrinsicsFilename = argv[++i];
        else if( strcmp(argv[i], "-s") == 0 )
        {
            if(sscanf(argv[++i], "%lf", &squareSize) != 1 || squareSize <= 0)
            {
                printf("Incorrect -s parameter (must be a positive real number)\n");
                puts(help);
                return 0;
            }
        }
    }
    if (intrinsicsFilename == 0 || squareSize == 0)
    {
        puts(help);
        return 0;
    }

    double tagRecoDuration, poseEstimationDuration;

    // Format floats
    cout.precision(1);
    cout.setf(ios::fixed, ios::floatfield);

    const static cv::Scalar scColor(255, 0, 255);
    // These constants will be given to OpenCv for drawing with
    // sub-pixel accuracy with fixed point precision coordinates
    static const int scShift = 16;
    static const float scPrecision = 1<<scShift;


    int tCameraIndex = 0;

    Mat cameraMatrix, distCoeffs;
    Size calibratedImageSize;
    readCameraMatrix(intrinsicsFilename, cameraMatrix, distCoeffs, calibratedImageSize );


    // The source of input images
    cv::VideoCapture tCapture(tCameraIndex);
    if (!tCapture.isOpened())
    {
        std::cerr << "Unable to initialise video capture." << std::endl;
        return 1;
    }
    tCapture.set(CV_CAP_PROP_FRAME_WIDTH, calibratedImageSize.width);
    tCapture.set(CV_CAP_PROP_FRAME_HEIGHT, calibratedImageSize.height);

    cv::namedWindow("TagPoseEstimation");

    int64 startTickCount;

    // The tag detection happens in the DetectChilitags class.
    // All it needs is a pointer to a OpenCv Image, i.e. a cv::Mat *
    // and a call to its update() method every time the image is updated.
    cv::Mat tInputImage;
    chilitags::DetectChilitags tDetectChilitags(&tInputImage);

    // store the object's point in the object coordinates -> the 4 corners
    // of our marker (here, in mm).
    vector<Point3f> markerPoints;
    markerPoints.push_back(Point3f(0.,0.,0.));
    markerPoints.push_back(Point3f(squareSize,0.,0.));
    markerPoints.push_back(Point3f(squareSize,squareSize,0.));
    markerPoints.push_back(Point3f(0.,squareSize,0.));

    // Rotation & translation vectors, computed by cv::solvePnP
    Mat rvec, tvec;

    // Main loop, exiting when 'q is pressed'
    for (; 'q' != (char) cv::waitKey(10); ) {

        // Capture a new image.
        tCapture.read(tInputImage);

        // Detect tags on the current image.
        startTickCount = cv::getTickCount();
        tDetectChilitags.update();
        tagRecoDuration = (1000 * (double) (cv::getTickCount()-startTickCount)) / cv::getTickFrequency();

        cout << "\x1b[KTag detec.: " << tagRecoDuration << "ms" << endl; 

        // We dont want to draw directly on the input image, so we clone it
        cv::Mat tOutputImage = tInputImage.clone();

        // We iterate over the 1024 possible tags (from #0 to #1023)
        for (int tTagId = 0; tTagId < 1024; ++tTagId) {

            chilitags::Chilitag tTag(tTagId);
            if (tTag.isPresent()) {

                chilitags::Quad tCorners = tTag.getCorners();

                startTickCount = cv::getTickCount();

                // Find the 3D pose of our marker
                solvePnP(markerPoints, tCorners.toVector(), 
                        cameraMatrix, distCoeffs,
                        rvec, tvec, false,
                        cv::ITERATIVE);

                // in nanoseconds
                poseEstimationDuration = (1000000 * (double) (cv::getTickCount()-startTickCount)) / cv::getTickFrequency();

                cout << "\x1b[K" 
                    << tvec.at<double>(0) << "mm, " << tvec.at<double>(1) << "mm, " << tvec.at<double>(2) << "mm, " 
                    << ", pose estim.: " << poseEstimationDuration << "nanosec." << endl << "\x1b[1F";


                // We draw this quadrilateral
                for (size_t i = 0; i < 4; ++i) {
                    cv::line(
                        tOutputImage,
                        scPrecision*tCorners[i],
                        scPrecision*tCorners[(i+1)%4],
                        scColor, 1, CV_AA, scShift);
                }

            break; // only track the first tag found.
            }
        }
        cout << "\x1b[1F";
        cv::imshow("TagPoseEstimation", tOutputImage);
    }

    cout << endl;
    cv::destroyWindow("TagPoseEstimation");
    tCapture.release();

    return 0;
}

