package ch.epfl.chili.chilitags.samples.estimate3d_gui.shader;

/**
 * Simple line shader, paints all of the interpolated pixels the same color
 * @author Ayberk Özgür
 */
public class LineShader extends Shader {
	
	@Override
	protected String getVertexShader() {
		return "attribute vec4 a_position;		\n" +
				"void main() {					\n" +
				"  gl_Position = a_position;	\n" +
				"}								\n";
	}

	@Override
	protected String getFragmentShader() {
		return "#ifdef GL_ES					\n" +
				"precision highp float;			\n" +
				"#endif							\n" +
				"uniform vec4 v_color;			\n" +
				"void main() {					\n" +
				"  gl_FragColor = v_color;		\n" +
				"}								\n";
	}

	@Override
	protected void loadUniforms() { /*No auto uniforms*/ }

	@Override
	protected void getUniformHandles() { /*No auto uniforms*/ } 
}
