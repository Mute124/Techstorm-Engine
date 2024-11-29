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
	/// <para>
	/// The IGameObject class is abstract and cannot be instantiated directly. Instead, you should inherit from this class and implement the pure virtual functions. As of version 0.0.3, the pure 
	/// virtual functions are: <see cref="render()"/>, <see cref="texture()"/>, <see cref="update()"/>, <see cref="prePhysicsUpdate()"/>, <see cref="postUpdate()"/>, <see cref="destroy()"/>,
	/// and <see cref="cleanup()"/>. 
	/// </para>
	/// </remarks>
	/// <inheritdoc />
	class IGameObject abstract {
	public:
		// Defines what layer the object is on to prevent z-fighting
		/// \todo add support for multiple layers.
		int depth = 0;

		Model model;

		// positional variables that are used to draw the object
		Vector3 position = Vector3Zero();
		Vector3 rotationAxis;
		Vector3 scale;

		float rotationAngle;
		Color tint = WHITE;

		// constructors/destructors
		IGameObject() = default;
		virtual ~IGameObject() = default;

		/// <summary>
		/// This is a pure virtual function that is the drawing function for when objects are being textured to the render texture. If you do not have anything different to do here, then you may
		/// just call <see cref="render()" /> instead, but this must be implemented in order for the object to be rendered.
		/// </summary>
		virtual void texture() = 0;

		/// <summary>
		/// Renders this instance. This is not a pure virtual and is empty because it is up to the user to use this as they see fit without forcing them to implement it.
		/// </summary>
		virtual void render() {}

		/// <summary>
		/// Called right before the physics update. Do anything you need to do before the physics update here. 
		/// \note Keep in mind that this can either run on the update thread or the physics thread, so make sure what you are doing is <b>thread safe</b>.
		/// </summary>
		/// <inheritdoc />
		virtual void prePhysicsUpdate() = 0;

		/// <summary>
		/// Updates this instance and is called every frame before texturing/rendering. 
		/// \note Keep in mind that this will run on the update thread, so make sure what you are doing is <b>thread safe</b>.
		/// </summary>
		/// <inheritdoc />
		virtual void update() = 0;

		/// <summary>
		/// Called right after the update function, but before texturing/rendering. 
		/// \note Keep in mind that this will run on the update thread, so make sure what you are doing is <b>thread safe</b>.
		/// </summary>
		/// <inheritdoc />
		virtual void postUpdate() = 0;

		/// <summary>
		/// Destroys this instance, and is called right before the object is removed from memory. 
		/// \note This must be implemented by the user.
		/// </summary>
		/// <inheritdoc />
		virtual void destroy() = 0;

		/// <summary>
		/// Cleanups this instance.
		/// \note This must be implemented by the user.
		/// </summary>
		/// <inheritdoc />
		virtual void cleanup() = 0;

	private:
	};

	/// <summary>
	/// A game object that can be rendered to the screen. Inherits from <see cref="IGameObject" />, and already provides the basic rendering functionality.
	/// </summary>
	class GameObject : public IGameObject {
	public:
		// This is being used to avoid a redundant constructor
		using IGameObject::IGameObject;

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
		/// Called right before the physics update. Do anything you need to do before the physics update here. Keep in mind that this can either run on the update thread or
		/// the physics thread, so make sure what you are doing is <b>thread safe</b>.
		/// </summary>
		/// <inheritdoc />
		virtual void prePhysicsUpdate() override {};


		/// <summary>
		/// Called right after the update function, but before texturing/rendering. Keep in mind that this will run on the update thread, so make sure what you are doing is
		/// <b>thread safe</b>.
		/// </summary>
		/// <inheritdoc />
		virtual void postUpdate() override {};

		/// <summary>
		/// Destroys this instance, and is called right before the object is removed from memory. This must be implemented by the user.
		/// </summary>
		/// <inheritdoc />
		virtual void destroy() override;
	};

	class IPhysicsGameObject abstract : public IGameObject {
	public:
		JPH::BodyID id;
		JPH::BodyInterface& bodyInterface;

		IPhysicsGameObject(JPH::BodyCreationSettings const& bodySettings, JPH::EActivation activationState) : IGameObject(), bodyInterface(PhysicsEngine::Instance().getBodyInterface()) {
			this->id = bodyInterface.CreateAndAddBody(bodySettings, activationState);
		}

		virtual ~IPhysicsGameObject() override {
			this->bodyInterface.RemoveBody(this->id);
		}

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
	};
}
