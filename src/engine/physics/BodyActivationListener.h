#pragma once
#include "PhysicsCommon.h"

namespace Techstorm {
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
}