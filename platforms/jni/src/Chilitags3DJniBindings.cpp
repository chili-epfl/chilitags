/*******************************************************************************
 *   Copyright 2014 EPFL                                                        *
 *                                                                              *
 *   This file is part of chilitags.                                            *
 *                                                                              *
 *   Chilitags is free software: you can redistribute it and/or modify          *
 *   it under the terms of the Lesser GNU General Public License as             *
 *   published by the Free Software Foundation, either version 3 of the         *
 *   License, or (at your option) any later version.                            *
 *                                                                              *
 *   Chilitags is distributed in the hope that it will be useful,               *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 *   GNU Lesser General Public License for more details.                        *
 *                                                                              *
 *   You should have received a copy of the GNU Lesser General Public License   *
 *   along with Chilitags.  If not, see <http://www.gnu.org/licenses/>.         *
 *******************************************************************************/

#include <jni.h>
#include <string>
#include <unistd.h>
#include <opencv2/imgproc/imgproc.hpp>

#include "chilitags.hpp"

#define JNI(RETURN_TYPE,NAME) extern "C" JNIEXPORT RETURN_TYPE JNICALL Java_ch_epfl_chili_chilitags_Chilitags3D_##NAME
#define GET_OBJ(X) reinterpret_cast<chilitags::Chilitags3D*>(X)
#define GET_PTR(X) reinterpret_cast<jlong>(X)

static int Chilitags3D_height = -1;
static int Chilitags3D_width = -1;
static int Chilitags3D_processingHeight = -1;
static int Chilitags3D_processingWidth = -1;
static int Chilitags3D_inputType = -1;
static cv::Mat Chilitags3D_grayscale;
static cv::Mat Chilitags3D_downsampled;

JNI(jlong,alloc)(JNIEnv* env, jclass* class_, jint width, jint height, jint processingWidth, jint processingHeight, jint inputType){
	Chilitags3D_height = height;
	Chilitags3D_width = width;
	Chilitags3D_processingHeight = processingHeight;
	Chilitags3D_processingWidth = processingWidth;
	Chilitags3D_inputType = inputType;
	switch(inputType){
	case 0: //YUV_NV21
	case 1: //RGB565
	case 2: //RGB888
		Chilitags3D_grayscale = cv::Mat(Chilitags3D_height,Chilitags3D_width,CV_8UC1);
		Chilitags3D_downsampled = cv::Mat(Chilitags3D_processingHeight,Chilitags3D_processingWidth,CV_8UC1);
		break;

	default:
		env->ThrowNew(env->FindClass("java/lang/Exception"), "Chilitags3D: inputType not supported.");
		return 0;
	}
	return GET_PTR(new chilitags::Chilitags3D(cv::Size(processingWidth,processingHeight)));
}

JNI(void,free)(JNIEnv* env, jclass* class_, jlong ptr){
	Chilitags3D_height = -1;
	Chilitags3D_width = -1;
	Chilitags3D_processingHeight = -1;
	Chilitags3D_processingWidth = -1;
	delete GET_OBJ(ptr);
}

JNI(void,readTagConfigurationImpl)(JNIEnv* env, jclass* class_, jlong ptr, jstring filename, jboolean omitOtherTags){
	GET_OBJ(ptr)->readTagConfiguration(env->GetStringUTFChars(filename, 0),omitOtherTags);
}

JNI(jobject,readCalibrationImpl)(JNIEnv* env, jclass* class_, jlong ptr, jstring filename){
	cv::Size size = GET_OBJ(ptr)->readCalibration(env->GetStringUTFChars(filename, 0));

	//Get class of CV::Size java wrapper
	jclass cls = env->FindClass("ch/epfl/chili/chilitags/CVSize");

	//Get constructor
	jmethodID constructor = env->GetMethodID(cls,"<init>","()V");

	//Get fields
	jfieldID heightID = env->GetFieldID(cls,"height","I");
	jfieldID widthID = env->GetFieldID(cls,"width","I");

	//Create and fill wrapper
	jobject result = env->NewObject(cls,constructor);
	env->SetIntField(result,heightID,size.height);
	env->SetIntField(result,widthID,size.width);

	return result;
}

JNI(void,setCalibrationImpl)(JNIEnv* env, jclass* class_, jlong ptr, jdoubleArray cameraMatrix, jdoubleArray distortionCoeffs){

	//Get camera matrix buffer from parameters
	jdouble* jcammatBuffer = env->GetDoubleArrayElements(cameraMatrix,0);
	double* cammatBuffer = reinterpret_cast<double*>(jcammatBuffer);

	//TODO: If we don't initialize the cv::Mat like this, 3D estimate doesn't work: returns NaN or 0.0 on all entries of the
	//transform. For example, cv::Mat cammat(3,3,CV_64F,cammatBuffer) doesn't work, even though all entries, type and sizes
	//are the same with the original camera matrix, I really don't know why.
	cv::Mat cammat = (cv::Mat_<double>(3,3) <<
			cammatBuffer[0], cammatBuffer[1], cammatBuffer[2],
			cammatBuffer[3], cammatBuffer[4], cammatBuffer[5],
			cammatBuffer[6], cammatBuffer[7], cammatBuffer[8]);
	cv::InputArray cammatArray(cammat);

	//Get distortion coefficients from parameters
	int len = env->GetArrayLength(distortionCoeffs);
	jdouble* jdistcoeffsBuffer;
	if(len>0){
		jdistcoeffsBuffer = env->GetDoubleArrayElements(distortionCoeffs,0);
		double* distcoeffsBuffer = reinterpret_cast<double*>(jdistcoeffsBuffer);

		//TODO: The following line probably won't work due to the above reason
		cv::Mat distcoeffsmat(len,1,CV_64F,distcoeffsBuffer);
		cv::InputArray distcoeffsArray(distcoeffsmat);

		GET_OBJ(ptr)->setCalibration(cammatArray,distcoeffsArray);
	}
	else{
		cv::InputArray distcoeffsArray(cv::Mat(0,0,CV_64FC1));
		GET_OBJ(ptr)->setCalibration(cammatArray,distcoeffsArray);
	}

	//Unpin the parameter arrays in the JVM heap
	env->ReleaseDoubleArrayElements(cameraMatrix,jcammatBuffer,0);
	if(len>0)
		env->ReleaseDoubleArrayElements(distortionCoeffs,jdistcoeffsBuffer,0);
}

