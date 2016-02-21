attribute vec3 pos;
attribute vec2 tex;

varying vec2 texcoord;
uniform mat3 mvp;

void kore() {
	gl_Position = vec4(mvp * vec3(pos.x, pos.y, 0.5), 1.0);
	texcoord = tex;
}
