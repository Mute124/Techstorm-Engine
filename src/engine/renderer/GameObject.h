#pragma once
#include "../math/Vector.h"
#include <raylib.h>
#include <raymath.h>
#include "../utils/DoublyLinkedList.h"

#include "../physics/PhysicsCommon.h"


namespace Techstorm {

	class IGameObject abstract {
	public:
		int depth = 0; // Defines what layer the object is on
		Model model;
		Vector3 position = Vector3Zero();
		Vector3 rotationAxis;
		Vector3 scale;
		float rotationAngle;
		Color tint = WHITE;
		//JPH::Body& body = IGameObject::sDummyBody;
/*		IGameObject(int depth, const Model& model, const Vector3& position, const Vector3& rotationAxis, const Vector3& scale, float rotationAngle, const Color& tint);
		IGameObject(const Model& model, const Vector3& position, const Vector3& rotationAxis, const Vector3& scale, float rotationAngle, const Color& tint);
		IGameObject(const Model& model, const Vector3& position, const Vector3& rotationAxis, float rotationAngle, const Color& tint);
		IGameObject(const Model& model, const Vector3& position, const Vector3& rotationAxis, float rotationAngle);
		IGameObject(const Model& model, const Vector3& position, float rotationAngle);
		IGameObject() = default;*/

		IGameObject() {

		}

		virtual ~IGameObject() = default;

		virtual void texture() = 0;
		virtual void render() = 0;

		// Physics interactions
		virtual void onCollisionValidation(IGameObject* other) = 0;
		virtual void onCollisionEnter(IGameObject* other) = 0;
		virtual void onCollisionExit(IGameObject* other) = 0;
		virtual void onCollisionStay(IGameObject* other) = 0;

		virtual void prePhysicsUpdate() = 0;
		virtual void update() = 0;
		virtual void postUpdate() = 0;

		virtual void destroy() = 0;
		virtual void cleanup() = 0;
		
		
	private:
	};


	class GameObject : public IGameObject {
	public:
		GameObject() : IGameObject() {}

		virtual void render() override;
		virtual void update() override;
		virtual void destroy() override;

		
	};
	
}