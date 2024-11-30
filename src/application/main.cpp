#include <Common.h>
#include <modding/ScriptingAPI.h>
#include <renderer/Renderer.h>
#include <renderer/WindowDecorations.h>
#include <conf/Config.h>

#include <project.h>
#include <raylib.h>
#include <thread>




using namespace Techstorm;

void InitWindow(WindowDecorations& decorations) {
	decorations.title = LookupConfig("Project.cfg", "projectWindowTitle");
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_INTERLACED_HINT);
	InitWindow(decorations.width, decorations.height, decorations.title);

	const char* iconPath = TextFormat("%s%s", TS_ASSET_DIR.c_str(), decorations.icon);

	Image icon = LoadImage(iconPath);
	ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

	SetWindowIcons(&icon, 1);
}

void HandleFrame(PROJECT_TYPENAME& project) {
	project.getRenderer().update();

	project.preObjectUpdate();
	project.objectUpdate();
	project.postObjectUpdate();

	project.prePhysicsUpdate();
	project.physicsUpdate();
	project.postPhysicsUpdate();

	project.texture();
	project.render();

	// This is here because it reduces CPU consumption
	std::this_thread::yield();
}


int main(int argc, char* argv[]) {
	PROJECT_TYPENAME project = PROJECT_TYPENAME();
	project.preInit();

	InitializeConfigRegistry();
	ConfigFileRegistry& configRegistry = GetConfigFileRegistry();
	
	Renderer& renderer = project.getRenderer();
	WindowDecorations& decorations = project.getWindowDecorations();
	
	ScriptingAPI scriptingAPI;

	scriptingAPI.InitializeScripting(project.getLuaLibraries(), project.getLuaFunctions());
	scriptingAPI.RegisterLua();

	InitWindow(decorations);

	project.init(argc, argv);
	project.postInit();
	DisableCursor();


	SetTargetFPS(decorations.targetFPS);

	while (!WindowShouldClose()) {
		HandleFrame(project);
	}

	project.cleanup(0);

	CloseWindow();
	return 0;
}