#include "GameObjectRegistry.h"

void Techstorm::GameObjectRegistry::addGameObject(IGameObject* gameObject)
{
	std::cout << "Pushing GameObject of type " << typeid(*gameObject).name() << " to GameObjectRegistry" << std::endl;
	if (gameObject != nullptr) {
		for (auto& gate : mGameObjectsGateSink) {
			gate->process(gameObject);
		}

		this->mGameObjectsSink.push_back(gameObject);
		std::cout << "GameObjectRegistry::addGameObject: GameObject added" << std::endl;
	}
	else {
		std::cout << "GameObjectRegistry::addGameObject: GameObject is null" << std::endl;
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
		//obj->update();
	}
}

void Techstorm::GameObjectRegistry::render()
{
	for (auto& drawCall : this->mStandaloneDrawCalls) {
		drawCall();
	}

	for (auto& obj : this->mGameObjectsSink) {

		obj->render();
	}
}
