#include "core/Packet.hpp"

mat4 scale(float sx, float sy) {
	mat4 m = MAT4_IDENTITY;

	m(0, 0) = sx;
	m(1, 1) = sy;

	return m;
}

mat4 rotate(float a) {
	mat4 m = MAT4_IDENTITY;

	m(0, 0) = cos(a);
	m(1, 0) = -sin(a);
	m(1, 1) = cos(a);
	m(0, 1) = sin(a);

	return m;
}

mat4 skew(float kx, float ky) {
	mat4 m = MAT4_IDENTITY;

	m(1, 0) = tan(kx);
	m(0, 1) = tan(ky);

	return m;
}

mat4 translate(float tx, float ty) {
	mat4 m = MAT4_IDENTITY;

	m(3, 0) = tx;
	m(3, 1) = ty;

	return m;
}

void __declspec(dllexport) __stdcall transform_compute(size_t sz, void* v) {
	Packet& pin = (*(Packet*)v)["in"];
	Packet& pout = (*(Packet*)v)["out"];

	const float D2R = 0.01745329251F;

	mat4 S = scale(pin["sx"].value.f, pin["sy"].value.f);
	mat4 K = skew(pin["kx"].value.f * D2R, pin["ky"].value.f * D2R);
	mat4 R = rotate(pin["r"].value.f * D2R);
	mat4 T = translate(pin["tx"].value.f, pin["ty"].value.f);

	pout["transform"].value.m4 = T * R * K * S;
}