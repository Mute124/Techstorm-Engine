#pragma once
#include "PhysicsCommon.h"
#include "BroadPhaseLayerRegistry.h"
#include "Layers.h"
namespace Techstorm {
	class ObjectVsBroadPhaseLayerFilter : public JPH::ObjectVsBroadPhaseLayerFilter {
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
				JPH_ASSERT(false);
				return false;
			}
		}
#endif
	};
}