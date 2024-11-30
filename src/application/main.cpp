#include <Common.h>
#include <modding/ScriptingAPI.h>
#include <renderer/Renderer.h>
#include <renderer/WindowDecorations.h>
#include <conf/Config.h>

#include <project.h>
#include <raylib.h>
#include <thread>

/*
#include <renderer/GameUI.h>
#include "Shell.h"
#include <backends/RmlUi_Backend.h>*/
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
	scriptingAPI.InitializeScripting(project.getLuaLibraries(), project.getLuaFunctions());
	scriptingAPI.RegisterLua();
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
	

	/*// Initializes the shell which provides common functionality used by the included samples.
	if (!Shell::Initialize()) {
		std::cout << "Failed to initialize shell" << std::endl;
		return -1;
	}



	Rml::Context* context = Rml::CreateContext("main", Rml::Vector2i(decorations.width, decorations.height));
	if (!context)
	{
		Rml::Shutdown();
		
		return -1;
	}
	// The RmlUi debugger is optional but very useful. Try it by pressing 'F8' after starting this sample.
	Rml::Debugger::Initialise(context);

	// Fonts should be loaded before any documents are loaded.
	Shell::LoadFonts();

	// Load and show the demo document.
	if (Rml::ElementDocument* document = context->LoadDocument("demo.rml"))
		document->Show();
	else 
		std::cout << "Failed to load demo document" << std::endl;


	project.getRenderer().addGameObject(new UI(context));*/

	SetTargetFPS(decorations.targetFPS);

	while (!WindowShouldClose()) {
		//context->Update();
		HandleFrame(project);
	}

	project.cleanup(0);

	CloseWindow();
	return 0;
}