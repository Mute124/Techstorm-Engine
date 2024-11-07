#pragma once
#include "PhysicsCommon.h"

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
#include "../renderer/GameObjectRegistry.h"

// All Jolt symbols are in the JPH namespace

// We're also using STL classes in this example
//using namespace std;
#define TS_NON_MOVING_LAYER_NAME "non-moving"
#define TS_MOVING_LAYER_NAME "moving"
#define TS_NUM_LAYERS_NAME "num-layers"

#define TS_NON_MOVING_LAYER Techstorm::PhysicsLayerRegistry::GetLayer(TS_NON_MOVING_LAYER_NAME)
#define TS_MOVING_LAYER Techstorm::PhysicsLayerRegistry::GetLayer(TS_MOVING_LAYER_NAME)
#define TS_NUM_LAYERS Techstorm::PhysicsLayerRegistry::GetLayer(TS_NUM_LAYERS_NAME)

JPH_SUPPRESS_WARNINGS
using namespace JPH;
using namespace JPH::literals;

namespace Techstorm {
	static inline void TraceImpl(const char* inFMT, ...) {
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
	static inline bool AssertFailedImpl(const char* expression, const char* message, const char* file, JPH::uint line) {
		// Print to the TTY
		std::cout << file << ":" << line << ": (" << expression << ") " << (message != nullptr ? message : "") << std::endl;

		// Breakpoint
		return true;
	}
#endif
	using ObjectLayer = JPH::ObjectLayer;

#ifdef TS_DYNAMIC_LAYERS

#ifndef TS_SILENCE_UNIMPLEMENTED_ERRORS
#error "Dynamic layers not supported yet"
#endif

	class PhysicsLayerRegistry : public Singleton<PhysicsLayerRegistry> {
	public:

		static inline void AddDefaultLayers() {
			NewLayer("non-moving");
			NewLayer("moving");
			NewLayer("num-layers");
		}

		static inline void NewLayer(ObjectLayer layer, const std::string& name) {
			PhysicsLayerRegistry& registryInstance = GetInstance();
			registryInstance.mLayerMap[name] = layer;
			registryInstance.mLayerMapReverse[layer] = name;
		}

		static inline void NewLayer(const std::string& name) {
			uint8_t& layerCount = GetInstance().mLayerCount;

			NewLayer(layerCount, name);

			layerCount++;
		}

		static inline ObjectLayer& GetLayer(const std::string& name) {
			return GetInstance().mLayerMap[name];
		}

		static inline std::string GetLayerName(const ObjectLayer& layer) {
			// Since there shouldnt be many layers, this should be okay.

			return GetInstance().mLayerMapReverse[layer];
		}

		static inline bool LayerExists(const std::string& name) {
			return GetInstance().mLayerMap.find(name) != PhysicsLayerRegistry::Instance().mLayerMap.end();
		}

		static inline bool IsLayer(const std::string& name, ObjectLayer layer) {
			return GetInstance().mLayerMap[name] == layer;
		}

		static inline void RemoveLayer(const std::string& name) {
			PhysicsLayerRegistry& registryInstance = GetInstance();

			// IMPORTANT: Order matters here!
			registryInstance.mLayerMapReverse.erase(registryInstance.mLayerMap[name]); // removes first because the normal map contains the object layer (Has to be searched by name)
			registryInstance.mLayerMap.erase(name);
		}

		static inline void Clear() {
			GetInstance().mLayerMap.clear();
		}

		static inline std::uint16_t GetLayerCount() {
			return GetInstance().mLayerCount;
		}

		static inline PhysicsLayerRegistry& GetInstance() {
			return PhysicsLayerRegistry::Instance();
		}
	private:

		std::uint8_t mLayerCount = 0;

		std::unordered_map<std::string, ObjectLayer> mLayerMap;
		std::unordered_map<ObjectLayer, std::string> mLayerMapReverse; // used to find the name of a layer
	};

	PhysicsLayerRegistry& GetPhysicsLayerRegistry() {
		return PhysicsLayerRegistry::GetInstance();
	}
#else
	// Layer that objects can be in, determines which other objects it can collide with
	// Typically you at least want to have 1 layer for moving bodies and 1 layer for static bodies, but you can have more
	// layers if you want. E.g. you could have a layer for high detail collision (which is not used by the physics simulation
	// but only if you do collision testing).
	namespace Layers
	{
		static constexpr ObjectLayer NON_MOVING = 0;
		static constexpr ObjectLayer MOVING = 1;
		static constexpr ObjectLayer NUM_LAYERS = 2;
	};
#endif
	/*
	* Filters layer pairs.
	*/
	class ObjectLPF : public JPH::ObjectLayerPairFilter {
	public:

		// Handles the logic of what layers should collide with each other. Directly used by ObjectLPF
		class LPFRelationships {
		public:

			void newRelationship(ObjectLayer inObject1, ObjectLayer inObject2, bool inShouldCollide) {
				//this->mRelationships[{inObject1, inObject2}] = inShouldCollide;
			}

			void setRelationship(ObjectLayer inObject1, ObjectLayer inObject2, bool inShouldCollide) {
				//this->mRelationships[{inObject1, inObject2}] = inShouldCollide;
			}

			bool getRelationship(ObjectLayer inObject1, ObjectLayer inObject2) {
				return true;//this->mRelationships[{inObject1, inObject2}];
			}

			virtual bool ShouldCollide(JPH::ObjectLayer inObject1, JPH::ObjectLayer inObject2) {
				return true; //this->mRelationships[{inObject1, inObject2}];
			}

		private:

			std::unordered_map<std::pair<JPH::ObjectLayer, JPH::ObjectLayer>, bool> mRelationships;
		};

		//static inline LPFRelationships layerRelationships;

		virtual bool ShouldCollide(ObjectLayer inObject1, ObjectLayer inObject2) const override
		{
#ifdef TS_DYNAMIC_LAYERS
			PhysicsLayerRegistry& registry = GetPhysicsLayerRegistry();
			if (!registry.LayerExists(registry.GetLayerName(inObject1)) || !registry.LayerExists(registry.GetLayerName(inObject2)))
			{
				return false;
			}
#endif

			return false;
		}
	};

#ifdef TS_DYNAMIC_LAYERS
	class BroadPhaseLayerRegistry : public Singleton<BroadPhaseLayerRegistry> {
	public:

		static inline void AddDefaultLayers() {
			NewLayer("non-moving");
			NewLayer("moving");
			//NewLayer("num-layers");
		}

		static inline void NewLayer(JPH::BroadPhaseLayer layer, const std::string& name) {
			BroadPhaseLayerRegistry& registryInstance = GetInstance();
			registryInstance.mLayerMap[name] = layer;
			registryInstance.mLayerMapReverse[layer] = name;
		}

		static inline void NewLayer(const std::string& name) {
			uint8_t& layerCount = GetInstance().mLayerCount;

			NewLayer(JPH::BroadPhaseLayer(layerCount), name);

			layerCount++;
		}

		static inline JPH::BroadPhaseLayer& GetLayer(const std::string& name) {
			return GetInstance().mLayerMap[name];
		}

		static inline std::string GetLayerName(const JPH::BroadPhaseLayer& layer) {
			// Since there shouldnt be many layers, this should be okay.

			return GetInstance().mLayerMapReverse[layer];
		}

		static inline bool LayerExists(const std::string& name) {
			return GetInstance().mLayerMap.find(name) != BroadPhaseLayerRegistry::Instance().mLayerMap.end();
		}

		static inline bool IsLayer(const std::string& name, JPH::BroadPhaseLayer layer) {
			return GetInstance().mLayerMap[name] == layer;
		}

		static inline void RemoveLayer(const std::string& name) {
			BroadPhaseLayerRegistry& registryInstance = GetInstance();

			// IMPORTANT: Order matters here!
			registryInstance.mLayerMapReverse.erase(registryInstance.mLayerMap[name]); // removes first because the normal map contains the object layer (Has to be searched by name)
			registryInstance.mLayerMap.erase(name);
		}

		static inline void Clear() {
			GetInstance().mLayerMap.clear();
		}

		static inline std::uint16_t GetLayerCount() {
			return GetInstance().mLayerCount;
		}

		static inline BroadPhaseLayerRegistry& GetInstance() {
			return BroadPhaseLayerRegistry::Instance();
		}
	private:

		std::uint8_t mLayerCount = 0;

		std::unordered_map<std::string, JPH::BroadPhaseLayer> mLayerMap;
		std::unordered_map<JPH::BroadPhaseLayer, std::string> mLayerMapReverse; // used to find the name of a layer
	};

	BroadPhaseLayerRegistry& GetBroadPhaseLayerRegistry() {
		return BroadPhaseLayerRegistry::GetInstance();
	}
#else
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
#endif
	class ObjectVsBroadPhaseLF : public JPH::ObjectVsBroadPhaseLayerFilter {
	public:
		virtual bool ShouldCollide(JPH::ObjectLayer inLayer1, JPH::BroadPhaseLayer inLayer2) const override
		{
#ifdef TS_DYNAMIC_LAYERS
#ifndef TS_SILENCE_UNIMPLEMENTED_ERRORS
#error "Dynamic layers not supported yet"
#endif
#else
			switch (inLayer1)
			{
			case Layers::NON_MOVING:
				return inLayer2 == BroadPhaseLayers::MOVING;
			case Layers::MOVING:
				return true;
			default:
				//JPH_ASSERT(false);
				return false;
			}
		}
#endif
	};

	class ObjectContactListener : public JPH::ContactListener {
	public:
		// See: ContactListener
		virtual JPH::ValidateResult	OnContactValidate(const JPH::Body& inBody1, const JPH::Body& inBody2, JPH::RVec3Arg inBaseOffset, const JPH::CollideShapeResult& inCollisionResult) override
		{
			// Allows you to ignore a contact before it is created (using layers to not make objects collide is cheaper!)
			return JPH::ValidateResult::AcceptAllContactsForThisBodyPair;
		}

		virtual void			OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override
		{
		}

		virtual void			OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override
		{
		}

		virtual void			OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair) override
		{
		}
	};

