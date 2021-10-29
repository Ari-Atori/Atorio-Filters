#include "Packet.hpp"
#include <cstring>

Packet null = { "", 0, 0, {0} };

Packet& Packet::operator[](const char* name) {
	Packet* list = (Packet*)value.v;
	for (uint32_t i = 0; i < count; ++i)
		if (!strcmp(name, list[i].name))
			return list[i];
	return null;
}