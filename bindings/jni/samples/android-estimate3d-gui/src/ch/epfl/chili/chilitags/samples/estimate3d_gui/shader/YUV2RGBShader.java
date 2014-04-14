package ch.epfl.chili.chilitags.samples.estimate3d_gui.shader;

/**
 * YUV to RGB conversion shader.
 * @author Ayberk Özgür
 */
public class YUV2RGBShader extends Shader {
	
	@Override
	protected String getVertexShader() {
		return "attribute vec4 a_position;							\n" + 
				"attribute vec2 a_texCoord;							\n" + 
				"varying vec2 v_texCoord;							\n" + 

				"void main(){										\n" + 
				"   gl_Position = a_position;						\n" + 
				"   v_texCoord = a_texCoord;						\n" +
				"}													\n";
	}

	@Override
	protected String getFragmentShader() {
		return "#ifdef GL_ES										\n" +
				"precision highp float;								\n" +
				"#endif												\n" +

				"varying vec2 v_texCoord;							\n" +
				"uniform sampler2D y_texture;						\n" +
				"uniform sampler2D uv_texture;						\n" +

				"void main (void){									\n" +
				"	float r, g, b, y, u, v;							\n" +

				//We had put the Y values of each pixel to the R,G,B components by GL_LUMINANCE, 
				//that's why we're pulling it from the R component, we could also use G or B
				"	y = texture2D(y_texture, v_texCoord).r;			\n" + 

				//We had put the U and V values of each pixel to the A and R,G,B components of the
				//texture respectively using GL_LUMINANCE_ALPHA. Since U,V bytes are interspread 
				//in the texture, this is probably the fastest way to use them in the shader
				"	u = texture2D(uv_texture, v_texCoord).a - 0.5;	\n" +									
				"	v = texture2D(uv_texture, v_texCoord).r - 0.5;	\n" +

				//The numbers are just YUV to RGB conversion constants
				"	r = y + 1.13983*v;								\n" +
				"	g = y - 0.39465*u - 0.58060*v;					\n" +
				"	b = y + 2.03211*u;								\n" +

				//We finally set the RGB color of our pixel
				"	gl_FragColor = vec4(r, g, b, 1.0);				\n" +
				"}													\n";
	}

	@Override
	protected void loadUniforms() { /*No auto uniforms*/ }

	@Override
	protected void getUniformHandles() { /*No auto uniforms*/	} 
}
