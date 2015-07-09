attribute vec3 pos;
attribute vec2 tex;

varying vec2 texcoord;
uniform mat3 matrix;

void kore() {
	gl_Position = vec4(matrix * vec3(pos.x, pos.y, 0.5), 1.0);
	texcoord = tex;
}
