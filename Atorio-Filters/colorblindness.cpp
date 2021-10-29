#include "core/Packet.hpp"
//radio

static mat4 colorblindness(float a, int cvd) {
	mat4 i = MAT4_IDENTITY;
	mat4 m;
	switch (cvd) {
	case 1: // protan
		m =  { {{0.17055699, 0.82944301, 0, 0}, {0.17055699, 0.82944301, 0, 0}, {-0.00451714, 0.00451714, 1, 0}, {0,0,0,1}} };
		break;
	case 2: // deutan
		m = { {{0.33066007, 0.66933993, 0, 0}, {0.247995052, 0.50200494, .25, 0}, {0.02785538, -0.02785538, 1, 0}, {0,0,0,1}} };
		break;
	case 3:
		m = { {{1, 0.12741869 , -0.12741869 , 0}, {0, 0.87388737, 0.12611263, 0}, {0, 0.87388737, 0.12611263, 0}, {0, 0, 0, 1}} };
		break;
	default:
		m = i;
	}
	return i + (m - i) * a;
}

void __declspec(dllexport) __stdcall cb_compute(size_t sz, void* v) {
	Packet& pin = (*(Packet*)v)["in"];
	Packet& pout = (*(Packet*)v)["out"];

	pout["colorblindness"].value.m4 = colorblindness(pin["severity"].value.f,pin["colorblindness"].value.i32);//name of uniform editor will use in shader
}