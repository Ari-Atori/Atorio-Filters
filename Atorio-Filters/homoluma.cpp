#include "core/Packet.hpp"

void __declspec(dllexport) __stdcall homoluma_compute(size_t sz, void* v) {
	Packet& pin = (*(Packet*)v)["in"];
	Packet& pout = (*(Packet*)v)["out"];

	pout["luma"].value.f = pin["luma"].value.f;
	pout["prop"].value.f = pin["prop"].value.f;
}