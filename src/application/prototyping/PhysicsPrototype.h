#pragma once
#include <Jolt/Jolt.h>

// Jolt includes
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <Jolt/Physics/Collision/Shape/HeightFieldShape.h>
#include <Jolt/Physics/Collision/PhysicsMaterialSimple.h>
#include <Jolt/Physics/Collision/Shape/MeshShape.h>
#include <Jolt/Physics/Collision/ObjectLayer.h>

#include <Jolt/Core/Color.h>
#include <Jolt/Core/Core.h>
#include <Jolt/Core/IssueReporting.h>
#include <Jolt/Core/JobSystem.h>
#include <Jolt/Core/Memory.h>
#include <Jolt/Core/StringTools.h>
#include <Jolt/Geometry/Triangle.h>
#include <Jolt/Math/Float3.h>
#include <Jolt/Math/Quat.h>
#include <Jolt/Math/Real.h>
#include <Jolt/Math/Vec3.h>
#include <Jolt/Physics/Body/Body.h>
#include <Jolt/Physics/Body/BodyID.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Body/MotionType.h>
#include <Jolt/Physics/Collision/BroadPhase/BroadPhaseLayer.h>
#include <Jolt/Physics/Collision/ContactListener.h>
#include <Jolt/Physics/Collision/Shape/Shape.h>
#include <Jolt/Physics/Collision/Shape/SubShapeIDPair.h>
#include <Jolt/Physics/EActivation.h>
#include <Jolt/Physics/Collision/Shape/HeightFieldShape.h>

#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/PhysicsMaterialSimple.h>
#include <Jolt/Physics/Collision/CastResult.h>
#include <Jolt/Physics/Collision/RayCast.h>

#include <Jolt/Physics/Collision/Shape/TriangleShape.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>


#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/ShapeCast.h>
#include <Jolt/Physics/Collision/CollisionCollectorImpl.h>

// Disable common warnings triggered by Jolt, you can use JPH_SUPPRESS_WARNING_PUSH / JPH_SUPPRESS_WARNING_POP to store and restore the warning state
JPH_SUPPRESS_WARNINGS

// If you want your code to compile using single or double precision write 0.0_r to get a Real value that compiles to double or float depending if JPH_DOUBLE_PRECISION is set or not.
using namespace JPH::literals;

// We're also using STL classes in this example
using namespace std;



// Callback for traces, connect this to your own trace function if you have one
static void TraceImpl(const char* inFMT, ...)
{
	// Format the message
	va_list list;
	va_start(list, inFMT);
	char buffer[1024];
	vsnprintf(buffer, sizeof(buffer), inFMT, list);
	va_end(list);

	// Print to the TTY
	cout << buffer << endl;
}

#ifdef JPH_ENABLE_ASSERTS

// Callback for asserts, connect this to your own assert handler if you have one
static bool AssertFailedImpl(const char* inExpression, const char* inMessage, const char* inFile, JPH::uint inLine)
{
	// Print to the TTY
	cout << inFile << ":" << inLine << ": (" << inExpression << ") " << (inMessage != nullptr ? inMessage : "") << endl;

	// Breakpoint
	return true;
};

#endif // JPH_ENABLE_ASSERTS

// Layer that objects can be in, determines which other objects it can collide with
// Typically you at least want to have 1 layer for moving bodies and 1 layer for static bodies, but you can have more
// layers if you want. E.g. you could have a layer for high detail collision (which is not used by the physics simulation
// but only if you do collision testing).
namespace Layers
{
	static constexpr JPH::ObjectLayer NON_MOVING = 0;
	static constexpr JPH::ObjectLayer MOVING = 1;
	static constexpr JPH::ObjectLayer TERRIAN = 2;
	static constexpr JPH::ObjectLayer NUM_LAYERS = 3;
};

/// Class that determines if two object layers can collide
class ObjectLayerPairFilterImpl : public JPH::ObjectLayerPairFilter
{
public:
	virtual bool					ShouldCollide(JPH::ObjectLayer inObject1, JPH::ObjectLayer inObject2) const override
	{
		using namespace JPH;
		switch (inObject1)
		{
		case Layers::NON_MOVING:
			return inObject2 == Layers::MOVING; // Non moving only collides with moving
		case Layers::MOVING:
			return true; // Moving collides with everything
		case Layers::TERRIAN:
			return inObject2 != Layers::TERRIAN;
		default:
			JPH_ASSERT(false);
			return false;
		}
	}
};

// Each broadphase layer results in a separate bounding volume tree in the broad phase. You at least want to have
// a layer for non-moving and moving objects to avoid having to update a tree full of static objects every frame.
// You can have a 1-on-1 mapping between object layers and broadphase layers (like in this case) but if you have
// many object layers you'll be creating many broad phase trees, which is not efficient. If you want to fine tune
// your broadphase layers define JPH_TRACK_BROADPHASE_STATS and look at the stats reported on the TTY.
namespace BroadPhaseLayers
{
	static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
	static constexpr JPH::BroadPhaseLayer MOVING(1);
	static constexpr JPH::uint NUM_LAYERS(2);
};

