package ch.epfl.chili.chilitags.samples.estimate3d_gui;

import ch.epfl.chili.chilitags.Chilitags3D;
import android.os.Bundle;
import android.app.Activity;

public class Estimate3DGUIActivity extends Activity {
	
	private CameraController camController; //The camera controller object that holds the device camera object and 
	private Chilitags3D chilitags; //The chilitags object
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		//Create and initialize the camera controller
		camController = new CameraController();
		camController.onStart();

		//Create the Chilitags object (which also creates its native counterpart)
		//The default Android camera color space is YUV_NV21
		chilitags = new Chilitags3D(camController.cameraWidth,camController.cameraHeight,
				camController.processingWidth,camController.processingHeight,Chilitags3D.InputType.YUV_NV21); 
		
		//A simple camera calibration based on a lot of assumptions
		double[] cc = {
				270,	0,		camController.processingWidth/2,
				0,		270,	camController.processingHeight/2,
				0,		0,		1}; 
		double[] dc = {};
		chilitags.setCalibration(cc,dc);
	
		//Create the surface that we will draw on using GLES 2.0
		setContentView(new CameraPreviewGLSurfaceView(this,camController,chilitags,cc,
				(double)camController.cameraWidth/camController.processingWidth,
				(double)camController.cameraHeight/camController.processingHeight));
	}
	
	@Override
	protected void onStart(){
		super.onStart();
		camController.onStart();
	}
	
	@Override
	protected void onResume(){
		super.onResume();
		camController.onResume();
	}
	
	@Override
	protected void onPause(){
		super.onPause();
		camController.onPause();
	}
	
	@Override
	protected void onStop(){
		super.onStop();
		camController.onStop();
	}
}
