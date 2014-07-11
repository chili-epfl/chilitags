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

package ch.epfl.chili.chilitags;

/**
 * JNI wrapper for the native Chilitags3D class.
 * 
 * @author Ayberk Özgür
 *
 */
public class Chilitags3D {

	/**
	 * The allowed input types/color spaces.
	 */
	public enum InputType{
		YUV_NV21,
		RGB565,
		RGB888
	}

	/**
	 * Preset groups of parameters (for setPerformance()) to adjust  the
	 * compromise between processing time and accuracy of detection. 
	 */
	public enum PerformancePreset {
		FASTER, /** Favor speed over accuracy: no corner refinment, no subsampling */
		FAST, /** Balance speed and accuracy (default): corners are refined, no subsampling */
		ROBUST, /** Favor robustness over accuracy: corner are refined, input is subsampled down to 160 pixels wide */
	};

	/**
	 * Values of the parameter to tell find() how to combine tracking and full detection.
	 */
	public enum DetectionTrigger {
	    TRACK_AND_DETECT, /** First track results of the previous call to find(), then run a full detection on the same input image. */
	    DETECT_ONLY, /**Disable tracking as a complement to detection.*/
	    TRACK_ONLY, /**Perform tracking only.*/
	    DETECT_PERIODICALLY /** Periodically run a full detection, default is every 15 frames */
	}
	
	/**
	 * Load the necessary libraries in the order of dependency.
	 */
	static {
		System.loadLibrary("opencv_core");
		System.loadLibrary("opencv_imgproc");
		System.loadLibrary("opencv_highgui");
		System.loadLibrary("opencv_flann");
		System.loadLibrary("opencv_features2d");
		System.loadLibrary("opencv_calib3d");
		System.loadLibrary("opencv_video");
		System.loadLibrary("chilitags");
		System.loadLibrary("chilitags_jni_bindings");
	}

	private final long ptr; //The pointer to the native object

	/*
	 * Prototypes for the actual native functions.
	 */
	private native long alloc(int width, int height, int processingWidth, int processingHeight, int inputType);
	private native void free(long ptr);
	private native void readTagConfigurationImpl(long ptr, String filename, boolean omitOtherTags);
	private native CVSize readCalibrationImpl(long ptr, String filename);
	private native ObjectTransform[] estimateImpl(long ptr, byte[] imageData, int detectionTrigger);
	private native void setCalibrationImpl(long ptr, double[] cameraMatrix, double[] distortionCoeffs);
	private native void setPerformancePresetImpl(long ptr, int preset);

	/**
	 * Creates a new Chilitags3D object.
	 * 
	 * @param width Camera image width
	 * @param height Camera image height
	 * @param processingWidth The camera image will be downsampled to this width before tag pose estimation
	 * @param processingHeight The camera image will be downsampled to this height before tag pose estimation
	 * @param inputType The type/color space of the input
	 */
	public Chilitags3D(int width, int height, int processingWidth, int processingHeight, InputType inputType){
		ptr = alloc(width, height, processingWidth, processingHeight, inputType.ordinal());
	}

	/**
	 * Deletes the native counterpart of this Chilitags3D object.
	 */
	public void delete(){
		free(ptr);
	}

	/**
	 * Reads the tag configuration file. 
	 * 
	 * @param filename Full path to the tag configuration file
	 * @param omitOtherTags Whether to ignore tags that are not defined in the configuration file
	 */
	public void readTagConfiguration(String filename, boolean omitOtherTags){
		readTagConfigurationImpl(ptr,filename,omitOtherTags);
	}

	/**
	 * Sets the camera calibration from a file.
	 * 
	 * @param filename Full path to the calibration file
	 * @return The size of the image used to generate the calibration data
	 */
	public CVSize readCalibration(String filename){
		return readCalibrationImpl(ptr,filename);
	}

	/**
	 * Sets the camera calibration from given parameters.
	 * 
	 * @param cameraMatrix The 3x3 camera calibration matrix (linearized in row-major order)
	 * @param distortionCoeffs The distortion coefficients, up to 6 of them are allowed
	 */
	public void setCalibration(double[] cameraMatrix, double[] distortionCoeffs){
		setCalibrationImpl(ptr,cameraMatrix,distortionCoeffs);
	}

	/**
	 * Sets the performance preset.
	 * 
	 * @param preset Performance preset
	 */
	public void setPerformancePreset(PerformancePreset preset){
		setPerformancePresetImpl(ptr,preset.ordinal());
	}

	/**
	 * Estimates the 3D transforms of objects tagged with Chilitags. 
	 * Depends on the tag configuration file, set it first.
	 * 
	 * Does not use tracking.
	 * 
	 * @param imageData The image buffer, must be of size (height)x(width) and of YUV_NV21 encoding; height and width values are set during construction
	 * @return The list of transforms of the objects found in the image
	 */
	public ObjectTransform[] estimate(byte[] imageData){
		return estimateImpl(ptr,imageData,DetectionTrigger.DETECT_ONLY.ordinal());
	}
	
	/**
	 * Estimates the 3D transforms of objects tagged with Chilitags. 
	 * Depends on the tag configuration file, set it first.
	 * 
	 * @param imageData The image buffer, must be of size (height)x(width) and of YUV_NV21 encoding; height and width values are set during construction
	 * @param detectionTrigger How to use detection and tracking
	 * @return The list of transforms of the objects found in the image
	 */
	public ObjectTransform[] estimate(byte[] imageData, DetectionTrigger detectionTrigger){
		return estimateImpl(ptr,imageData,detectionTrigger.ordinal());
	}
}
