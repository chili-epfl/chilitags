package ch.epfl.chili.chilitags.samples.estimate3d;

import ch.epfl.chili.chilitags.Chilitags3D;
import ch.epfl.chili.chilitags.ObjectTransform;
import android.hardware.Camera;
import android.os.Bundle;
import android.widget.TextView;
import android.app.Activity;

public class Estimate3DActivity extends Activity implements Camera.PreviewCallback  {

	TextView info;
	Camera camera;
	Chilitags3D chilitags;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_chilitags_sample_estimate3d);

		info = (TextView)findViewById(R.id.info);


		/*
		 * Set up the camera
		 */

		//Open the rear camera
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
		chilitags = new Chilitags3D(preferredSize.width,preferredSize.height,
				processingWidth,processingHeight,Chilitags3D.InputType.YUV_NV21); 

		//A simple camera calibration based on a lot of assumptions
		double[] cc = {
				540*processingWidth/preferredSize.width,	0,											processingWidth/2,
				0,											540*processingHeight/preferredSize.height,	processingHeight/2,
				0,											0,											1}; 
		double[] dc = {};
		chilitags.setCalibration(cc,dc);

		/*
		 * Finally, start camera preview
		 */

		camera.startPreview();
	}

	@Override
	public void onPreviewFrame(byte[] data, Camera camera) {

		//Run 3D estimation on the camera image
		ObjectTransform[] results = chilitags.estimate(data); 

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

	@Override
	public void onDestroy(){
		super.onDestroy();
		camera.stopPreview();
		camera.setPreviewCallback(null);
		camera.release();
	}

	private double roundToOneDP(double input){
		return Math.round(input*10)/10.0;
	}
}
