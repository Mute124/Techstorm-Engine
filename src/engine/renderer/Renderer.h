#pragma once
#include <vector>
#include <memory>
#include "../utils/Singleton.h"

#include "GameObjectRegistry.h"
#include "GameCamera.h"

// Jolt includes
#include <Jolt/Jolt.h>
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

	/// <summary>
	/// Serves as the renderer for the game.
	/// </summary>
	class Renderer {
	public:
#ifndef TS_CUSTOM_RENDERER_CONSTRUCTOR
		/// <summary>
		/// Initializes a new instance of the <see cref="Renderer"/> class.
		/// </summary>
		Renderer() {
			//initialize();
		}
#endif
		/// <summary>
		/// Initializes this instance.
		/// </summary>
		void initialize();

		/// <summary>
		/// Renders the render texture to the screen using the specified camera.
		/// </summary>
		/// <param name="cam">The cam.</param>
		void render(GameCamera& cam);

		/// <summary>
		/// Textures the scene to the render texture using the specified camera.
		/// </summary>
		/// <param name="cam">The cam.</param>
		void texture(GameCamera& cam);

		/// <summary>
		/// Draws the FBO/RenderTexture2D.
		/// </summary>
		void drawFBO();

		/// <summary>
		/// Adds the game object.
		/// </summary>
		/// <param name="gameObject">The game object pointer to add.</param>
		void addGameObject(GameObject* gameObject);

		/// <summary>
		/// Removes a game object.
		/// </summary>
		/// <param name="gameObject">The game object pointer to remove.</param>
		void removeGameObject(GameObject* gameObject);

		/// <summary>
		/// Adds a game object gate.
		/// </summary>
		/// <param name="gameObjectGate">The game object gate pointer to add.</param>
		/// <seealso cref="IGameObjectGate" />
		void addGameObjectGate(IGameObjectGate* gameObjectGate);

		/// <summary>
		/// Removes a game object gate.
		/// </summary>
		/// <param name="gameObjectGate">The game object gate pointer to remove.</param>
		/// <seealso cref="IGameObjectGate" />
		void removeGameObjectGate(IGameObjectGate* gameObjectGate);

		/// <summary>
		/// Cleanups this instance.
		/// </summary>
		void cleanup();
	private:
		GameObjectRegistry mGameObjects;
		RenderTexture2D mScreenBuffer;
		Color mBackgroundColor = BLACK;
		Color mFBOTint = WHITE;
		GameCamera mCamera;


#ifdef TS_RENDERER_2D
		/// <summary>
		/// Renders the 2d scene.
		/// </summary>
		/// <param name="cam">The active camera.</param>
		void render2D(GameCamera& cam);
#else
		/// <summary>
		/// Renders the 3d scene.
		/// </summary>
		/// <param name="cam">The active camera.</param>
		void render3D(GameCamera& cam);
#endif
	};
}
