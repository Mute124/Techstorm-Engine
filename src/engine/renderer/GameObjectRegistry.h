#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "../Common.h"
#include "IGameObjectGate.h"

namespace Techstorm {


	class GameObjectRegistry {
	public:
		void addGameObject(GameObject* gameObject);

		void addGameObjectGate(IGameObjectGate* gameObjectGate);

		
		void update();
		void render();

	private:
		std::vector<GameObject*> mGameObjectsSink;
		std::vector<IGameObjectGate*> mGameObjectsGateSink;

		friend class Renderer;
		//std::vector<IDynamicGameObject*> mDynamicObjectsSink;
		//std::vector<IStaticGameObject*> mStaticObjectsSink;
	};



}