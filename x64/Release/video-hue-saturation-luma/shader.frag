#version 130

in vec2 T;

uniform sampler2D diffuse;
uniform vec4 hsya;

float f(float a) { return clamp(6.0*abs(fract(a)-0.5)-1.0,0.0,1.0); }
vec3 vmax(vec3 v) {
    float m = max(max(v.x, v.y), v.z); vec3 ret;
    ret.x = float(m == v.x); ret.y = float(m == v.y) * (1.0 - ret.x); ret.z = float(m == v.z) * (1.0 - ret.x - ret.y);
    return ret;
}
vec3 Y = vec3(0.2126, 0.7152, 0.0722);

vec3 colluma(float h, float y) {
    float e = 1.0e-16;
    vec3 c = vec3(f(h), f(h - 0.3333333), f(h - 0.6666667));
    float cy = dot(c, Y);
    vec3 top = (vec3(1.0) - c) / (1.0 - cy + e);
    vec3 bottom = c / (cy + e);
    vec3 slope = mix(bottom, top, float(y >= cy));
    vec3 base = c - slope * cy;
    return clamp(slope * y + base, vec3(0), vec3(1));
}

vec3 hsy2rgb(vec3 c) {
    vec3 huelum = colluma(c.x, c.z);
    vec3 gray = vec3(c.z);
    return mix(gray, huelum, c.y);
}

vec3 rgb2hsy(vec3 c) {
    vec3 hsy;
    hsy.z = dot(c, Y);
    float e = 1.0e-16;
    float V = max(max(c.r, c.g), c.b), V_ = min(min(c.r, c.g), c.b), C = (V - V_);
    vec3 h = vec3(mod((c.g-c.b)/(C+e),6.0), 2.0 + (c.b-c.r)/(C+e), 4.0 + (c.r-c.g)/(C+e));
    hsy.x = dot(h, vmax(c)) * 0.1666666;
    vec3 hy = colluma(hsy.x, hsy.z);
    vec3 gray = vec3(hsy.z);
    vec3 invlerp = (clamp((c - gray) / (hy - gray + e), 0.0, 1.0));
    hsy.y = max(max(invlerp.x, invlerp.y), invlerp.z);
    return hsy;
}

void main() {  
	vec4 color = texture2D(diffuse, T);
	vec3 hsy = rgb2hsy(color.rgb);
	hsy.x = fract(hsya.x + hsy.x);
	hsy.y = clamp(hsy.y * hsya.y, 0.0, 1.0);
	hsy.z = clamp(hsy.z * hsya.z, 0.0, 1.0);
	gl_FragColor = vec4(hsy2rgb(hsy), color.a);
}