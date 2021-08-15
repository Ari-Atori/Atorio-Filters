#include "core/Packet.hpp"

void __declspec(dllexport) __stdcall homoluma_compute(size_t sz, void* v) {
	Packet& pin = (*(Packet*)v)["in"];
	Packet& pout = (*(Packet*)v)["out"];

	pout["factor"].value.f = pin["factor"].value.f;
}