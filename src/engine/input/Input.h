#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>
#include <optional>
#include "../utils/Singleton.h"
namespace Techstorm {
	enum class EInputType {
		INPUT_KEYBOARD,
		INPUT_MOUSE,
		INPUT_CONTROLLER
	};

	enum class EInputTrigger {
		INPUT_TRIGGER_PRESSED,
		INPUT_TRIGGER_RELEASED,
		INPUT_TRIGGER_DOWN,
		INPUT_TRIGGER_UP,
		INPUT_TRIGGER_REPEAT
	};

	class InputAction {
	public:

		std::string name;
		int key;
		EInputType type;
		EInputTrigger trigger;
	};


	class InputRegistry : public Singleton<InputRegistry> {
	public:

		int registerAction(InputAction* action, std::function<void(InputAction*)> const& callback);

		void unregisterAction(InputAction* action);
		void unregisterCallback(InputAction* action, int id);
		
		void checkAll();

	private:
		std::unordered_map<InputAction*, std::unordered_map<int, std::function<void(InputAction*)>>> mActions;
	};
}