#version 130

in vec2 T;
uniform mat4 colorblindness;
uniform sampler2D diffuse;

void main() {  
	vec4 color = texture2D(diffuse, T);
	color=colorblindness*color; 
	gl_FragColor = color;
}