#pragma once
#include <iostream>
#define TS_RENDERER_RAYLIB
#ifdef TS_RENDERER_RAYLIB
#include <raylib.h>

#endif

namespace Techstorm {
	class Window {
	public:

		~Window();

		// TODO : Make this the constructor
		int initialize(int width = 600, int height = 800, const char* title = "Untitled Techstorm Project", unsigned int windowConfig = 0);
		bool shouldClose();
		bool isReady();

	private:

		int mWidth = 600;
		int mHeight = 800;
		const char* mTitle = "Untitled Techstorm Project";
		unsigned int mWindowConfig;
	};
}
