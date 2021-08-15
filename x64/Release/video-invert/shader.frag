#version 130

in vec2 T;

uniform sampler2D diffuse;

void main() {  
	vec4 color = texture2D(diffuse, T);
	color.rgb= vec3(1)-color.rgb;
	gl_FragColor = color;
}