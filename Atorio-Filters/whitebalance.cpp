#include "core/Packet.hpp"

//TODO: Create better matrix to handle fully saturated colors

//{ { {0.422725, 0.491345, 0.027358, 0}, {0.055700, 0.961534, 0.023184, 0}, {0.021383, 0.087642, 0.980508, 0}, {0, 0, 0, 1}}}
//{ { {2.538047, -1.293278, 10.040237, 0}, {-0.146005, 1.116649, -0.022329, 0},{-0.042299, 0.071607, 1.022753, 0},{0, 0, 0, 1}}}
static vec3 srgb2lrgb(vec3 c) {
	c.x = (c.x <= 0.04045F) ? c.x * 0.0773993808F : (float) pow((c.x + 0.055) * 0.94786729857, 2.4);
	c.y = (c.y <= 0.04045F) ? c.y * 0.0773993808F : (float) pow((c.y + 0.055) * 0.94786729857, 2.4);
	c.z = (c.z <= 0.04045F) ? c.z * 0.0773993808F : (float) pow((c.z + 0.055) * 0.94786729857, 2.4);
	return c;
}

static mat4 neutral(vec3 c) {
	c = srgb2lrgb(c);
	vec4 color = { c.x, c.y, c.z, 1.0F };
	vec3 y = { .2126F, .7152F, .0722F };
	float luma = c | y; //allows grey tones not just white
	//point=point / luma;
	vec4 grey = { luma, luma, luma, 1 };

	mat4 total = MAT4_IDENTITY;
	static mat4 rgb2lms = { { {0.422725, 0.491345, 0.027358, 0}, {0.055700, 0.961534, 0.023184, 0}, {0.021383, 0.087642, 0.980508, 0}, {0, 0, 0, 1}} };
	static mat4 lms2rgb = { { {2.538047, -1.293278, -0.040237, 0}, {-0.146005, 1.116649, -0.022329, 0},{-0.042299, -0.071607, 1.022753, 0},{0, 0, 0, 1}} };

	vec4 greylms = rgb2lms * grey;
	vec4 colorlms = rgb2lms * color;

	total.c[0][0] = greylms.x / colorlms.x;
	total.c[1][1] = greylms.y / colorlms.y;
	total.c[2][2] = greylms.z / colorlms.z;//changing to 1/n as per

	total = lms2rgb * total * rgb2lms;//changes to lms
	return total;
}

static vec4 temp(float K) {
    vec4 color = { 0, 0, 0, 1 };
    if (K < 1000.0F) {
        return { 1.0F, .03133630F, 0.0F, 1.0F };
    }
    if (K > 40000.0F) {
        return { 0.3567632F, 0.4747332F, 1.0F, 1.0F };
    }
    if (K > 6700.0F) {
        color.x = (float) (36331.1572487 * (pow(K - 2697.65116524, -1.31345819667)) + 0.32083009448);
        color.y = (float) (21477.5773003 * (pow(K - 1919.02861119, -1.25528592041)) + 0.436548753055);
        color.z = 1.0F;
    }
    else {
        color.x = 1.0F;
        color.y = (float) (((-2.7758028321e-13 * K - 1.4735072824e-8) * K + 0.000289782192499) * K - 0.244725078766);
        color.z = (K <= 1900) ? 0.0F : (float)(((-6.0309557064e-12 * K + 8.9308429292e-8) * K - 0.000188417180468) * K + 0.067391230594);
    }
	return color;
}

float min(float x, float y) {
	return x < y ? x : y;
}

static vec4 tint(float t) {
	vec4 v;
	v.w = 1;
	v.x = min(1.0F - t, 1.0F);
	v.y = min(1.0F + t, 1.0F);
	v.z = min(1.0F - t, 1.0F);
	return v;
}

void __declspec(dllexport) __stdcall whitebalance_compute(size_t sz, void* v) {
	Packet& pin = (*(Packet*)v)["in"];
	Packet& pout = (*(Packet*)v)["out"];

	pout["neutral"].value.m4 = neutral(pin["neutral"].value.v3);
	pout["lumpres"].value.f = pin["lumpres"].value.f;
	pout["temptint"].value.v4 = temp(pin["temp"].value.f) * tint(pin["tint"].value.f);
}