#pragma once
#include "renderer/Window.h"
#include "renderer/Renderer.h"
#include "utils/Singleton.h"

namespace Techstorm {
	class IProject abstract {
	private:
		
	protected:
		Renderer mRenderer;
		Window mWindow ;

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



		template<typename T>
		void setProject(T* project) {
			ProjectReference::Instance().setProjectReference(project);
		}

		virtual void preInit() = 0;
		virtual void init(int argc, char* argv[]) = 0;
		virtual void postInit() {}

		// Should be called in preInit
		virtual void initWindow(uint16_t width, uint16_t height, const char* title, unsigned int windowConfig = 0) {

			mWindow.initialize(width, height, title, windowConfig);
		}

		// Should be called after initWindow in preInit
		virtual void initRenderer() {
			mRenderer = Renderer();
			mRenderer.initialize();
		}

		virtual int run(int argc, char* argv[]) = 0;

		virtual int prePhysicsUpdate() {return 0; }
		virtual int postPhysicsUpdate() { return 0; }
		
		virtual int preObjectUpdate() { return 0; }
		virtual int objectUpdate() { return 0; }
		virtual int postObjectUpdate() { return 0; }

		virtual int texture() { return 0; }
		virtual int render() { return 0; }
		
		virtual int cleanup(int exitCode) { return exitCode; }

		static IProject* GetProject() {
			return ProjectReference::Instance().project;
		}

	};
}