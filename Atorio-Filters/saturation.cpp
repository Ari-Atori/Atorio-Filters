#include "core/Packet.hpp"

void __declspec(dllexport) __stdcall saturation_compute(size_t sz, void* v) {
	Packet& pin = (*(Packet*)v)["in"];
	Packet& pout = (*(Packet*)v)["out"];

	pout["saturation"].value.f = pin["saturation"].value.f;
}