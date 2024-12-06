#pragma once
#include "../utils/Gate.h"
#include "IGameObject.h"
namespace Techstorm {
	/// <summary>
	/// Same thing as a gate, but for game objects.
	/// </summary>
	/// <seealso cref="Gate&lt;GameObject*&gt;" />
	class IGameObjectGate abstract : public IGate<IGameObject*> {
	public:
	};
}
