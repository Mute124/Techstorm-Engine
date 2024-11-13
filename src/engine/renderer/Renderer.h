#pragma once
#include <vector>
#include <memory>
#include "../utils/Singleton.h"

#include "GameObjectRegistry.h"
#include "Camera.h"

#include <Jolt/Jolt.h>

// Jolt includes
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <raylib.h>

namespace Techstorm {
	class GameObject;

	class Renderer {
	public:
#ifndef TS_CUSTOM_RENDERER_CONSTRUCTOR
		// This damn constructor.
		Renderer() {
			//initialize();
		}
#endif
		void initialize();

		void startLoop() {
			std::cout << "Thread ID for startLoop Begin: " << std::this_thread::get_id() << "" << std::endl;
			while (!WindowShouldClose()) {
				std::cout << "Thread ID for startLoop in loop: " << std::this_thread::get_id() << "" << std::endl << std::endl;
				BeginDrawing();
				ClearBackground(RAYWHITE);
				EndDrawing();
			}
		}

		void test() {
			DrawText("Welcome to the third dimension!", 10, 40, 20, DARKGRAY);
		}

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
