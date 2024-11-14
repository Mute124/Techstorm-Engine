#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "../Common.h"
#include "IGameObjectGate.h"

namespace Techstorm {
	/// <summary>
	/// Game object registry, it stores all game objects in the world and manages their updating, rendering, destruction, creation, etc.
	/// </summary>
	class GameObjectRegistry {
	public:

		/// <summary>
		/// Adds a game object pointer to mGameObjectsSink.
		/// </summary>
		/// <param name="gameObject">The game object pointer to add.</param>
		/// <seealso cref="GameObject"/>
		void addGameObject(GameObject* gameObject);

		/// <summary>
		/// Adds a game object gate pointer of IGameObjectGate to mGameObjectsGateSink.
		/// </summary>
		/// <param name="gameObjectGate">The game object gate.</param>
		/// <seealso cref="IGameObjectGate"/>
		void addGameObjectGate(IGameObjectGate* gameObjectGate);

		/// <summary>
		/// Updates all game objects in the instance (world).
		/// </summary>
		void update();

		/// <summary>
		/// Renders all game objects in the instance (world).
		/// </summary>
		void render();

	private:
		std::vector<GameObject*> mGameObjectsSink;
		std::vector<IGameObjectGate*> mGameObjectsGateSink;

		friend class Renderer;
		//std::vector<IDynamicGameObject*> mDynamicObjectsSink;
		//std::vector<IStaticGameObject*> mStaticObjectsSink;
	};
}
