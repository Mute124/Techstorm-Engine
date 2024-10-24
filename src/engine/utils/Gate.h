#pragma once

namespace Techstorm {

	/*
	* A gate is a class that acts as, well, a gate! An example of it's use is in the GameObjectRegistry class. When an GameObject is added, it will first be passed through
	* all the gates before being added to the registry. Think of it as an assembly line.
	*/
	template<typename T>
	class Gate {
	public:
		virtual void process(T entree) = 0;
	};
}