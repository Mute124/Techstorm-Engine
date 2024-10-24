#pragma once
#include <vector>
#include <memory>
#include "../utils/Singleton.h"

#include "GameObjectRegistry.h"
#include "Camera.h"
#include <raylib.h>
namespace Techstorm {
	class GameObject;

	class Renderer {
	public:
#ifndef TS_CUSTOM_RENDERER_CONSTRUCTOR
		// This fucking constructor.
		Renderer() {
			//initialize();
		}
#endif
		void initialize();

		void render(GameCamera& cam);
		void texture(GameCamera& cam);
		void drawFBO();

		void addGameObject(GameObject* gameObject);
		void removeGameObject(GameObject* gameObject);

		void addGameObjectGate(IGameObjectGate* gameObjectGate);
		void removeGameObjectGate(IGameObjectGate* gameObjectGate);

		void cleanup();
	private:
		GameObjectRegistry mGameObjects;
		RenderTexture2D mScreenBuffer;
		Color mBackgroundColor = BLACK;
		Color mFBOTint = WHITE;
#ifdef TS_RENDERER_2D
		void render2D(GameCamera& cam);
#else
		void render3D(GameCamera& cam);
#endif

	};
}