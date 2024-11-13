#include "Window.h"
#include <rlgl.h>
#include <iostream>
#include <thread>
int Techstorm::Window::initialize(int width, int height, const char* title, unsigned int windowConfig)
{
	this->mWidth = width;
	this->mHeight = height;
	this->mTitle = title;
	std::cout << "Thread ID for Window Initialization: " << std::this_thread::get_id() << "" << std::endl;
	int result = 0;
#ifdef TS_RENDERER_RAYLIB
	//SetConfigFlags(windowConfig);
	InitWindow(this->mWidth, this->mHeight, this->mTitle);
	//rlglInit(this->mWidth, this->mHeight);

	if (!IsWindowReady())
	{
		result = -1;
		std::cout << "Failed to initialize window: " << std::endl;
	}
#endif
	return result;
}

bool Techstorm::Window::shouldClose()
{
	std::cout << "Thread ID for Window shouldClose: " << std::this_thread::get_id() << "" << std::endl;
	bool result = false;

#ifdef TS_RENDERER_RAYLIB
	result = WindowShouldClose();
#endif

	return result;
}

bool Techstorm::Window::isReady()
{
	bool result = false;
#ifdef TS_RENDERER_RAYLIB
	result = IsWindowReady();
#endif

	return result;
}

Techstorm::Window::~Window()
{
#ifdef TS_RENDERER_RAYLIB
	CloseWindow();
#endif
}
