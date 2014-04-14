package ch.epfl.chili.chilitags.samples.estimate3d_gui;

import ch.epfl.chili.chilitags.Chilitags3D;
import android.content.Context;
import android.opengl.GLSurfaceView;

public class CameraPreviewGLSurfaceView extends GLSurfaceView {

	/**
	 * Our GL surface. It will hold the rendered the camera image on the background and the frames of all detected tags.
	 * 
	 * @param context Current context
	 * @param camController The camera controller that holds the camera image buffer
	 * @param chilitags The Chilitags3D object that detects tags and calculates their transforms w.r.t the camera
	 * @param camCalib Camera calibration matrix that was fed to Chilitags3D
	 * @param xScale The inverse of the downscale value that was induced to the Chilitags processing image width vs. the camera image width
	 * @param yScale The inverse of the downscale value that was induced to the Chilitags processing image height vs. the camera image height
	 */
	public CameraPreviewGLSurfaceView(Context context, CameraController camController, Chilitags3D chilitags, double[] camCalib, double xScale, double yScale) {
		super(context);
		setEGLContextClientVersion(2); //We're declaring that we're using GLES 2.0
		setRenderer(new CameraPreviewRenderer(camController,chilitags,camCalib,xScale,yScale));
	}
}
