attribute vec3 pos;
attribute vec2 tex;

varying vec2 texcoord;
uniform float offset;

void kore() {
	gl_Position = vec4(pos.x + offset, pos.y, 0.5, 1.0);
	texcoord = tex;
}
