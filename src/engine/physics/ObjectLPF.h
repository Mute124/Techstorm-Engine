#pragma once
#include "PhysicsCommon.h"
#include "Layers.h"
namespace Techstorm {

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

		static LPFRelationships layerRelationships;

		virtual bool ShouldCollide(ObjectLayer inObject1, ObjectLayer inObject2) const override
		{
#ifdef TS_DYNAMIC_LAYERS
			PhysicsLayerRegistry& registry = GetPhysicsLayerRegistry();
			if (!registry.LayerExists(registry.GetLayerName(inObject1)) || !registry.LayerExists(registry.GetLayerName(inObject2)))
			{
				return false;
			}
#endif

			return layerRelationships.ShouldCollide(inObject1, inObject2);

		}
	};
}