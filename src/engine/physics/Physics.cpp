#include "Physics.h"

Techstorm::GamePhysics::GamePhysics()
{
}

Techstorm::GamePhysics::GamePhysics(const JPH::uint maxBodies, const JPH::uint numBodyMutexes, const JPH::uint maxBodyPairs, const JPH::uint maxContactConstraints)
{
}

void Techstorm::GamePhysics::preInit(const JPH::uint maxBodies, const JPH::uint numBodyMutexes, const JPH::uint maxBodyPairs, const JPH::uint maxContactConstraints)
{
	/*JPH::RegisterDefaultAllocator();

	// Install trace and assert callbacks
	JPH::Trace = TraceImpl;
	JPH::JPH_IF_ENABLE_ASSERTS(AssertFailed = AssertFailedImpl;)
		JPH::Factory::sInstance = new JPH::Factory();
	JPH::RegisterTypes();

	JPH::TempAllocatorImpl tempAllocator(10 * 1024 * 1024);
	JPH::JobSystemThreadPool jobSystem(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, std::thread::hardware_concurrency() - 1);

	const JPH::uint cMaxBodies = 1024;
	const JPH::uint cNumBodyMutexes = 0;
	const JPH::uint cMaxBodyPairs = 1024;
	const JPH::uint cMaxContactConstraints = 1024;

	// Now we can create the actual physics system.
	JPH::PhysicsSystem physics_system;
	physics_system.Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, this->mBroadPhaseLayerInterface, this->mObjectVsBroadPhaseLayerFilter, this->mObjectVsObjectLayerFilter);

	// A body activation listener gets notified when bodies activate and go to sleep
	// Note that this is called from a job so whatever you do here needs to be thread safe.
	// Registering one is entirely optional.
	MyBodyActivationListener body_activation_listener;
	physics_system.SetBodyActivationListener(&body_activation_listener);

	physics_system.SetContactListener(this->mContactListener);

	JPH::BodyInterface& body_interface = physics_system.GetBodyInterface();

	JPH::Vec3 floorPos = JPH::Vec3(100.0f, 1.0f, 100.0f);
	JPH::BoxShapeSettings floor_shape_settings(floorPos);

	// Create the shape
	JPH::ShapeSettings::ShapeResult floor_shape_result = floor_shape_settings.Create();
	JPH::ShapeRefC floor_shape = floor_shape_result.Get(); // We don't expect an error here, but you can check floor_shape_result for HasError() / GetError()

	JPH::BodyCreationSettings floor_settings(floor_shape, JPH::RVec3(0.0_r, -1.0_r, 0.0_r), JPH::Quat::sIdentity(), JPH::EMotionType::Static, Layers::NON_MOVING);

	// Create the actual rigid body
	JPH::Body* floor = body_interface.CreateBody(floor_settings); // Note that if we run out of bodies this can return nullptr

	// Add it to the world
	body_interface.AddBody(floor->GetID(), JPH::EActivation::DontActivate);

	// create a box shape
	JPH::Vec3 boxShape = JPH::Vec3(0.5f, 0.75f, 1.0f);
	JPH::RVec3 boxPos = JPH::RVec3(0, 10, 0);
	JPH::Body& box = *body_interface.CreateBody(JPH::BodyCreationSettings(new JPH::BoxShape(boxShape), boxPos, JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic, Layers::MOVING));

	// Add it to the world
	body_interface.AddBody(box.GetID(), JPH::EActivation::Activate);

	JPH::BodyCreationSettings sphere_settings(new JPH::SphereShape(0.5f), JPH::RVec3(0.0_r, 2.0_r, 0.0_r), JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic, Layers::MOVING);
	JPH::BodyID sphere_id = body_interface.CreateAndAddBody(sphere_settings, JPH::EActivation::Activate);

	body_interface.SetLinearVelocity(sphere_id, JPH::Vec3(0.0f, -5.0f, 0.0f));

	const float cDeltaTime = 1.0f / 60.0f;
	physics_system.OptimizeBroadPhase();

	// Now we're ready to simulate the body, keep simulating until it goes to sleep
	JPH::uint step = 0;

	// Remove the sphere from the physics system. Note that the sphere itself keeps all of its state and can be re-added at any time.
	body_interface.RemoveBody(sphere_id);

	// Destroy the sphere. After this the sphere ID is no longer valid.
	body_interface.DestroyBody(sphere_id);

	// Remove and destroy the floor
	body_interface.RemoveBody(floor->GetID());
	body_interface.DestroyBody(floor->GetID());

	// Unregisters all types with the factory and cleans up the default material
	JPH::UnregisterTypes();

	// Destroy the factory
	delete JPH::Factory::sInstance;
	JPH::Factory::sInstance = nullptr;

	//return 0;*/
}

void Techstorm::GamePhysics::init()
{
}

void Techstorm::GamePhysics::update()
{
}
