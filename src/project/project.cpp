#include "project.h"
#include "renderer/Renderer.h"
#include "renderer/objects/PlaneObject.h"
#include <iostream>
#include <chrono>
#include <raylib.h>
using namespace Techstorm;
int Project::run(int argc, char* argv[])
{
	//std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	//test1 testStruct1;
	//test2 testStruct2;



	//std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	//// calculate nanoseconds
	//int nanosec = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
	//int millisec = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	//std::cout << "Time elapsed: " << millisec << "ms, " << nanosec << "ns" << std::endl;
	////std::cout << testStruct1.x << ", " << testStruct1.y << ", " << testStruct1.z << std::endl;
	////std::cout << testStruct2.x << ", " << testStruct2.y << ", " << testStruct2.z << std::endl;
	//setProject<Project>(this);


	//Renderer renderer = Renderer();
	
	//renderer.addGameObject(new PlaneObject());
	//renderer.addGameObject(new Cube());

	GameCamera cam = { 0 };
	cam.Data.position = Vector3{ 0.0f, 5.0f, 3.0f };
	cam.Data.target = Vector3{ 0.0f, -10.0f, 0.0f };
	cam.Data.up = Vector3{ 0.0f, 1.0f, 0.0f};
	cam.Data.fovy = 45.0f;
	cam.Data.projection = CAMERA_PERSPECTIVE;
	//renderer.setCamera(cam);
	
	while (!this->mWindow.shouldClose()) {
		//renderer.render(cam);
	}


//	renderer.cleanup();
	return 0;
}

void Project::init(int argc, char* argv[])
{
	
}

void Project::preInit()
{
	this->initWindow(600, 800, "Techstorm", FLAG_MSAA_4X_HINT);
	this->initRenderer();
}
