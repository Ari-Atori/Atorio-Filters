#version 130

in vec2 T;

uniform sampler2D diffuse;
uniform mat4 neutral;
uniform vec4 temptint;
uniform float lumpres;

const vec4 Y = vec4(0.2126, 0.7152, 0.0722, 0);

vec4 colluma(vec4 c, float y) {
    float e = 1.0e-16;
    float cy = dot(c, Y);
    vec4 top = (vec4(1.0) - c) / (1.0 - cy + e);
    vec4 bottom = c / (cy + e);
    vec4 slope = mix(bottom, top, float(y >= cy));
    vec4 base = c - slope * cy;
    return clamp(slope * y + base, vec4(0), vec4(1));
}

void main() {  
	vec4 color = texture2D(diffuse, T);
	float lumin = dot(Y, color);
	color = neutral * color;
	color *= temptint;
	lumin = mix(dot(color, Y), lumin, lumpres);
	color = colluma(color, lumin);
	gl_FragColor = color;
}