// BroadPhaseLayerInterface implementation
// This defines a mapping between object and broadphase layers.
class BPLayerInterfaceImpl final : public JPH::BroadPhaseLayerInterface
{
public:
	BPLayerInterfaceImpl()
	{
		// Create a mapping table from object to broad phase layer
		mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
		mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
	}

	virtual JPH::uint					GetNumBroadPhaseLayers() const override
	{
		return BroadPhaseLayers::NUM_LAYERS;
	}

	virtual JPH::BroadPhaseLayer			GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override
	{
		using namespace JPH;
		JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
		return mObjectToBroadPhase[inLayer];
	}

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
	virtual const char* GetBroadPhaseLayerName(BroadPhaseLayer inLayer) const override
	{
		switch ((BroadPhaseLayer::Type)inLayer)
		{
		case (BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING:	return "NON_MOVING";
		case (BroadPhaseLayer::Type)BroadPhaseLayers::MOVING:		return "MOVING";
		default:													JPH_ASSERT(false); return "INVALID";
		}
	}
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

private:
	JPH::BroadPhaseLayer					mObjectToBroadPhase[Layers::NUM_LAYERS];
};

/// Class that determines if an object layer can collide with a broadphase layer
class ObjectVsBroadPhaseLayerFilterImpl : public JPH::ObjectVsBroadPhaseLayerFilter
{
public:
	virtual bool				ShouldCollide(JPH::ObjectLayer inLayer1, JPH::BroadPhaseLayer inLayer2) const override
	{
		using namespace JPH;
		switch (inLayer1)
		{
		case Layers::NON_MOVING:
			return inLayer2 == BroadPhaseLayers::MOVING;
		case Layers::MOVING:
			return true;
		default:
			JPH_ASSERT(false);
			return false;
		}
	}
};

// An example contact listener
class MyContactListener : public JPH::ContactListener
{
public:
	// See: ContactListener
	virtual JPH::ValidateResult	OnContactValidate(const JPH::Body& inBody1, const JPH::Body& inBody2, JPH::RVec3Arg inBaseOffset, const JPH::CollideShapeResult& inCollisionResult) override
	{
		//cout << "Contact validate callback" << endl;

		// Allows you to ignore a contact before it is created (using layers to not make objects collide is cheaper!)
		return JPH::ValidateResult::AcceptAllContactsForThisBodyPair;
	}

	virtual void			OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override
	{
		//cout << "A contact was added" << endl;
	}

	virtual void			OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override
	{
		//cout << "A contact was persisted" << endl;
	}

	virtual void			OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair) override
	{
		//cout << "A contact was removed" << endl;
	}
};

// An example activation listener
class MyBodyActivationListener : public JPH::BodyActivationListener
{
public:
	virtual void		OnBodyActivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) override
	{
		//cout << "A body got activated" << endl;
	}

	virtual void		OnBodyDeactivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) override
	{
		//cout << "A body went to sleep" << endl;
	}
};


JPH::PhysicsSystem* GetPhysicsSystem();

struct AllocatedPhysicsResources {
	JPH::uint cMaxBodies = 65536;
	JPH::uint cNumBodyMutexes = 0;
	JPH::uint cMaxBodyPairs = 65536;
	JPH::uint cMaxContactConstraints = 1024;

	int preAllocatedMemory = 20 * 1024 * 1024;

	AllocatedPhysicsResources() {}
	AllocatedPhysicsResources(AllocatedPhysicsResources const& resources) : cMaxBodies(resources.cMaxBodies), cNumBodyMutexes(resources.cNumBodyMutexes), cMaxBodyPairs(resources.cMaxBodyPairs), cMaxContactConstraints(resources.cMaxContactConstraints) {}

	AllocatedPhysicsResources(const JPH::uint& cMaxBodies, const JPH::uint& cNumBodyMutexes, const JPH::uint& cMaxBodyPairs, const JPH::uint& cMaxContactConstraints)
		: cMaxBodies(cMaxBodies), cNumBodyMutexes(cNumBodyMutexes), cMaxBodyPairs(cMaxBodyPairs), cMaxContactConstraints(cMaxContactConstraints)
	{
	}
};

class PhysicsEngine : public Techstorm::Singleton<PhysicsEngine> {
public:
	PhysicsEngine() = default;

