#include "core/Packet.hpp"

	void __declspec(dllexport) __stdcall hsy_compute(size_t sz, void* v) {
		Packet& pin = (*(Packet*)v)["in"];
		Packet& pout = (*(Packet*)v)["out"];

		pout["hsya"].value.v4 = { pin["hue"].value.f / 360.0F, pin["saturation"].value.f, pin["luma"].value.f, 1.0F };
	}