#include "GameObjectRegistry.h"

void Techstorm::GameObjectRegistry::addGameObject(GameObject* gameObject)
{
	if (gameObject != nullptr) {
		for (auto& gate : mGameObjectsGateSink) {
			gate->process(gameObject);
		}

		this->mGameObjectsSink.push_back(gameObject);
	}
}
void Techstorm::GameObjectRegistry::addGameObjectGate(IGameObjectGate* gameObjectGate) {
	if (gameObjectGate != nullptr) {
		this->mGameObjectsGateSink.push_back(gameObjectGate);
	}
}

void Techstorm::GameObjectRegistry::update()
{
	for (auto& obj : this->mGameObjectsSink) {
		obj->update();
	}
}

void Techstorm::GameObjectRegistry::render()
{
	for (auto& obj : this->mGameObjectsSink) {
		obj->render();
	}
}
