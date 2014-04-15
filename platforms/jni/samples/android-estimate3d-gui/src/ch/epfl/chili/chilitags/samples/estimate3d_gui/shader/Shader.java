package ch.epfl.chili.chilitags.samples.estimate3d_gui.shader;

import android.opengl.GLES20;
import android.util.Log;

/**
 * Base class for a GLSL shader.
 * @author Ayberk Özgür
 */
public abstract class Shader {

	/**
	 * The GL program handle (i.e name)
	 */
	private int programHandle;

	/**
	 * Compiles and loads the shader
	 */
	public void load(){
		programHandle = loadProgram(getVertexShader(), getFragmentShader());
		getUniformHandles();
	}

	/**
	 * Gets the GL program handle (i.e name)
	 * @return The GL program handle
	 */
	public int getHandle(){
		return programHandle;
	}

	/**
	 * Loads the shader and uniforms for rendering
	 */
	public void begin(){
		
		//Load the shader program object
		GLES20.glUseProgram(getHandle());
		
		//Load the auto uniforms
		loadUniforms();
	}

	/**
	 * Loads the uniforms that can be loaded automatically without manual implementation
	 */
	protected abstract void loadUniforms();
	
	/**
	 * Gets the handles of the uniforms that can be loaded automatically without manual implementation
	 */
	protected abstract void getUniformHandles();

	/**
	 * Gets the vertex shader code
	 * @return The vertex shader code
	 */
	protected abstract String getVertexShader();

	/**
	 * Gets the fragment shader code
	 * @return The fragment shader code
	 */
	protected abstract String getFragmentShader();

	/**
	 * Compiles the given shader code and returns its program handle.
	 * 
	 * @param type The type of the shader
	 * @param source The GLSL source code of the shader
	 * @return The program handle of the compiled shader
	 */
	private static int loadShader(int type, String source) {
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
	private static int loadProgram(String vertexShaderSource, String fragmentShaderSource) {
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
