#pragma once
#include <cstdint>

namespace Techstorm {
	using WindowDecorations = struct WindowDecorations {
		const char* title = "Untitled Techstorm Project";
		uint32_t width = 1280;
		uint32_t height = 720;
		unsigned int windowConfig = -1;
		unsigned int targetFPS = 60;
	};
}
