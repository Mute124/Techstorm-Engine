#include "ApplicationUtils.h"

int main(int argc, char* argv[]) {
#ifdef _DEBUG
	// Enable leak detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	using namespace Techstorm;

	PROJECT_TYPENAME project = PROJECT_TYPENAME();
	project.preInit();

	Renderer& renderer = project.getRenderer();
	WindowDecorations& decorations = project.getWindowDecorations();

	InitWindow(decorations.width, decorations.height, decorations.title);

	const char* iconPath = TextFormat("%s%s", TS_ASSET_DIR.c_str(), decorations.icon);

	Image icon = LoadImage(iconPath);
	ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

	SetWindowIcons(&icon, 1);

	project.init(argc, argv);
	project.postInit();

	SetTargetFPS(decorations.targetFPS);

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
	return 0;
}
