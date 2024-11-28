#include "Listeners.h"

// See: ContactListener

  JPH::ValidateResult Techstorm::ObjectContactListener::OnContactValidate(const JPH::Body& inBody1, const JPH::Body& inBody2, JPH::RVec3Arg inBaseOffset, const JPH::CollideShapeResult& inCollisionResult)
{
	//cout << "Contact validate callback" << endl;

	// Allows you to ignore a contact before it is created (using layers to not make objects collide is cheaper!)
	return JPH::ValidateResult::AcceptAllContactsForThisBodyPair;
}

  void Techstorm::ObjectContactListener::OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings)
{
	//cout << "A contact was added" << endl;
}

  void Techstorm::ObjectContactListener::OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings)
{
	//cout << "A contact was persisted" << endl;
}

  void Techstorm::ObjectContactListener::OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair)
{
	//cout << "A contact was removed" << endl;
}

  void Techstorm::MyBodyActivationListener::OnBodyActivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData)
{
	//cout << "A body got activated" << endl;
}

  void Techstorm::MyBodyActivationListener::OnBodyDeactivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData)
{
	//cout << "A body went to sleep" << endl;
}
