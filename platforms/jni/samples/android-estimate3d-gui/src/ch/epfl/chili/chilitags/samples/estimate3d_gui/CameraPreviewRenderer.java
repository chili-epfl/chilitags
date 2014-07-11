package ch.epfl.chili.chilitags.samples.estimate3d_gui;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import ch.epfl.chili.chilitags.Chilitags3D;
import ch.epfl.chili.chilitags.ObjectTransform;
import ch.epfl.chili.chilitags.samples.estimate3d_gui.shader.Shader;
import ch.epfl.chili.chilitags.samples.estimate3d_gui.shader.YUV2RGBShader;
import android.graphics.Point;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.util.Log;

public class CameraPreviewRenderer implements GLSurfaceView.Renderer {

	private CameraController camController; //The camera controller object that will provide the background image
	private Chilitags3D chilitags; //The Chilitags object that detects the tags

	//The Y and UV buffers that will pass our image channel data to the textures
	private ByteBuffer yBuffer;
	private ByteBuffer uvBuffer;

	//The Y and UV texture objects
	private int yTextureHandle;
	private int uvTextureHandle;
	private int[] yTextureNames;
	private int[] uvTextureNames;

	//Our line object
	private GLESLine line;

	//The shader program object that will do the YUV-RGB conversion for us
	private Shader yuv2rgbShader;

	private int positionHandle; //The location of the a_position attribute object
	private int texCoordHandle; //The location of the a_texCoord attribute object

	//The vertices and indices of our mesh that we will draw the camera preview image on
	private final float[] verticesData = { 
			-1.f, 1.f, // Position 0
			0.0f, 0.0f, // TexCoord 0
			-1.f, -1.f, // Position 1
			0.0f, 1.0f, // TexCoord 1
			1.f, -1.f, // Position 2
			1.0f, 1.0f, // TexCoord 2
			1.f, 1.f, // Position 3
			1.0f, 0.0f // TexCoord 3
	};
	private final short[] indicesData = { 0, 1, 2, 0, 2, 3 };
	private FloatBuffer vertices;
	private ShortBuffer indices;

	private double[][] camMat; //The camera matrix
	private double xScale; //(Camera image width)/(Chilitags processing image width)
	private double yScale; //(Camera image height)/(Chilitags processing image height)

	/**
	 * Creates a new renderer for our GL surface. It will render the camera image on the background and the frames of all detected tags.
	 * 
	 * @param camController The camera controller that holds the camera image buffer
	 * @param chilitags The Chilitags3D object that detects tags and calculates their transforms w.r.t the camera
	 * @param camCalib Camera calibration matrix that was fed to Chilitags3D
	 * @param xScale The inverse of the downscale value that was induced to the Chilitags processing image width vs. the camera image width
	 * @param yScale The inverse of the downscale value that was induced to the Chilitags processing image height vs. the camera image height
	 */
	public CameraPreviewRenderer(CameraController camController, Chilitags3D chilitags, double[] camCalib, double xScale, double yScale){
		this.camController = camController;
		this.chilitags = chilitags;

		/*
		 * GLES stuff
		 */

		//Create our shader
		yuv2rgbShader = new YUV2RGBShader();

		//Allocate vertices of our mesh on native memory space
		vertices = ByteBuffer.allocateDirect(verticesData.length * 4).order(ByteOrder.nativeOrder()).asFloatBuffer();
		vertices.put(verticesData);
		vertices.position(0);

		//Allocate indices of our mesh on native memory space
		indices = ByteBuffer.allocateDirect(indicesData.length * 2).order(ByteOrder.nativeOrder()).asShortBuffer();
		indices.put(indicesData);
		indices.position(0);

		//Allocate image channel buffers on the native memory space
		yBuffer = ByteBuffer.allocateDirect(camController.cameraWidth*camController.cameraHeight).order(ByteOrder.nativeOrder());
		uvBuffer = ByteBuffer.allocateDirect(camController.cameraWidth*camController.cameraHeight/2).order(ByteOrder.nativeOrder()); //We have (width/2*height/2) pixels, each pixel is 2 bytes

		//Allocate our line object
		line = new GLESLine();

		/*
		 * Prepare the transforms we will use
		 */

		//Get the camera matrix
		camMat = new double[4][4];
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				camMat[i][j] = camCalib[i*3+j];
		camMat[3][2] = 1; //This is for getting the Z coordinate on the last element of the vector when multiplied with the camera matrix

		//Get the scaling values
		this.xScale = xScale;
		this.yScale = yScale;
	}

