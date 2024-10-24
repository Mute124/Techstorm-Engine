#pragma once
#include <iostream>
#define TS_RENDERER_RAYLIB
#ifdef TS_RENDERER_RAYLIB
#include <raylib.h>
#include <rlgl.h>

#endif

namespace Techstorm {
	class Window {
	public:

		~Window();

		// TODO : Make this the constructor
		int initialize(uint16_t width = 600, uint16_t height = 800, const char* title = "Untitled Techstorm Project", unsigned int windowConfig = 0);
		bool shouldClose();
		bool isReady();

		
	private:

	
		uint16_t mWidth = 600;
		uint16_t mHeight = 800;
		const char* mTitle = "Untitled Techstorm Project";
		unsigned int mWindowConfig;
	};
}