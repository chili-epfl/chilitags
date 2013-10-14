#ifndef Estimator_HPP
#define Estimator_HPP

#include "opencv2/video/tracking.hpp"

namespace chilitags {

template <int NDIMS>
class Estimator {

public:

    Estimator(cv::Mat pFirstMeasurement):
	mMeasurementAge(0),
	mFilter(
		2*NDIMS, //dynamic parameters: x, y, z, dx, dy, dz
		NDIMS, //measurements: x, y, z
		0) // no control parameters
    {
		// transitionMatrix =
		// 1 0 0 1 0 0
		// 0 1 0 0 1 0
		// 0 0 1 0 0 1
		// 0 0 0 1 0 0
		// 0 0 0 0 1 0
		// 0 0 0 0 0 1
		mFilter.transitionMatrix = cv::Mat::zeros(
			2*NDIMS, 2*NDIMS, CV_32F);
		for (int i = 0; i<NDIMS; ++i) {
			mFilter.transitionMatrix.at<float>(i, i) = 1;
			mFilter.transitionMatrix.at<float>(i, NDIMS+i) = 1;
			mFilter.transitionMatrix.at<float>(NDIMS+i, NDIMS+i) = 1;
		}

		cv::setIdentity(mFilter.measurementMatrix);
		cv::setIdentity(mFilter.processNoiseCov, cv::Scalar::all(1e-5));
		cv::setIdentity(mFilter.measurementNoiseCov, cv::Scalar::all(1e-1));
		cv::setIdentity(mFilter.errorCovPost, cv::Scalar::all(1));

		// Initialize the filter with the current position
		// The rest (speeds) is already initialised to 0 by default.
		pFirstMeasurement.copyTo(mFilter.statePost(cv::Rect(0,0,1,NDIMS)));

		mEstimation = mFilter.predict()(cv::Rect(0,0,1,NDIMS));
    }

	/** Needs to be called every time there is a new frame.
	 */
	void predict() {
		++mMeasurementAge;
		mEstimation = mFilter.predict()(cv::Rect(0,0,1,NDIMS));
	}

	/** May be called after predict(), if a new measurement is available.
	 */
    void correct(cv::Mat pMeasurement)
    {
		mMeasurementAge = 0;
		mEstimation = mFilter.correct(pMeasurement)(cv::Rect(0,0,1,NDIMS));
    }

	/** Returns the latest estimation.
	*/
    cv::Mat getEstimation() const
    {
        return mEstimation;
    }

	/** Returns how many times predict() has been called without being
	 * followed by a call to correct().
	 * In other words, it tells how long the estimation has been computed
	 * without actual measure.
	 */
	int getMeasurementAge() const
	{
		return mMeasurementAge;
	}

protected:
	int mMeasurementAge;
	cv::KalmanFilter mFilter;
	cv::Mat mEstimation;

};

}

#endif
