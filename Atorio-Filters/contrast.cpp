#include "core/Packet.hpp"

void __declspec(dllexport) __stdcall contrast_compute(size_t sz, void* v) {
	Packet& pin = (*(Packet*)v)["in"];
	Packet& pout = (*(Packet*)v)["out"];

	const float e = 1.00000011920928955F; //1 + epsilon, to avoid divide by zero
	float c = pin["contrast"].value.f;

	pout["cslope"].value.f = (e * (1.0F + c) / (e - c));
	pout["pivot"].value.f = pin["pivot"].value.f;
}