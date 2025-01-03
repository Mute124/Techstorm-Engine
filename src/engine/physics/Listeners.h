#pragma once
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/Body.h>
#include <Jolt/Physics/Collision/ContactListener.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>

namespace Techstorm {
	// An example contact listener
	class ObjectContactListener : public JPH::ContactListener
	{
	public:
		// See: ContactListener
		virtual JPH::ValidateResult	OnContactValidate(const JPH::Body& inBody1, const JPH::Body& inBody2, JPH::RVec3Arg inBaseOffset, const JPH::CollideShapeResult& inCollisionResult) override;

		virtual void			OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override;

		virtual void			OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override;

		virtual void			OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair) override;
	};

	// An example activation listener
	class MyBodyActivationListener : public JPH::BodyActivationListener
	{
	public:
		virtual void		OnBodyActivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) override;

		virtual void		OnBodyDeactivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) override;
	};
}