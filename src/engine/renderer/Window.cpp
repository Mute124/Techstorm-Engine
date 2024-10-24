#include "Window.h"




int Techstorm::Window::initialize(uint16_t width, uint16_t height, const char* title, unsigned int windowConfig)
{
	this->mWidth = width;
	this->mHeight = height;
	this->mTitle = title;
	
	int result = 0;
#ifdef TS_RENDERER_RAYLIB
	//SetConfigFlags(windowConfig);
	InitWindow(width, height, title);
	rlglInit(width, height);

	if (!IsWindowReady())
	{
		
		result = -1;
		std::cout << "Failed to initialize window: "<< std::endl;
	}
#endif
	return result;
}

bool Techstorm::Window::shouldClose()
{
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
	result =  IsWindowReady();
#endif

	return result;
}

Techstorm::Window::~Window()
{
#ifdef TS_RENDERER_RAYLIB
	CloseWindow();
#endif
}
