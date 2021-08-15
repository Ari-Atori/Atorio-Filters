#include "core/Packet.hpp"
//radio

static mat4 colorblindness(float a, int cvd) {
	//mat4 rgb2lms = { {{17.8824F, 43.5161F, 4.11935F, 0}, {3.45565F, 27.1554F, 3.86714F, 0}, {0.0299566F, 0.184309F, 1.46709F, 0}, {0, 0, 0, 1}} };
	//mat4 lms2rgb = { { {0.0809445F, -0.130504F, 0.116721F, 0}, { -0.0102485F, 0.0540193F, -0.113615F, 0 }, { -0.000365297F, -0.00412162F, 0.693511F, 0 }, { 0, 0, 0, 1 }} };
	mat4 protan = { {{0, 1.05118294 , -0.05116099, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0,0,0,1}} };
	mat4 deutan = { {{0.33066007 , 0.66933993 , 0 , 0}, {0.33066007, 0.66933993, 0, 0}, {-0.02785538, 0.02785538, 1, 0}, {0, 0, 0, 1}} };
	return deutan;
	//mat4 deutan = { {{1,0,0,0},{ 0.9513092,0,0.04866992, 0 },{0,0,1,0},{0,0,0,1}} };
	//{ {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}} }
	//return deutan;
	if (cvd == 0) {//protan
		//mat4 protan = { {{1 - 0.433333 * a,0.433333*a,0,1},{0.55883 * a,1 - 0.55883 * a,0,0},{0, 0.24167 * a, 1 - 0.24167*a, 0},{0,0,0,1}} };
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