#include "project.h"
#ifdef _DEBUG
//#include <crtdbg.h>
#endif

void initProject(Project& project, int argc, char* argv[]) {
	project.preInit();
	project.init(argc, argv);
	project.postInit();
}

int main(int argc, char* argv[]) {
#ifdef _DEBUG
	// Enable leak detection
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	/*	// Initialization
		//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;
	std::cout << "Thread ID for Window Initialization: " << std::this_thread::get_id() << "" << std::endl;
	//InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");
	std::cout << "Thread ID for after Window Initialization: " << std::this_thread::get_id() << "" << std::endl;
	Techstorm::Window window = Techstorm::Window();
	window.initialize(screenWidth, screenHeight, "Techstorm");

	Techstorm::Renderer renderer = Techstorm::Renderer();
	// Define the camera to look into our 3d world
	Camera3D camera = { 0 };
	camera.position = Vector3{ 0.0f, 10.0f, 10.0f };  // Camera position
	camera.target = Vector3{ 0.0f, 0.0f, 0.0f };      // Camera looking at point
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

	Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!window.shouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);

		DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
		DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

		DrawGrid(10, 1.0f);

		EndMode3D();

		renderer.test();

		DrawFPS(10, 10);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------*/
	//std::cout << "Thread ID for Window Initialization: " << std::this_thread::get_id() << "" << std::endl;
	//Project project = Project();

	//initProject(project, argc, argv);

	//int projectResult = project.run(argc, argv);
/*	std::cout << "Thread ID for main: " << std::this_thread::get_id() << "" << std::endl;
	using namespace Techstorm;

	renderer.initialize();
	renderer.startLoop();*/
	return 0;
}
