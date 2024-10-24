#pragma once
#include "PhysicsCommon.h"
#include "../utils/Singleton.h"
#include <unordered_map>



namespace Techstorm {
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
}