#ifndef ATORIO_PACKET
#define ATORIO_PACKET

#include <stdint.h>
#include "Vector.hpp"
#include "Matrix.hpp"

#define PACKET_PACKET 0
#define PACKET_FLOAT 1
#define PACKET_VEC2 2
#define PACKET_VEC3 3
#define PACKET_VEC4 4
#define PACKET_MAT4 5
#define PACKET_INT32 6
#define PACKET_INT64 7
#define PACKET_VOID  8
#define PACKET_STRING 9

struct Packet {
	char name[32];
	uint32_t type;
	uint32_t count;
	union {
		float f;
		vec2 v2; vec3 v3; vec4 v4; mat4 m4;
		int32_t i32; int64_t i64;
		void* v;
	} value;

	Packet& operator[](const char* name);
};

#endif