	class BPLayerInterface : public JPH::BroadPhaseLayerInterface {
	public:
		BPLayerInterface()
		{
#ifdef TS_DYNAMIC_LAYERS
#ifndef TS_SILENCE_UNIMPLEMENTED_ERRORS
#error "Dynamic layers not supported yet"
#endif
#else
			//BroadPhaseLayerRegistry& layerRegistry = GetBroadPhaseLayerRegistry();
			// Create a mapping table from object to broad phase layer
			mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
			mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
#endif
		}

		virtual JPH::uint					GetNumBroadPhaseLayers() const override
		{
			return BroadPhaseLayers::NUM_LAYERS;
		}

		virtual JPH::BroadPhaseLayer			GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override
		{
			//JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
			return mObjectToBroadPhase[inLayer];
		}

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
		virtual const char* GetBroadPhaseLayerName(JPH::BroadPhaseLayer inLayer) const override
		{
			switch ((JPH::BroadPhaseLayer::Type)inLayer)
			{
			case (JPH::BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING:	return "NON_MOVING";
			case (JPH::BroadPhaseLayer::Type)BroadPhaseLayers::MOVING:		return "MOVING";
			default:													JPH_ASSERT(false); return "INVALID";
			}
		}
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

	private:
		JPH::BroadPhaseLayer					mObjectToBroadPhase[Layers::NUM_LAYERS];
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

	// TODO: Create physics world class and finish IPhysicsInitializer
	class GamePhysics {
	public:

		GamePhysics();
		GamePhysics(const JPH::uint maxBodies, const JPH::uint numBodyMutexes, const JPH::uint maxBodyPairs, const JPH::uint maxContactConstraints);

		void init();

		void update();

	private:
		void preInit(const JPH::uint maxBodies, const JPH::uint numBodyMutexes, const JPH::uint maxBodyPairs, const JPH::uint maxContactConstraints);

		TempAllocator* mTempAllocator = nullptr;									// Allocator for temporary allocations
		JobSystem* mJobSystem = nullptr;										// The job system that runs physics jobs
		JobSystem* mJobSystemValidating = nullptr;								// The job system to use when validating determinism
		BPLayerInterface	mBroadPhaseLayerInterface;									// The broadphase layer interface that maps object layers to broadphase layers
		ObjectVsBroadPhaseLF mObjectVsBroadPhaseLayerFilter;					// Class that filters object vs broadphase layers
		ObjectLPF mObjectVsObjectLayerFilter;								// Class that filters object vs object layers
		PhysicsSystem* mPhysicsSystem = nullptr;									// The physics system that simulates the world
		ObjectContactListener* mContactListener = nullptr;									// Contact listener implementation
		PhysicsSettings			mPhysicsSettings;											// Main physics simulation settings
	};
}
