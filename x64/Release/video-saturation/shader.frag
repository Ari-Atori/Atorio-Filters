#version 130

in vec2 T;

uniform sampler2D diffuse;
uniform float saturation;

const vec3 Y = vec3(0.2126, 0.7152, 0.0722);

void main() {  
	vec4 color = texture2D(diffuse, T);
	float gray = dot(color.rgb, Y);
	
	color.rgb = mix(vec3(gray), color.rgb, saturation);
	
	gl_FragColor = color;
}