#pragma once
#include "../math/Vector.h"
#include <raylib.h>
#include <raymath.h>
#include "../utils/DoublyLinkedList.h"
#include "../physics/Physics.h"
namespace Techstorm {
	/// <summary>
	/// Represents an object that can be rendered in the screen. This is an abstract class that contains all the common properties of a game object.
	/// </summary>
	/// <remarks>
	/// <para>
	/// You may implement this yourself to create your own game objects and drawing code, or you can inherit from <see cref="Techstorm::GameObject" /> to use the default
	/// implementation. However, if you inherit from this class, be sure you have a basic understanding of Raylib's and OpenGL's rendering system. If not,
	/// see <see cref="https://learnopengl.com/"/> and <see cref="https://www.raylib.com/"/> for a good place to start. In addition, it is not advised for you to inherit this
	/// yourself because it will require you to implement rendering code. However, it is recommended if your game requires a rendering system that is not provided by default.
	/// </para>
	/// <inheritdoc />
	class IGameObject abstract {
	public:
		// Defines what layer the object is on
		int depth = 0;
		Model model;

		

		// positional variables
		Vector3 position = Vector3Zero();
		Vector3 rotationAxis;
		Vector3 scale;

		float rotationAngle;
		Color tint = WHITE;

		// constructors/destructors
		IGameObject() = default;
		virtual ~IGameObject() = default;

		/// <summary>
		/// Textures this instance.
		/// </summary>
		virtual void texture() = 0;

		/// <summary>
		/// Renders this instance. This is not a pure virtual and is empty because it is up to the user to use this as they see fit without forcing them to implement it.
		/// </summary>
		virtual void render() {}

		// Physics interactions

		/// <summary>
		/// Action on collision validation.
		/// </summary>
		/// <param name="other">The other game object.</param>
		virtual void onCollisionValidation(IGameObject* other) = 0;

		/// <summary>
		/// Action upon entering collision. This is called the frame the collision happens.
		/// </summary>
		/// <param name="other">The other game object.</param>
		virtual void onCollisionEnter(IGameObject* other) = 0;

		/// <summary>
		/// Action upon exiting collision.
		/// </summary>
		/// <param name="other">The other game object.</param>
		virtual void onCollisionExit(IGameObject* other) = 0;

		/// <summary>
		/// Action upon remaining in collision.
		/// </summary>
		/// <param name="other">The other game object.</param>
		/// <inheritdoc />
		virtual void onCollisionStay(IGameObject* other) = 0;

		/// <summary>
		/// Called right before the physics update. Do anything you need to do before the physics update here. Keep in mind that this can either run on the update thread or
		/// the physics thread, so make sure what you are doing is <b>thread safe</b>.
		/// </summary>
		/// <inheritdoc />
		virtual void prePhysicsUpdate() = 0;

		/// <summary>
		/// Updates this instance and is called every frame before texturing/rendering. Keep in mind that this will run on the update thread, so make sure what you are
		/// doing is <b>thread safe</b>.
		/// </summary>
		/// <inheritdoc />
		virtual void update() = 0;

		/// <summary>
		/// Called right after the update function, but before texturing/rendering. Keep in mind that this will run on the update thread, so make sure what you are doing is
		/// <b>thread safe</b>.
		/// </summary>
		/// <inheritdoc />
		virtual void postUpdate() = 0;

		/// <summary>
		/// Destroys this instance, and is called right before the object is removed from memory. This must be implemented by the user.
		/// </summary>
		/// <inheritdoc />
		virtual void destroy() = 0;

		/// <summary>
		/// Cleanups this instance.
		/// </summary>
		/// <inheritdoc />
		virtual void cleanup() = 0;

	private:
	};
	


	/// <summary>
	/// A game object that can be rendered to the screen. Inherits from <see cref="IGameObject" />, and already provides the basic rendering functionality. If you override this
	/// class, you should inherit the function.
	/// </summary>
	class GameObject : public IGameObject {
	public:
		GameObject() : IGameObject() {}

		/// <summary>
		/// Renders this instance. This is not a pure virtual and is empty because it is up to the user to use this as they see fit without forcing them to implement it.
		/// </summary>
		virtual void render() override;

		/// <summary>
		/// Updates this instance and is called every frame before texturing/rendering. Keep in mind that this will run on the update thread, so make sure what you are
		/// doing is <b>thread safe</b>.
		/// </summary>
		/// <inheritdoc />
		virtual void update() override;

		/// <summary>
		/// Destroys this instance, and is called right before the object is removed from memory. This must be implemented by the user.
		/// </summary>
		/// <inheritdoc />
		virtual void destroy() override;
	};
	/*struct PhysicsObjectSettings {
		const JPH::BodyCreationSettings cBodyCreationSettings;
		const JPH::EActivation activationState;
		JPH::BodyInterface& bodyInterface = GetBodyInterface();
	};
	class IPhysicsGameObject abstract : public IGameObject {
	public:
		JPH::BodyID id;
		JPH::BodyInterface& bodyInterface;

		IPhysicsGameObject(PhysicsObjectSettings const& settings) : IGameObject(), bodyInterface(settings.bodyInterface) {
			this->id = bodyInterface.CreateAndAddBody(settings.cBodyCreationSettings, settings.activationState);
		}

		virtual ~IPhysicsGameObject() {
			this->bodyInterface.RemoveBody(this->id);
		}
	};*/
}
