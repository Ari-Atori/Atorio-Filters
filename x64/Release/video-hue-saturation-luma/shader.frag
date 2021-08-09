#version 130

in vec2 T;

uniform sampler2D diffuse;
uniform vec4 hsya;

void main() {  
	vec4 color = texture2D(diffuse, T);
	color.r += hsya.x;
	gl_FragColor = color;
}