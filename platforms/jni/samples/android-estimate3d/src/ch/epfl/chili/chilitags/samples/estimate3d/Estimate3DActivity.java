package ch.epfl.chili.chilitags.samples.estimate3d;

import java.io.IOException;

import ch.epfl.chili.chilitags.Chilitags3D;
import ch.epfl.chili.chilitags.ObjectTransform;
import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.opengl.GLES20;
import android.os.Bundle;
import android.widget.TextView;
import android.app.Activity;

public class Estimate3DActivity extends Activity implements Camera.PreviewCallback  {

	TextView info;
	Camera camera = null;
	Chilitags3D chilitags = null;

	//Dummy surface texture
	SurfaceTexture surf;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_chilitags_sample_estimate3d);

		info = (TextView)findViewById(R.id.info);
	}

	@Override
	protected void onStart(){
		super.onStart();

		/*
		 * Set up the camera
		 */

		//Open the rear camera
		if(camera == null){
			camera = Camera.open(0);

			//Tell the camera to call us when a preview is ready
			camera.setPreviewCallback(this);

			//Set image size during preview
			Camera.Parameters params = camera.getParameters();
			Camera.Size preferredSize = params.getPreferredPreviewSizeForVideo();
			if(preferredSize == null) //We might be on the emulator, set a very generic size that is 640x480
				preferredSize = camera.new Size(640, 480);
			params.setPreviewSize(preferredSize.width,preferredSize.height); 

			//Tell camera to autofocus continuously
			params.setFocusMode(Camera.Parameters.FOCUS_MODE_CONTINUOUS_VIDEO);

			//Set the parameters
			camera.setParameters(params);

			/*
			 * Set up Chilitags
			 */

			//Chilitags is too slow for trueHD (1280x720) so we downsample the image to a more reasonable size
			int processingWidth = preferredSize.width > 640 ? 640 : preferredSize.width;
			int processingHeight = preferredSize.height * processingWidth / preferredSize.width;

			//Create the Chilitags object (which also creates its native counterpart)
			//The default Android camera color space is YUV_NV21
			if(chilitags == null){
				chilitags = new Chilitags3D(preferredSize.width,preferredSize.height,
						processingWidth,processingHeight,Chilitags3D.InputType.YUV_NV21); 

				//A simple camera calibration based on a lot of assumptions
				double[] cc = {
						270,										0,											processingWidth/2,
						0,											270,	processingHeight/2,
						0,											0,											1}; 
				double[] dc = {};
				chilitags.setCalibration(cc,dc);
			}
		}
	}

	@Override
	protected void onResume(){
		super.onResume();
		camera.startPreview();
	}

	@Override
	protected void onPause(){
		super.onPause();
		detachDummyTexture();
		camera.stopPreview();
	}

	@Override
	protected void onStop(){
		super.onStop();
		camera.release();
		camera = null;
	}

	@Override
	public void onPreviewFrame(byte[] data, Camera camera) {

		//Dummy surface texture update
		if(surf != null)
			surf.updateTexImage();

		//Run 3D estimation on the camera image
		ObjectTransform[] results = chilitags.estimate(data,Chilitags3D.DetectionTrigger.DETECT_PERIODICALLY); 

		//Report transform matrices of found tags
		if(results.length > 0){
			String infos = "Found " + results.length + " tag(s):\n\n";

			for(int i=0;i<results.length;i++){
				infos += results[i].name + " at:\n";
				for(int y=0;y<4;y++){
					for(int x=0;x<4;x++)
						infos += roundToOneDP(results[i].transform[y][x]) + " ";
					infos += "\n";
				}
				infos += "\n";
			}

			info.setText(infos);
		}
		else
			info.setText("Found no tags.");
	}

	/**
	 * Attaches a dummy texture to the camera; the preview won't start otherwise on some devices.
	 * We need a GL context in order to call this!
	 */
	public void attachDummyTexture(){
		if(surf == null){
			int[] dummyTex = new int[1];
			GLES20.glGenTextures(1, dummyTex, 0);
			surf = new SurfaceTexture(dummyTex[0]);
			try {
				camera.setPreviewTexture(surf);
			} catch (IOException e) {e.printStackTrace();}
		}
	}

	/**
	 * Detaches the dummy texture to free GPU memory
	 */
	public void detachDummyTexture(){
		if(surf != null){
			surf.detachFromGLContext();
			surf = null;
		}
	}	

	private double roundToOneDP(double input){
		return Math.round(input*10)/10.0;
	}
}
