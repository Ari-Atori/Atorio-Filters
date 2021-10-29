#version 130

in vec4 position;
in vec2 texture;

out vec2 T;

uniform mat4 transform;

void main() {
	T = texture;
	gl_Position = transform * position;
}