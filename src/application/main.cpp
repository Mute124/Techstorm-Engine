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

	return 0;
}
