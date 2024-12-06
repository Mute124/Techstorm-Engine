#include <Common.h>
#include <modding/ScriptingAPI.h>
#include <renderer/Renderer.h>
#include <renderer/WindowDecorations.h>
#include <conf/Config.h>

#include <project.h>
#include <raylib.h>
#include <thread>
#include "ApplicationUtils.h"
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

void InitScripting(ScriptingAPI& scriptingAPI, PROJECT_TYPENAME& project) {
	scriptingAPI.initializeScripting(project.getLuaLibraries(), project.getLuaFunctions());
	scriptingAPI.registerLua();
}

void HandleFrame(PROJECT_TYPENAME& project) {
	project.getRenderer().update();

	project.texture();
	project.render();

	// This is here because it reduces CPU consumption
	std::this_thread::yield();
}
/*
class UI : public GameObject {
public:


	Rml::Context* context = nullptr;
	UI(Rml::Context* context) : context(context), GameObject() {
	}
	void render() override {
		context->Render();
	}

};*/

int main(int argc, char* argv[]) {
	PROJECT_TYPENAME project = PROJECT_TYPENAME();
	project.preInit();

	InitializeConfigRegistry();
	ConfigFileRegistry& configRegistry = GetConfigFileRegistry();
	
	Renderer& renderer = project.getRenderer();
	WindowDecorations& decorations = project.getWindowDecorations();
	
	ScriptingAPI scriptingAPI;

	InitScripting(scriptingAPI, project);

	InitWindow(decorations);

	project.init(argc, argv);
	project.postInit();

	Techstorm::Application::FrameManager& manager = Techstorm::Application::FrameManager::Instance();

	SetTargetFPS(decorations.targetFPS);

	manager.launchThreads(project);

	while (!WindowShouldClose()) {
		//context->Update();
		HandleFrame(project);
	}

	project.cleanup(0);

	CloseWindow();
	return 0;
}