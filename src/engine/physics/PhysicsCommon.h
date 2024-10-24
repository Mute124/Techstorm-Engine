#pragma once
#define TS_ENABLE_ASSERTS
#ifdef TS_ENABLE_ASSERTS
#define JPH_ENABLE_ASSERTS
#endif


#ifdef TS_SUPPRESS_WARNINGS
#define JPH_SUPPRESS_WARNINGS
#endif

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
#endif

#ifndef TS_PHYSICS_LAYERS
#define TS_PHYSICS_LAYERS()								\
	namespace Layers									\
	{													\
		static constexpr ObjectLayer NON_MOVING = 0;	\
		static constexpr ObjectLayer MOVING = 1;		\
		static constexpr ObjectLayer NUM_LAYERS = 2;	\
	};													
#endif


#include <Jolt.h>

// Jolt includes
#include <RegisterTypes.h>
#include <Core/Factory.h>
#include <Core/TempAllocator.h>
#include <Core/JobSystemThreadPool.h>
#include <Physics/PhysicsSettings.h>
#include <Physics/PhysicsSystem.h>
#include <Physics/Collision/Shape/BoxShape.h>
#include <Physics/Collision/Shape/SphereShape.h>
#include <Physics/Body/BodyCreationSettings.h>
#include <Physics/Body/BodyActivationListener.h>
#include <Physics/Collision/Shape/BoxShape.h>
#include <Physics/Body/BodyCreationSettings.h>
#include <Physics/Vehicle/VehicleConstraint.h>
#include <Physics/Constraints/HingeConstraint.h>
#include <Physics/Collision/CollisionCollectorImpl.h>
#include <Physics/Collision/RayCast.h>
#include <Physics/Collision/CastResult.h>
#include <Physics/Collision/Shape/BoxShape.h>
#include <Physics/Collision/Shape/CylinderShape.h>
#include <Physics/Collision/Shape/SphereShape.h>
#include <Physics/Collision/Shape/OffsetCenterOfMassShape.h>
#include <Physics/Vehicle/TrackedVehicleController.h>
#include <Physics/Collision/GroupFilterTable.h>
#include <Physics/Body/BodyCreationSettings.h>


#include "../Common.h"

namespace Techstorm {


		static void TraceImpl(const char* inFMT, ...) {
			// Format the message
			va_list list;
			va_start(list, inFMT);
			char buffer[1024];
			vsnprintf(buffer, sizeof(buffer), inFMT, list);
			va_end(list);

			// Print to the TTY
			std::cout << buffer << std::endl;
		}
		
#ifdef TS_ENABLE_ASSERTS
		// TODO: make this use the logging functionality
		static bool AssertFailedImpl(const char* expression, const char* message, const char* file, JPH::uint line) {
			// Print to the TTY
			std::cout << file << ":" << line << ": (" << expression << ") " << (message != nullptr ? message : "") << std::endl;

			// Breakpoint
			return true;
		}
#endif

		struct ObjectContactData {
			const JPH::Body& other;
			JPH::RVec3Arg baseOffset;
			const JPH::CollideShapeResult& collisionResult;
		};
}