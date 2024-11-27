#pragma once


#include <Jolt/Jolt.h>

#include <Jolt/Core/Core.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/IssueReporting.h>
#include <Jolt/Core/JobSystem.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Core/Memory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Collision/ContactListener.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/RegisterTypes.h>

#include "../Common.h"
#include "Layers.h"
#include "Listeners.h"
JPH_SUPPRESS_WARNINGS

using namespace JPH::literals;

namespace Techstorm {


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

	struct AllocatedPhysicsResources {
		JPH::uint cMaxBodies = 65536;
		JPH::uint cNumBodyMutexes = 0;
		JPH::uint cMaxBodyPairs = 65536;
		JPH::uint cMaxContactConstraints = 1024;

		int preAllocatedMemory = 20 * 1024 * 1024;

		AllocatedPhysicsResources();
		AllocatedPhysicsResources(AllocatedPhysicsResources const& resources);

		AllocatedPhysicsResources(const JPH::uint& cMaxBodies, const JPH::uint& cNumBodyMutexes, const JPH::uint& cMaxBodyPairs, const JPH::uint& cMaxContactConstraints);
	};

	class PhysicsEngine : public Techstorm::Singleton<PhysicsEngine> {
	public:
		PhysicsEngine() = default;

		void init(const AllocatedPhysicsResources resources);

		void update(const float cDeltaTime);

		void optimizeBroadPhase();

		JPH::BodyInterface& getBodyInterface() const;
		JPH::PhysicsSystem* mPhysicsSystem = nullptr;									// The physics system that simulates the world
	private:
		// A work around to keep the body interface references.
		class BodyInterfaceHolder {
		public:
			JPH::BodyInterface& bodyInterface;

			explicit BodyInterfaceHolder(JPH::BodyInterface& bodyInterface);
			~BodyInterfaceHolder();


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


}
