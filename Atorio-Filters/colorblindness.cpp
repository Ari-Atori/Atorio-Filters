#include "core/Packet.hpp"
//radio

static mat4 colorblindness(float a, int cvd) {


	if (cvd == 0) {//protan
		mat4 protan = { {{1 - 0.433333 * a,0.433333*a,0,1},{0.55883 * a,1 - 0.55883 * a,0,0},{0, 0.24167 * a, 1 - 0.24167*a, 0},{0,0,0,1}} };
		return protan ;
	}
	else if (cvd==1) {
		mat4 duertan = { {{1 - .375 * a, .375 * a, 0, 0}, {.7 * a, 1 - .7 * a, 0, 0},{0, .3 * a, 1 - .3 * a, 0},{0,0,0,1}} };
		return duertan;
	}
	else if (cvd == 2) {
		mat4 tritan = { {{(1-.05*a), 0.05*a, 0, 0},{0, 0.43333*a, (1-.43333*a), 0},{0, .475*a, (1-.475*a), 0},{0, 0, 0, 1}} };
		return tritan;
	}
	}

void __declspec(dllexport) __stdcall cb_compute(size_t sz, void* v) {
	Packet& pin = (*(Packet*)v)["in"];
	Packet& pout = (*(Packet*)v)["out"];

	pout["colorblindness"].value.m4 = colorblindness(pin["severity"].value.f,pin["colorblindness"].value.i32);//name of uniform editor will use in shader
}