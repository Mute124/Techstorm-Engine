#pragma once
#include "PhysicsCommon.h"
#include "../utils/Singleton.h"


#define TS_NON_MOVING_LAYER_NAME "non-moving"
#define TS_MOVING_LAYER_NAME "moving"
#define TS_NUM_LAYERS_NAME "num-layers"

#define TS_NON_MOVING_LAYER Techstorm::PhysicsLayerRegistry::GetLayer(TS_NON_MOVING_LAYER_NAME)
#define TS_MOVING_LAYER Techstorm::PhysicsLayerRegistry::GetLayer(TS_MOVING_LAYER_NAME)
#define TS_NUM_LAYERS Techstorm::PhysicsLayerRegistry::GetLayer(TS_NUM_LAYERS_NAME)

namespace Techstorm {
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
}