JNI(jobjectArray,estimateImpl)(JNIEnv* env, jclass* class_, jlong ptr, jbyteArray imageData, jint detectionTrigger){

	//Get a pointer to the image data buffer inside the JVM heap by first pinning it down to prevent garbage collector from touching it
	//This doesn't cause copying the buffer to another location in the heap unless necessary: We're truly sharing memory most of the time
	jbyte* buffer = env->GetByteArrayElements(imageData,0);
	unsigned char* ubuffer = reinterpret_cast<unsigned char*>(buffer);

	//Do color space conversion and downsampling
	switch(Chilitags3D_inputType){
	case 0:{ //YUV_NV21

		//YUV_NV21 image contains 12 bits per pixel, hence the weird resolution
		cv::Mat original(Chilitags3D_height + Chilitags3D_height/2, Chilitags3D_width, CV_8UC1, ubuffer);
		cv::cvtColor(original,Chilitags3D_grayscale,cv::COLOR_YUV2GRAY_NV21);
		cv::resize(Chilitags3D_grayscale,Chilitags3D_downsampled,cv::Size(Chilitags3D_processingWidth,Chilitags3D_processingHeight));
		break;
	}
	case 1:{ //RGB565

		cv::Mat original(Chilitags3D_height, Chilitags3D_width, CV_8UC2, ubuffer);
		cv::cvtColor(original,Chilitags3D_grayscale,cv::COLOR_BGR5652GRAY); //We are actually sending RGB565 but since it's going to be grayscaled, it shouldn't be a problem
		cv::resize(Chilitags3D_grayscale,Chilitags3D_downsampled,cv::Size(Chilitags3D_processingWidth,Chilitags3D_processingHeight));
		break;
	}
	case 2:{ //RGB888

		cv::Mat original(Chilitags3D_height, Chilitags3D_width, CV_8UC3, ubuffer);
		cv::cvtColor(original,Chilitags3D_grayscale,cv::COLOR_RGB2GRAY);
		cv::resize(Chilitags3D_grayscale,Chilitags3D_downsampled,cv::Size(Chilitags3D_processingWidth,Chilitags3D_processingHeight));
		break;
	}
	}

	//Call Chilitags' estimate on the grayscale image
	auto result = GET_OBJ(ptr)->estimate(Chilitags3D_downsampled,static_cast<chilitags::Chilitags::DetectionTrigger>(detectionTrigger));

	//Unpin the image data buffer inside the JVM
	env->ReleaseByteArrayElements(imageData,buffer,0);

	/*
	 * Allocate the jobjectArray that we will return
	 */

	//Get class
	jclass cls = env->FindClass("ch/epfl/chili/chilitags/ObjectTransform");

	//Get constructor
	jmethodID constructor = env->GetMethodID(cls,"<init>","()V");

	//Get fields
	jfieldID nameID = env->GetFieldID(cls,"name","Ljava/lang/String;");
	jfieldID transformID = env->GetFieldID(cls,"transform","[[D");

	//Allocate object array
	jobjectArray jresult = env->NewObjectArray((unsigned int)result.size(),cls,NULL);

	//Get each object transform and put it inside our jobjectArray
	int i=0;
	jdouble row[4];
	for(auto pair : result){

		//Build single object
		jobject jpair = env->NewObject(cls, constructor);

		//Set object name
		env->SetObjectField(jpair, nameID, env->NewStringUTF(pair.first.c_str()));

		/*
		 * Build object transform matrix
		 */

		//Get rows of the matrix in JVM heap space, we will change them
		jobjectArray rows = reinterpret_cast<jobjectArray>(env->GetObjectField(jpair,transformID));
		jdoubleArray jrow;

		//Traverse rows
		for(int j=0;j<4;j++){

			//Traverse columns
			for(int k=0;k<4;k++){

				//Set current element of the matrix accordingly
				row[k] = pair.second(j,k);
			}

			//Temporarily allocate a new row in JVM heap space (no need to unpin an array allocated with New...Array in the end)
			jrow = env->NewDoubleArray(4);

			//Fill the newly allocated row
			env->SetDoubleArrayRegion(jrow,0,4,row);

			//Write the newly filled row to the appropriate row of our matrix
			env->SetObjectArrayElement(rows,j,jrow);
		}

		//Put it in final result array
		env->SetObjectArrayElement(jresult,i,jpair);
		i++;
	}

	return jresult;
}

JNI(void,setPerformancePresetImpl)(JNIEnv* env, jclass* class_, jlong ptr, jint preset){
	switch(preset){
	case 0: //FASTER
		GET_OBJ(ptr)->getChilitags().setPerformance(chilitags::Chilitags::FASTER);
		break;
	case 1: //FAST
		GET_OBJ(ptr)->getChilitags().setPerformance(chilitags::Chilitags::FAST);
		break;
	case 2: //ROBUST
		GET_OBJ(ptr)->getChilitags().setPerformance(chilitags::Chilitags::ROBUST);
		break;
	default: //UNKNOWN PRESET
		env->ThrowNew(env->FindClass("java/lang/Exception"), "Chilitags3D: performancePreset unknown.");
		break;
	}
}