	@Override
	public void onSurfaceCreated(GL10 unused, EGLConfig config) {

		/*
		 * Prepare the shader stuff
		 */
		
		//Compile and load our shaders
		yuv2rgbShader.load();
		line.load();
		
		//Get the attribute locations
		positionHandle = GLES20.glGetAttribLocation(yuv2rgbShader.getHandle(), "a_position");
		texCoordHandle = GLES20.glGetAttribLocation(yuv2rgbShader.getHandle(), "a_texCoord");

		//Create the Y texture object
		GLES20.glEnable(GLES20.GL_TEXTURE_2D);
		yTextureHandle = GLES20.glGetUniformLocation(yuv2rgbShader.getHandle(), "y_texture");
		yTextureNames = new int[1];
		GLES20.glGenTextures(1, yTextureNames, 0);

		//Create the UV texture object
		GLES20.glEnable(GLES20.GL_TEXTURE_2D);
		uvTextureHandle = GLES20.glGetUniformLocation(yuv2rgbShader.getHandle(), "uv_texture");
		uvTextureNames = new int[1];
		GLES20.glGenTextures(1, uvTextureNames, 0);

		//Clear the screen
		GLES20.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		/*
		 * Attach the dummy texture to the camera now that we have a GL context
		 */
		camController.attachDummyTexture();
	}

	@Override
	public void onSurfaceChanged(GL10 unused, int width, int height) {
		GLES20.glActiveTexture(GLES20.GL_ACTIVE_TEXTURE);
		GLES20.glViewport(0, 0, width, height);
	}

	@Override
	public void onDrawFrame(GL10 unused) {

		//Clear the screen
		GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);

