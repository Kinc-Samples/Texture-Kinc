#ifdef GL_ES
precision mediump float;
#endif

varying vec2 texcoord;

uniform sampler2D sampler;

void main() {
	vec4 color = texture2D(sampler, texcoord);
	gl_FragColor = vec4(color.r, color.g, color.b, 1.0);
}
