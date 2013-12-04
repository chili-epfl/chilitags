#ifndef KalmanOfSpeeds_HPP
#define KalmanOfSpeeds_HPP

#include <opencv2/video/tracking.hpp>
#include <opencv2/calib3d/calib3d.hpp>

namespace chilitags {

/**
 * A Kalman Filter using NDIMS measurements and their NORDERS derivates as
 * dynamic parameters.
 * For example, to filter 2D points using their speed and acceleration,
 * use NDIMS=2 and NORDERS=3.
 */
template <int NDIMS, int NORDERS>
class KalmanWithDerivates {

public:

    KalmanWithDerivates(cv::Mat pFirstMeasurement):
	mFilter( NORDERS*NDIMS, NDIMS, 0),
	mEstimation()
    {
		// transitionMatrix =
		// 1 0 0 1 0 0 ...
		// 0 1 0 0 1 0 ...
		// 0 0 1 0 0 1 ...
		// 0 0 0 1 0 0 ...
		// 0 0 0 0 1 0 ...
		// 0 0 0 0 0 1 ...
		// ...
		mFilter.transitionMatrix = cv::Mat::zeros(
			NORDERS*NDIMS, NORDERS*NDIMS, CV_32F);
		for (int i = 0; i<NDIMS*NORDERS; ++i) {
			for (int j = i; j<NDIMS*NORDERS; j+=NDIMS) {
				mFilter.transitionMatrix.at<float>(i, j) = 1;
			}
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
		mEstimation = mFilter.predict()(cv::Rect(0,0,1,NDIMS));
	}

	/** May be called after predict(), if a new measurement is available.
	 */
    void correct(cv::Mat pMeasurement)
    {
		mEstimation = mFilter.correct(pMeasurement)(cv::Rect(0,0,1,NDIMS));
    }

	/** Returns the latest estimation.
	*/
    cv::Mat get() const
    {
        return mEstimation;
    }

protected:
	cv::KalmanFilter mFilter;
	cv::Mat mEstimation;

};

class Estimator {

public:
	typedef KalmanWithDerivates<3,2> Filter;

	Estimator(cv::Mat pFirstTranslation, cv::Mat pFirstRotation):
	mMeasurementAge(0),
	mTranslation(pFirstTranslation),
	mRotation(pFirstRotation)
	{
	}

	/** Needs to be called every time there is a new frame.
	 */
	void predict() {
		++mMeasurementAge;
		mTranslation.predict();
		mRotation.predict();
	}

	/** May be called after predict(), if a new measurement is available.
	 */
    void correct(cv::Mat pTranslationMeasurement, cv::Mat pRotationMeasurement)
    {
		mMeasurementAge = 0;
		mTranslation.correct(pTranslationMeasurement);
		mRotation.correct(pRotationMeasurement);
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

	const Filter &translation() {return mTranslation;}
	const Filter &rotation() {return mRotation;}

	cv::Matx44f transformationMatrix() const
	{
		cv::Matx33f tRotationMatrix;
		cv::Rodrigues(mRotation.get(), tRotationMatrix);

		cv::Matx44f tTransformationMatrix;
		tTransformationMatrix(0,0) = tRotationMatrix(0,0);
		tTransformationMatrix(0,1) = tRotationMatrix(0,1);
		tTransformationMatrix(0,2) = tRotationMatrix(0,2);
		tTransformationMatrix(1,0) = tRotationMatrix(1,0);
		tTransformationMatrix(1,1) = tRotationMatrix(1,1);
		tTransformationMatrix(1,2) = tRotationMatrix(1,2);
		tTransformationMatrix(2,0) = tRotationMatrix(2,0);
		tTransformationMatrix(2,1) = tRotationMatrix(2,1);
		tTransformationMatrix(2,2) = tRotationMatrix(2,2);

		cv::Mat tTranslation = mTranslation.get();
		tTransformationMatrix(0,3) = tTranslation.at<float>(0);
		tTransformationMatrix(1,3) = tTranslation.at<float>(1);
		tTransformationMatrix(2,3) = tTranslation.at<float>(2);

		return tTransformationMatrix;
	}

protected:
	int mMeasurementAge;
	Filter mTranslation;
	Filter mRotation;
};

}

#endif
