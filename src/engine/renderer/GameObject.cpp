#include "GameObject.h"

/*inline Techstorm::IGameObject::IGameObject(int depth, const Model& model, const Vector3& position, const Vector3& rotationAxis, const Vector3& scale, float rotationAngle, const Color& tint)
	: depth(depth), model(model), position(position), rotationAxis(rotationAxis), scale(scale), rotationAngle(rotationAngle), tint(tint)
{
}

inline Techstorm::IGameObject::IGameObject(const Model& model, const Vector3& position, const Vector3& rotationAxis, const Vector3& scale, float rotationAngle, const Color& tint)
	: IGameObject(0, model, position, rotationAxis, scale, rotationAngle, tint)
{}

inline Techstorm::IGameObject::IGameObject(const Model & model, const Vector3 & position, const Vector3 & rotationAxis, float rotationAngle, const Color & tint)
	: IGameObject(0, model, position, rotationAxis, Vector3One() rotationAngle, tint)
{}

inline Techstorm::IGameObject::IGameObject(const Model & model, const Vector3 & position, const Vector3 & rotationAxis, float rotationAngle)
	: IGameObject(0, model, position, rotationAxis, Vector3One() rotationAngle, WHITE)
{}

inline Techstorm::IGameObject::IGameObject(const Model & model, const Vector3 & position, float rotationAngle)
	: IGameObject(0, model, position, Vector3One(), Vector3One() rotationAngle, WHITE)
{}*/




void Techstorm::GameObject::render() {
	//DrawModelEx(this->model, this->position, this->rotationAxis, this->rotationAngle, this->scale, this->tint);
	//DrawModel(model, position, 1.0f, tint);
}
void Techstorm::GameObject::update() {
	
}
void Techstorm::GameObject::destroy() {
	UnloadModel(this->model);
}

