#ifdef OPENCV3
#include <opencv2/ts.hpp>
#else
#include <opencv2/ts/ts.hpp>
#endif

#include <opencv2/core/core.hpp>

#include <Objects.hpp>

cv::Matx44f makeTransformation(
	float rx, float ry, float rz,
	float tx, float ty, float tz){

    static const float DEG2RAD = 3.141593f / 180.f;
    float A = cos(rx * DEG2RAD);
    float B = sin(rx * DEG2RAD);
    float C = cos(ry * DEG2RAD);
    float D = sin(ry * DEG2RAD);
    float E = cos(rz * DEG2RAD);
    float F = sin(rz * DEG2RAD);

    return {
            C*E        ,        -C*F ,    D , tx,
            B*D*E+A*F  ,  -B*D*F+A*E , -B*C , ty,
            -A*D*E+B*F , A*D*F+B*E   ,  A*C , tz,
            0.f        ,         0.f ,  0.f ,  1.f,
	};
}

cv::Point2f applyTransform(cv::Matx44f pTransformation, cv::Point2f pPoint) {
	cv::Vec4f tHomogenousPoint = cv::Vec4f(pPoint.x, pPoint.y, 0.f, 1.f);

	static const cv::Matx44f tProjectionMatrix = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,1,0,
	};
	cv::Vec4f tTransformedPoint = tProjectionMatrix*pTransformation*tHomogenousPoint;

	return cv::Point2f(
		tTransformedPoint[0]/tTransformedPoint[3],
		tTransformedPoint[1]/tTransformedPoint[3]);
}

TEST(Objects, FreeTags) {
	auto tExpectedTransformation = makeTransformation(35,45,65,20,40,60);

	float tSize = 37;
	std::vector<cv::Point2f> tCorners = {
		applyTransform(tExpectedTransformation, cv::Point2f(0.f   , 0.f   )),
		applyTransform(tExpectedTransformation, cv::Point2f(tSize , 0.f   )),
		applyTransform(tExpectedTransformation, cv::Point2f(tSize , tSize )),
		applyTransform(tExpectedTransformation, cv::Point2f(0.f   , tSize )),
	};

	cv::Matx33f tCamera = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1,
	};
	cv::Mat_<float>tDistortion (5,1);
	tDistortion << 0.f, 0.f, 0.f, 0.f, 0.f;
	chilitags::Objects tObjects(tCamera, tDistortion, tSize);

	int tTagId = 0;
	auto tResult = tObjects({{tTagId,tCorners}});
	ASSERT_EQ(1, tResult.size());

	std::string tActualID = tResult.cbegin()->first;
	EXPECT_EQ(cv::format("marker_%d", tTagId), tActualID);
	cv::Matx44f tActualTransformation = tResult.cbegin()->second;
	EXPECT_GT(1e-3, cv::norm(tActualTransformation-tExpectedTransformation))
		<< "\nExpected:\n" << cv::Mat(tExpectedTransformation)
		<< "\nActual:\n" << cv::Mat(tActualTransformation);
}

TEST(Objects, Configurations) {
	auto tObjectTransformation = makeTransformation(135, 145, 155, 201, 401, 601);

	std::vector<int> tIds = {2, 3};
	std::vector<float> tSizes = {20,30};
	std::vector<cv::Matx44f> tTagTransformations = {
		tObjectTransformation*makeTransformation(0, 0, 0, -50, -100, 0),
		tObjectTransformation*makeTransformation(0, 0, 0, +50, -100, 0),
	};

	std::map<int, std::vector<cv::Point2f>> tTags;
	for (int i = 0; i<tIds.size(); ++i) {
		tTags[tIds[i]] = {
			applyTransform(tTagTransformations[i], cv::Point2f(0.f      , 0.f      )),
			applyTransform(tTagTransformations[i], cv::Point2f(tSizes[i], 0.f      )),
			applyTransform(tTagTransformations[i], cv::Point2f(tSizes[i], tSizes[i])),
			applyTransform(tTagTransformations[i], cv::Point2f(0.f      , tSizes[i])),
		};
	}

	cv::Matx33f tCamera = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1,
	};
	cv::Mat_<float>tDistortion (5,1);
	tDistortion << 0.f, 0.f, 0.f, 0.f, 0.f;
	chilitags::Objects tObjects(tCamera, tDistortion, std::string(
		cvtest::TS::ptr()->get_data_path())
		+"misc/markers_configuration_sample.yml");

	auto tResult = tObjects(tTags);
	EXPECT_EQ(2, tResult.size());

	auto tResultIt = tResult.cbegin();
	std::vector<std::string> tExpectedNames = {"marker_2", "myobject3"};
	std::vector<cv::Matx44f> tExpectedTransformations = {
		tTagTransformations[0],
		tObjectTransformation};
	for (int i = 0; i<tExpectedNames.size(); ++i) {
		EXPECT_EQ(tExpectedNames[i], tResultIt->first);

		cv::Matx44f tActualTransformation = tResultIt->second;
		EXPECT_GT(1e-3, cv::norm(tActualTransformation-tExpectedTransformations[i]))
			<< "For:" << tExpectedNames[i]
			<< "\nExpected:\n" << cv::Mat(tExpectedTransformations[i])
			<< "\nActual:\n" << cv::Mat(tActualTransformation);

		++tResultIt;
	}
}

CV_TEST_MAIN(".")
