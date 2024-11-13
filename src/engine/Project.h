#pragma once
#include "renderer/Renderer.h"
#include "renderer/Window.h"
#include "utils/Singleton.h"
#include <stdint.h>

namespace Techstorm {
	/// <summary>
	/// This is an <b>abstract interface singleton</b> that all projects must implement and set the <i>ProjectReference</i> singleton to
	/// their project. If this boilerplate code is not done, Techstorm will not know what to run. In terms of functionality, this interface
	/// just holds the functions and variables that Techstorm will call (besides some initialization).
	/// </summary>
	class IProject abstract {
	protected:

		/// <summary>
		/// Represents a polymorphic singleton reference to the user's project instance through a pointer of Techstorm::IProject. This is
		/// mandatory for Techstorm to run the user's engine.
		/// </summary>
		class ProjectReference : public Singleton<ProjectReference> {
		public:
			IProject* project = nullptr;

			void setProjectReference(IProject* project) {
				if (project != nullptr) {
					this->project = project;
				}
			}
		};

	public:

		/// <summary>
		/// This function is used to set the <i>ProjectReference</i> singleton to the project.
		/// </summary>
		/// <typeparam name="T">The typename for what the user's project is</typeparam>
		/// <param name="project">The pointer to the user's project</param>
		template<typename T>
		void setProject(T* project) {
			ProjectReference::Instance().setProjectReference(project);
		}

		/// <summary>
		/// This is the first function that will be called on startup. This is empty because it is an optional feature but is highly reccomended to clearly outline initialization phases.
		/// </summary>
		virtual void preInit() {
			//initWindow(600, 800, "Techstorm", FLAG_MSAA_4X_HINT);
			//initRenderer();
		};

		/// <summary>
		/// Initializes your project. Any code you need done before the loop starts, call it here. <b>THIS MUST BE OVERRIDEN BY YOUR PROJECT CLASS!</b>
		/// </summary>
		/// <param name="argc">Command line argument count int</param>
		/// <param name="argv">Command line arguments array</param>
		virtual void init(int argc, char* argv[]) {
			std::cout << "Thread ID for IProject init" << std::this_thread::get_id() << std::endl;

		}

		/// <summary>
		/// Does a post initialization of the project. This is empty because it is not neccesary to override.
		/// </summary>
		virtual void postInit() {}

		/// <summary>
		/// Initializes the window.
		/// </summary>
		/// <param name="width">Window width in <b>16 bit unsigned int</b></param>
		/// <param name="height">Window height in <b>16 bit unsigned int</b></param>
		/// <param name="title">Window title (what shows in the top left) in <b>const char*</b></param>
		/// <param name="windowConfig">The window flags that should be used in <b>unsigned int</b></param>
		virtual void initWindow(uint16_t width, uint16_t height, const char* title, unsigned int windowConfig = 0) {
			//mWindow.initialize(width, height, title, windowConfig);
		}

		/// <summary>
		/// Initializes the renderer and should be called after initWindow.
		/// </summary>
		virtual void initRenderer() {
			//mRenderer = Renderer();
			//mRenderer.initialize();
		}

		/// <summary>
		/// Runs the actual game and is called after the init functions
		/// </summary>
		/// <param name="argc">Command line argument count int</param>
		/// <param name="argv">Command line arguments array</param>
		/// <returns>The game loop's exit code</returns>
		virtual int run(int argc, char* argv[]) {
			std::cout << "Thread ID for IProject run: " << std::this_thread::get_id() << "" << std::endl;
			return 0;
		}

		/// <summary>
		/// Pre-update step that is called in the physics or update thread (depending on thread count)
		/// </summary>
		/// <returns>The exit code of the step</returns>
		virtual int prePhysicsUpdate() { return 0; }

		/// <summary>
		/// This is where the actual physics update happens. <b>Please note that this will run on the physics thread!</b>
		/// </summary>
		/// <returns>The exit code of the step</returns>
		virtual int physicsUpdate() { return 0; }

		/// <summary>
		/// Post physics update that is called after physicsUpdate() in the physics or update thread (depending on thread count).
		/// </summary>
		/// <returns>The exit code of the step</returns>
		virtual int postPhysicsUpdate() { return 0; }

		/// <summary>
		/// Any preparation code for updating the scene's game objects. Use this if you need to do something after the physics update, but before the
		/// GameObject update. <b>Please note that this will run on the update thread!</b>
		/// </summary>
		/// <returns>The exit code of the step</returns>
		virtual int preObjectUpdate() { return 0; }

		/// <summary>
		/// This is where the actual GameObject update happens, and is called after preObjectUpdate(). <b>Please note that this will run on the update thread!</b>
		/// </summary>
		/// <returns>The exit code of the step</returns>
		virtual int objectUpdate() { return 0; }

		/// <summary>
		/// Called right after objectUpdate(). Use this to do anything after the GameObject update. <b>Please note that this will run on the update thread!</b>
		/// </summary>
		/// <returns></returns>
		virtual int postObjectUpdate() { return 0; }

		/// <summary>
		/// Textures all GameObjects before render() is called and after update functions are called. This is essentially where the scene is
		/// rendered. <b>Please note that this will run on the render thread!</b>
		/// </summary>
		/// <returns> An integer that is the exit code for this texturing frame.</returns>
		virtual int texture() { return 0; }

		/// <summary>
		/// Assuming that the FBO is enabled, this will render the FBO and apply any post-processing effects to the FBO.
		/// <b>Please note that this will run on the update thread!</b>
		/// </summary>
		/// <returns> An integer that is the exit code for this rendering frame.</returns>
		virtual int render() { return 0; }

		/// <summary>
		/// Cleans up anything that may need to be cleaned up.
		/// </summary>
		/// <param name="exitCode">The code that the engine has exited with</param>
		/// <returns>The cleanup exit code.</returns>
		virtual int cleanup(int exitCode) { return exitCode; }

		/// <summary>
		/// Gets the current project instance.
		/// </summary>
		/// <returns>An IProject pointer of the current project reference instance</returns>
		static IProject* GetProject() {
			return ProjectReference::Instance().project;
		}
	};


}
