#include "GameObject.h"

void Techstorm::GameObject::render() {
	//DrawModelEx(this->model, this->position, this->rotationAxis, this->rotationAngle, this->scale, this->tint);
	//DrawModel(model, position, 1.0f, tint);
}
void Techstorm::GameObject::update() {
}
void Techstorm::GameObject::destroy() {
	UnloadModel(this->model);
}
