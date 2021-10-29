#version 130

in vec2 T;

const float epsilon = 1.00000011920928955F;

uniform sampler2D diffuse;
uniform float cslope;
uniform float pivot;

void main() {
	vec4 color = texture2D(diffuse, T);
	gl_FragColor = vec4(cslope * (color.rgb - pivot) + pivot, color.a);
}
