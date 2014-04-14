package ch.epfl.chili.chilitags.samples.estimate3d_gui;

import java.io.IOException;
import java.util.List;

import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.hardware.Camera.Size;
import android.opengl.GLES20;

public class CameraController implements Camera.PreviewCallback {

	private static byte[] image = null; //The image buffer that will hold the camera image when preview callback arrives

	private Camera camera = null; //The camera object

	//The camera image size
	public int cameraWidth = -1;
	public int cameraHeight = -1;

	//The image size that Chilitags will deal with
	public int processingWidth = -1; 
	public int processingHeight = -1;

	//Dummy surface texture
	SurfaceTexture surf;

	/**
	 * Initializes the camera
	 */
	public void onStart(){
		
		//Only open the camera if it's not already open
		if(camera != null)
			return;
		
		//(Try to) Open the rear camera
		camera = Camera.open(0);

		//Tell the camera to call us when a preview is ready
		camera.setPreviewCallbackWithBuffer(this);

		//Set image size during preview
		Camera.Parameters params = camera.getParameters();
		List<Size> sizeList = params.getSupportedVideoSizes(); //We don't get the preferred preview size because it somehow is a 4:3 size on a 16:9 camera
		if(sizeList != null){
			Size[] sizes = sizeList.toArray(new Size[sizeList.size()]);
			cameraWidth = sizes[0].width;
			cameraHeight = sizes[0].height;
		}
		else{ //We might be on the emulator, set a very generic size that is 640x480
			cameraWidth = 640;
			cameraHeight = 480;
		}
		params.setPreviewSize(cameraWidth,cameraHeight); 

		//Our YUV image is 12 bits per pixel
		if(image == null)
			image = new byte[cameraHeight*cameraWidth/8*12];

		//Tell camera to autofocus continuously
		params.setFocusMode(Camera.Parameters.FOCUS_MODE_CONTINUOUS_VIDEO);

		//Set the parameters
		camera.setParameters(params);

		//Chilitags is too slow for HD so we downsample the image to a more reasonable size
		processingWidth = cameraWidth > 640 ? 640 : cameraWidth;
		processingHeight = cameraHeight * processingWidth / cameraWidth;
	}

	/**
	 * Starts the preview
	 */
	public void onResume() {
		startPreview();
	}

	/**
	 * Stops the preview and detaches the dummy texture
	 */
	public void onPause() {
		detachDummyTexture();
		stopPreview();
	}

	/**
	 * Releases the camera
	 */
	public void onStop() {
		camera.release();
		camera = null;
	}
	
	/**
	 * Gets the camera image.
	 * 
	 * @return The latest camera image
	 */
	public byte[] getPictureData() {
		return image;
	}

	@Override
	public void onPreviewFrame(byte[] data, Camera camera) {

		//Dummy surface texture update
		if(surf != null)
			surf.updateTexImage();

		//Send the buffer reference to the next preview so that a new buffer is not allocated and we use the same space
		camera.addCallbackBuffer(image);
	}

	/**
	 * Starts the preview; requires an OpenGL context for dummy texture creation
	 */
	public void startPreview(){
		camera.startPreview();

		//Set the first buffer, the preview doesn't start unless we set the buffers
		camera.addCallbackBuffer(image);
	}

	/**
	 * Stops the preview and frees the camera
	 */
	public void stopPreview(){
		camera.stopPreview();
		camera.setPreviewCallbackWithBuffer(null);
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
}
