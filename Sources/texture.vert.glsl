attribute vec3 pos;
attribute vec2 tex;

varying vec2 texcoord;
uniform mat4 matrix;

void kore() {
	gl_Position = matrix * vec4(pos.x, pos.y, 0.5, 1.0);
	texcoord = tex;
}
