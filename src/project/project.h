#pragma once
#include "../engine/Project.h"
#include <raylib.h>

/// <summary>
/// Write your project code here or do what you want with it. However,
/// you MUST implement the IProject interface somehow and set the project reference!
/// See <see cref="Techstorm::IProject" /> for more information on this.
/// </summary>
/// <inheritdoc />
class Project : public Techstorm::IProject {
public:
	Techstorm::Renderer mRenderer;
	Techstorm::Window mWindow;
	Project() : IProject() {}

	/// <inheritdoc />
	/// <see cref="Techstorm::IProject::init" />
	void init(int argc, char* argv[]) override {
		IProject::init(argc, argv);
		std::cout << "Thread ID for Project init: " << std::this_thread::get_id() << "" << std::endl;
		mWindow.initialize(800, 600, "Techstorm");
		mRenderer = Techstorm::Renderer();
		mRenderer.initialize();
	}

	int run(int argc, char* argv[]) override {
		IProject::run(argc, argv);
		std::cout << "Thread ID for Project run: " << std::this_thread::get_id() << "" << std::endl;
		while (!mWindow.shouldClose()) {
			BeginDrawing();
			ClearBackground(RAYWHITE);
			EndDrawing();
		}
		return 0;
	}
};