	void init(const AllocatedPhysicsResources resources) {
		if (!mIsInitialized) {
			mResources = resources;

			// Register allocation hook. In this example we'll just let Jolt use malloc / free but you can override these if you want (see Memory.h).
			// This needs to be done before any other Jolt function is called.
			JPH::RegisterDefaultAllocator();

			// Install trace and assert callbacks
			JPH::Trace = TraceImpl;
			JPH_IF_ENABLE_ASSERTS(JPH::AssertFailed = AssertFailedImpl;)

				// Create a factory, this class is responsible for creating instances of classes based on their name or hash and is mainly used for deserialization of saved data.
				// It is not directly used in this example but still required.
				JPH::Factory::sInstance = new JPH::Factory();

			// Register all physics types with the factory and install their collision handlers with the CollisionDispatch class.
			// If you have your own custom shape types you probably need to register their handlers with the CollisionDispatch before calling this function.
			// If you implement your own default material (PhysicsMaterial::sDefault) make sure to initialize it before this function or else this function will create one for you.
			JPH::RegisterTypes();

			// We need a temp allocator for temporary allocations during the physics update. We're
			// pre-allocating 10 MB to avoid having to do allocations during the physics update.
			// B.t.w. 10 MB is way too much for this example but it is a typical value you can use.
			// If you don't want to pre-allocate you can also use TempAllocatorMalloc to fall back to
			// malloc / free.
			//JPH::TempAllocatorImpl temp_allocator(mResources.preAllocatedMemory);
			mTempAllocator = new JPH::TempAllocatorImpl(mResources.preAllocatedMemory);

			// We need a job system that will execute physics jobs on multiple threads. Typically
			// you would implement the JobSystem interface yourself and let Jolt Physics run on top
			// of your own job scheduler. JobSystemThreadPool is an example implementation.
			mJobSystemThreadPool = new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, thread::hardware_concurrency() - 1);


			mPhysicsSystem = new JPH::PhysicsSystem();
			// Now we can create the actual physics system. This is not nullptr.
			mPhysicsSystem->Init(
				resources.cMaxBodies,
				resources.cNumBodyMutexes,
				resources.cMaxBodyPairs,
				resources.cMaxContactConstraints,
				mBroadPhaseLayerInterface,
				mObjectVsBroadPhaseLayerFilter,
				mObjectLayerPairFilter
			);

			// A body activation listener gets notified when bodies activate and go to sleep
			// Note that this is called from a job so whatever you do here needs to be thread safe.
			// Registering one is entirely optional.
			//MyBodyActivationListener body_activation_listener;
			mPhysicsSystem->SetBodyActivationListener(mBodyActivationListener);

			// A contact listener gets notified when bodies (are about to) collide, and when they separate again.
			// Note that this is called from a job so whatever you do here needs to be thread safe.
			// Registering one is entirely optional.
			//MyContactListener contact_listener;
			mPhysicsSystem->SetContactListener(mContactListener);

			// The main way to interact with the bodies in the physics system is through the body interface. There is a locking and a non-locking
			// variant of this. We're going to use the locking version (even though we're not planning to access bodies from multiple threads)
			mBodyInterfaceHolder = new BodyInterfaceHolder(mPhysicsSystem->GetBodyInterface());

		}
	}

	void update(const float cDeltaTime) {
		mPhysicsSystem->Update(cDeltaTime, mCollisionSteps, 4, mTempAllocator, mJobSystemThreadPool);
	}

	void optimizeBroadPhase() {
		mPhysicsSystem->OptimizeBroadPhase();
	}

	JPH::BodyInterface& getBodyInterface() const { return mBodyInterfaceHolder->bodyInterface; }
	JPH::PhysicsSystem* mPhysicsSystem = nullptr;									// The physics system that simulates the world
private:
	// A work around to keep the body interface references.
	class BodyInterfaceHolder {
	public:
		JPH::BodyInterface& bodyInterface;

		explicit BodyInterfaceHolder(JPH::BodyInterface& bodyInterface) : bodyInterface(bodyInterface) {}
		~BodyInterfaceHolder() {}


	};
	//float					mUpdateFrequency = 60.0f;									// Physics update frequency, measured in Hz (cycles per second)
	int						mCollisionSteps = 1;										// How many collision detection steps per physics update

	BodyInterfaceHolder* mBodyInterfaceHolder;

	bool mIsInitialized = false;
	AllocatedPhysicsResources mResources;

	JPH::TempAllocator* mTempAllocator = nullptr;
	JPH::JobSystem* mJobSystemThreadPool = nullptr;
	BPLayerInterfaceImpl mBroadPhaseLayerInterface;
	ObjectVsBroadPhaseLayerFilterImpl mObjectVsBroadPhaseLayerFilter;
	ObjectLayerPairFilterImpl mObjectLayerPairFilter;

	JPH::ContactListener* mContactListener = nullptr;									// Contact listener implementation
	JPH::PhysicsSettings  mPhysicsSettings;											// Main physics simulation settings
	JPH::BodyActivationListener* mBodyActivationListener = nullptr;					// Body activation listener implementation
};


JPH::PhysicsSystem* GetPhysicsSystem() {
	return PhysicsEngine::Instance().mPhysicsSystem;
}