#include <stdlib.h>

const char* filter_names[8] =
{
	"video-colorblindness",
	"video-contrast",
	"video-fadein",
	"video-fadeout",
	"video-homoluma",
	"video-hue-saturation-luma",
	"video-transform",
	"video-whitebalance"
};

void __declspec(dllexport) __stdcall get_filters(size_t sz, void* v) {
	const char** c = (const char**)v;
	*c = (sz < 0 || sz >= 8) ? NULL : filter_names[sz];
}