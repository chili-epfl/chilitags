package ch.epfl.chili.chilitags.samples.estimate3d_gui;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import ch.epfl.chili.chilitags.samples.estimate3d_gui.shader.LineShader;
import ch.epfl.chili.chilitags.samples.estimate3d_gui.shader.Shader;
import android.opengl.GLES20;

public class GLESLine {

	private FloatBuffer vertexBuffer; //The vertex buffer

	private Shader shader; //Our line shader that paints the pixels on the line
	
	protected int positionHandle; //The handle to the a_position  attribute
	protected int colorHandle; //The handle to the v_color uniform

	//The line coordinate array
	static float lineCoords[] = {
		0.0f, 0.0f,	//Line end 1
		1.0f, 0.0f	//Line end 2
	};

	//The line color
	float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	/**
	 * Creates a new GLES line object.
	 */
	public GLESLine(){

		//Create out line shader
		shader = new LineShader();
		
		//Allocate space for our line coordinates in native space instead of JVM heap
		ByteBuffer buf = ByteBuffer.allocateDirect(4*4);
		buf.order(ByteOrder.nativeOrder());

		//Get the float buffer that will contain the line coordinates
		vertexBuffer = buf.asFloatBuffer();
		vertexBuffer.put(lineCoords);
		vertexBuffer.position(0);
	}

	/**
	 * Sets the vertices that describe the ends of this line.
	 * 
	 * @param x0 The X coordinate of one end
	 * @param y0 The Y coordinate of one end
	 * @param x1 The X coordinate of the other end
	 * @param y1 The Y coordinate of the other end
	 */
	public void setVerts(float x0, float y0, float x1, float y1){
		lineCoords[0] = x0;
		lineCoords[1] = y0;
		lineCoords[2] = x1;
		lineCoords[3] = y1;

		vertexBuffer.put(lineCoords);
		vertexBuffer.position(0);
	}

	/**
	 * Sets the color of this line.
	 * 
	 * @param red The red component
	 * @param green The green component
	 * @param blue The blue component
	 * @param alpha The alpha component
	 */
	public void setColor(float red, float green, float blue, float alpha){
		color[0] = red;
		color[1] = green;
		color[2] = blue;
		color[3] = alpha;
	}

	/**
	 * Begins the usage of this line in the GL context.
	 */
	public void load(){
		
		shader.load();
	}

	/**
	 * Draws this line.
	 */
	public void draw() { 

		//Use our shader
		shader.begin();

		//Get the handle to the a_position attribute of our shader code
		positionHandle = GLES20.glGetAttribLocation(shader.getHandle(), "a_position");

		//Load our attribute array to the shader
		GLES20.glEnableVertexAttribArray(positionHandle);
		GLES20.glVertexAttribPointer(positionHandle, 2, GLES20.GL_FLOAT, false, 2*4, vertexBuffer);

		//Get the handle to the v_color uniform of our shader code
		colorHandle = GLES20.glGetUniformLocation(shader.getHandle(), "v_color");

		//Set color to the v_color uniform
		GLES20.glUniform4fv(colorHandle, 1, color, 0);

		//Draw the actual line
		GLES20.glDrawArrays(GLES20.GL_LINES, 0, 2);

		//Unload our vertex array
		GLES20.glDisableVertexAttribArray(positionHandle);
	}

	/**
	 * Multiplies a 4x4 matrix by a 4-vector (from left).
	 * 
	 * @param mat The 4x4 matrix
	 * @param vec The 4-vector
	 * @return The result, i.e mat*vec
	 */
	public static double[] multiply(double[][] mat, double[] vec){
		double[] res = new double[4];

		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				res[i] += mat[i][j]*vec[j];

		return res;
	}
}