		//Get the camera image
		byte[] cameraImage = camController.getPictureData();
		if(cameraImage != null){

			//Render the background that is the live camera preview
			renderBackground(cameraImage);

			//Get the 3D tag poses from Chilitags
			ObjectTransform[] tags = chilitags.estimate(cameraImage,Chilitags3D.DetectionTrigger.DETECT_PERIODICALLY);

			//Render the tags' reference frames on the image
			renderTagFrames(tags);
		}
	}

	/**
	 * Draws the tag frames as X,Y,Z arrows
	 * 
	 * @param tags The tag transforms estimated by Chilitags3D
	 */
	private void renderTagFrames(ObjectTransform[] tags){

		final double TAG_SIZE = 20.0; //The tag edges are assumed to be 20 mm
		final double[] WORLD_ARROW_ORIGIN = 	{0.0, 			0.0,		0.0,		1.0};
		final double[] WORLD_ARROW_X = 		{TAG_SIZE,		0.0,		0.0,		1.0};
		final double[] WORLD_ARROW_Y = 		{0.0,			TAG_SIZE,	0.0,		1.0};
		final double[] WORLD_ARROW_Z = 		{0.0,			0.0,		TAG_SIZE,	1.0};

		for(ObjectTransform tag : tags){

			/*
			 * Calculate line positions on the screen
			 */

			//Calculate the (unscaled) tag frame points in the screen frame: v_screen = cameraMatrix * tagTransform * v_world
			double[] screen_arrow_origin = GLESLine.multiply(camMat, GLESLine.multiply(tag.transform, WORLD_ARROW_ORIGIN));
			double[] screen_arrow_X = GLESLine.multiply(camMat, GLESLine.multiply(tag.transform, WORLD_ARROW_X));
			double[] screen_arrow_Y = GLESLine.multiply(camMat, GLESLine.multiply(tag.transform, WORLD_ARROW_Y));
			double[] screen_arrow_Z = GLESLine.multiply(camMat, GLESLine.multiply(tag.transform, WORLD_ARROW_Z));

			//Calculate the origin point on the screen frame
			Point screenPoints_origin = new Point();
			screenPoints_origin.x = (int)(xScale * screen_arrow_origin[0] / screen_arrow_origin[3]);
			screenPoints_origin.y = (int)(yScale * screen_arrow_origin[1] / screen_arrow_origin[3]);

			//Calculate the X arrow end on the screen frame
			Point screenPoints_X = new Point();
			screenPoints_X.x = (int)(xScale * screen_arrow_X[0] / screen_arrow_X[3]);
			screenPoints_X.y = (int)(yScale * screen_arrow_X[1] / screen_arrow_X[3]);

			//Calculate the Y arrow end on the screen frame
			Point screenPoints_Y = new Point();
			screenPoints_Y.x = (int)(xScale * screen_arrow_Y[0] / screen_arrow_Y[3]);
			screenPoints_Y.y = (int)(yScale * screen_arrow_Y[1] / screen_arrow_Y[3]);

			//Calculate the Z arrow end on the screen frame
			Point screenPoints_Z = new Point();
			screenPoints_Z.x = (int)(xScale * screen_arrow_Z[0] / screen_arrow_Z[3]);
			screenPoints_Z.y = (int)(yScale * screen_arrow_Z[1] / screen_arrow_Z[3]);

			/*
			 * Draw the arrows
			 */

			//Draw the X arrow
			line.setColor(1.0f, 0.0f, 0.0f, 1.0f);
			line.setVerts(
					((float)screenPoints_origin.x/camController.cameraWidth - 0.5f)*2.0f, -((float)screenPoints_origin.y/camController.cameraHeight - 0.5f)*2.0f, 
					((float)screenPoints_X.x/camController.cameraWidth - 0.5f)*2.0f, -((float)screenPoints_X.y/camController.cameraHeight - 0.5f)*2.0f);
			line.draw();

			//Draw the Y arrow
			line.setColor(0.0f, 1.0f, 0.0f, 1.0f);
			line.setVerts(
					((float)screenPoints_origin.x/camController.cameraWidth - 0.5f)*2.0f, -((float)screenPoints_origin.y/camController.cameraHeight - 0.5f)*2.0f,
					((float)screenPoints_Y.x/camController.cameraWidth - 0.5f)*2.0f, -((float)screenPoints_Y.y/camController.cameraHeight - 0.5f)*2.0f);
			line.draw();

			//Draw the Z arrow
			line.setColor(0.0f, 0.0f, 1.0f, 1.0f);
			line.setVerts(
					((float)screenPoints_origin.x/camController.cameraWidth - 0.5f)*2.0f, -((float)screenPoints_origin.y/camController.cameraHeight - 0.5f)*2.0f, 
					((float)screenPoints_Z.x/camController.cameraWidth - 0.5f)*2.0f, -((float)screenPoints_Z.y/camController.cameraHeight - 0.5f)*2.0f);
			line.draw();
		}
	}

	/**
	 * Draws the image to the background.
	 * 
	 * @param image The YUV-NV21 image to be drawn
	 */
	private void renderBackground(byte[] image){

		/*
		 * Because of Java's limitations, we can't reference the middle of an array and 
		 * we must copy the channels in our byte array into buffers before setting them to textures
		 */

		//Copy the Y channel of the image into its buffer, the first (width*height) bytes are the Y channel
		yBuffer.put(image, 0, camController.cameraWidth*camController.cameraHeight);
		yBuffer.position(0);

		//Copy the UV channels of the image into their buffer, the following (width*height/2) bytes are the UV channel; the U and V bytes are interspread
		uvBuffer.put(image, camController.cameraWidth*camController.cameraHeight, camController.cameraWidth*camController.cameraHeight/2);
		uvBuffer.position(0);

		//Use the shader program object
		yuv2rgbShader.begin();

		//Load the vertex position
		vertices.position(0);
		GLES20.glVertexAttribPointer(positionHandle, 2, GLES20.GL_FLOAT, false, 4*4, vertices);

		//Load the texture coordinate
		vertices.position(2);
		GLES20.glVertexAttribPointer(texCoordHandle, 2, GLES20.GL_FLOAT, false, 4*4, vertices);

		//Load our vertex array into the shader
		GLES20.glEnableVertexAttribArray(positionHandle);
		GLES20.glEnableVertexAttribArray(texCoordHandle);

		/*
		 * Load the Y texture
		 */

		//Set texture slot 0 as active and bind our texture object to it
		GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
		GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, yTextureNames[0]);

		//Y texture is (width*height) in size and each pixel is one byte; by setting GL_LUMINANCE, OpenGL puts this byte into R,G and B components of the texture
		GLES20.glTexImage2D(GLES20.GL_TEXTURE_2D, 0, GLES20.GL_LUMINANCE, camController.cameraWidth, camController.cameraHeight, 
				0, GLES20.GL_LUMINANCE, GLES20.GL_UNSIGNED_BYTE, yBuffer);

		//Use linear interpolation when magnifying/minifying the texture to areas larger/smaller than the texture size
		GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
		GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
		GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_CLAMP_TO_EDGE);
		GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_CLAMP_TO_EDGE);

		//Set the uniform y_texture object in the shader code to the texture at slot 0
		GLES20.glUniform1i(yTextureHandle, 0);

		/*
		 * Load the UV texture
		 */

		//Set texture slot 1 as active and bind our texture object to it
		GLES20.glActiveTexture(GLES20.GL_TEXTURE1);
		GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, uvTextureNames[0]);

		//UV texture is (width/2*height/2) in size (downsampled by 2 in both dimensions, each pixel corresponds to 4 pixels of the Y channel) 
		//and each pixel is two bytes. By setting GL_LUMINANCE_ALPHA, OpenGL puts first byte (V) into R,G and B components and of the texture
		//and the second byte (U) into the A component of the texture. That's why we find U and V at A and R respectively in the fragment shader code.
		//Note that we could have also found V at G or B as well. 
		GLES20.glTexImage2D(GLES20.GL_TEXTURE_2D, 0, GLES20.GL_LUMINANCE_ALPHA, camController.cameraWidth/2, camController.cameraHeight/2, 
				0, GLES20.GL_LUMINANCE_ALPHA, GLES20.GL_UNSIGNED_BYTE, uvBuffer);

		//Use linear interpolation when magnifying/minifying the texture to areas larger/smaller than the texture size
		GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
		GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
		GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_CLAMP_TO_EDGE);
		GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_CLAMP_TO_EDGE);

		//Set the uniform uv_texture object in the shader code to the texture at slot 1
		GLES20.glUniform1i(uvTextureHandle, 1);

		/*
		 * Actual rendering
		 */

		GLES20.glDrawElements(GLES20.GL_TRIANGLES, 6, GLES20.GL_UNSIGNED_SHORT, indices);

		//Unload our vertex array
		GLES20.glDisableVertexAttribArray(positionHandle);
		GLES20.glDisableVertexAttribArray(texCoordHandle);
	}

	/**
	 * Compiles the given shader code and returns its program handle.
	 * 
	 * @param type The type of the shader
	 * @param source The GLSL source code of the shader
	 * @return The program handle of the compiled shader
	 */
	public static int loadShader(int type, String source) {
		int shader;
		int[] compiled = new int[1];

		//Create the shader object
		shader = GLES20.glCreateShader(type);
		if(shader == 0)
			return 0;

		//Load the shader source
		GLES20.glShaderSource(shader, source);

		//Compile the shader
		GLES20.glCompileShader(shader);

		//Check the compile status
		GLES20.glGetShaderiv(shader, GLES20.GL_COMPILE_STATUS, compiled, 0);

		if(compiled[0] == 0){
			Log.e("ESShader", GLES20.glGetShaderInfoLog(shader));
			GLES20.glDeleteShader(shader);
			return 0;
		}
		return shader;
	}

	/**
	 * Compiles and links the individual shaders into a complete program and returns the program handle.
	 * 
	 * @param vertexShaderSource The vertex shader GLSL source code
	 * @param fragmentShaderSource The fragment shader GLSL source code
	 * @return The handle of the shader program
	 */
	public static int loadProgram(String vertexShaderSource, String fragmentShaderSource) {
		int vertexShader;
		int fragmentShader;
		int programObject;
		int[] linked = new int[1];

		//Load the vertex/fragment shaders
		vertexShader = loadShader(GLES20.GL_VERTEX_SHADER, vertexShaderSource);
		if(vertexShader == 0)
			return 0;

		fragmentShader = loadShader(GLES20.GL_FRAGMENT_SHADER, fragmentShaderSource);
		if(fragmentShader == 0){
			GLES20.glDeleteShader(vertexShader);
			return 0;
		}

		//Create the program object
		programObject = GLES20.glCreateProgram();

		if(programObject == 0)
			return 0;

		GLES20.glAttachShader(programObject, vertexShader);
		GLES20.glAttachShader(programObject, fragmentShader);

		//Link the program
		GLES20.glLinkProgram(programObject);

		//Check the link status
		GLES20.glGetProgramiv(programObject, GLES20.GL_LINK_STATUS, linked, 0);

		if(linked[0] == 0){
			Log.e("ESShader", "Error linking program:");
			Log.e("ESShader", GLES20.glGetProgramInfoLog(programObject));
			GLES20.glDeleteProgram(programObject);
			return 0;
		}

		//Free up no longer needed shader resources
		GLES20.glDeleteShader(vertexShader);
		GLES20.glDeleteShader(fragmentShader);

		return programObject;
	}
}
