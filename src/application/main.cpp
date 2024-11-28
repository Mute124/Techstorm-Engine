#include <Common.h>
#include <modding/ScriptingAPI.h>
#include <renderer/Renderer.h>
#include <renderer/WindowDecorations.h>
#include <conf/Config.h>

#include <project.h>

#include <raylib.h>
#include <thread>

int main(int argc, char* argv[]) {
	using namespace Techstorm;

	PROJECT_TYPENAME project = PROJECT_TYPENAME();
	project.preInit();

	InitializeConfigRegistry();
	ConfigFileRegistry& configRegistry = GetConfigFileRegistry();
	
	Renderer& renderer = project.getRenderer();
	WindowDecorations& decorations = project.getWindowDecorations();
	
	ScriptingAPI scriptingAPI;

	scriptingAPI.InitializeScripting(project.getLuaLibraries(), project.getLuaFunctions());
	scriptingAPI.RegisterLua();

	decorations.title = LookupConfig("Project.cfg", "projectWindowTitle");

	InitWindow(decorations.width, decorations.height, decorations.title);

	const char* iconPath = TextFormat("%s%s", TS_ASSET_DIR.c_str(), decorations.icon);

	Image icon = LoadImage(iconPath);
	ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

	SetWindowIcons(&icon, 1);

	project.init(argc, argv);
	project.postInit();

	SetTargetFPS(decorations.targetFPS);

	while (!WindowShouldClose()) {
		renderer.update();

		project.preObjectUpdate();
		project.objectUpdate();
		project.postObjectUpdate();

		project.prePhysicsUpdate();
		project.physicsUpdate();
		project.postPhysicsUpdate();

		renderer.texture(renderer.mCamera);
		renderer.render(renderer.mCamera);
		
		// This is here because it reduces CPU consumption
		std::this_thread::yield();
	}

	project.cleanup(0);

	CloseWindow();
	return 0;
}