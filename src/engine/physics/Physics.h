#pragma once
//#include "PhysicsCommon.h"
//#include "ObjectLPF.h"
//#include "ObjectVsBroadPhaseLayerFilter.h"
//#include "ObjectContactListener.h"
//#include "Layers.h"
//#include "BPLayerInterface.h"
//#include "BodyActivationListener.h"

namespace Techstorm {
	
	using PhysicsMaxes = struct PhysicsMaxes {
		// This is the max amount of rigid bodies that you can add to the physics system. If you try to add more you'll get an error.
		// Note: This value is low because this is a simple test. For a real project use something in the order of 65536.
		const JPH::uint cMaxBodies = 1024;

		// This determines how many mutexes to allocate to protect rigid bodies from concurrent access. Set it to 0 for the default settings.
		const JPH::uint cNumBodyMutexes = 0;

		// This is the max amount of body pairs that can be queued at any time (the broad phase will detect overlapping
		// body pairs based on their bounding boxes and will insert them into a queue for the narrowphase). If you make this buffer
		// too small the queue will fill up and the broad phase jobs will start to do narrow phase work. This is slightly less efficient.
		// Note: This value is low because this is a simple test. For a real project use something in the order of 65536.
		const JPH::uint cMaxBodyPairs = 1024;

		// This is the maximum size of the contact constraint buffer. If more contacts (collisions between bodies) are detected than this
		// number then these contacts will be ignored and bodies will start interpenetrating / fall through the world.
		// Note: This value is low because this is a simple test. For a real project use something in the order of 10240.
		const JPH::uint cMaxContactConstraints = 1024;
	};

	// TODO: Create physics world class and finish IPhysicsInitializer

	class IPhysicsInitializer abstract {
	public:

		

		virtual void preInit() = 0;
		virtual void init() = 0;

		

	};

	class PhysicsInitializer : public IPhysicsInitializer {
	public:
		virtual void preInit() override;
		virtual void init() override;
	};
}