#include "RenderLayer.h"
void Techstorm::GameObjectsList::forwardTraverseFunction(Node<GameObject*>* current) {
	this->draw();
}

void Techstorm::GameObjectsList::backwardTraverseFunction(Node<GameObject*>* current) {
	this->draw();
}

void Techstorm::RenderLayer::draw()
{
	this->mGameObjects.displayForward();
}

void Techstorm::RenderLayer::drawGameObjectTraversal(GameObject* obj)
{
	obj->render();
}

void Techstorm::GameObjectsList::draw(GameObject* object)
{
	object->render();
}
