#pragma once
/*#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <modding/ScriptingAPI.h>
#include <conf/Config.h>

#include <project.h>
#include <raylib.h>
#include <renderer/Renderer.h>
#include <renderer/WindowDecorations.h>
#include <fs/FileSystem.h>
#include <string>
#include <chrono>


int main(int argc, char* argv[]) {
#ifdef _DEBUG
	// Enable leak detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	using namespace Techstorm;

	PROJECT_TYPENAME project = PROJECT_TYPENAME();
	ConfigFileRegistry& configFileRegistry = ConfigFileRegistry::Instance();
	project.preInit();

	FileSystemRegistry& fileSystemRegistry = GetFileSystemRegistry();
	Renderer const& renderer = project.getRenderer();
	WindowDecorations const& decorations = project.getWindowDecorations();
	ScriptingAPI scriptingAPI;
	InputRegistry& inputRegistry = InputRegistry::Instance();

	scriptingAPI.InitializeScripting(project.getLuaLibraries(), project.getLuaFunctions());
	scriptingAPI.RegisterLua();

	InitWindow(decorations.width, decorations.height, decorations.title);

	configFileRegistry.init();

	std::string iconPath = GetFile("png")->meta->path;

	Image icon = LoadImage(iconPath.c_str());
	ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

	SetWindowIcons(&icon, 1);

	project.init(argc, argv);

	project.postInit();

	SetTargetFPS(decorations.targetFPS);

	Texture tex = LoadTextureFromImage(fileSystemRegistry.getFile("png")->get<Image>());
	// Controller index is typically 0 for the first controller
	int controllerIndex = 0;
	using namespace std::chrono_literals;

	while (!WindowShouldClose()) {

		project.preObjectUpdate();
		project.objectUpdate();
		project.postObjectUpdate();

		project.prePhysicsUpdate();
		project.physicsUpdate();
		project.postPhysicsUpdate();

	}

	project.cleanup(0);

	CloseWindow();



	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
	return 0;
}
*/