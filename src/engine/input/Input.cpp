#include "Input.h"

inline int Techstorm::InputRegistry::registerAction(InputAction* action, std::function<void(InputAction*)> const& callback) {
	int id = mActions[action].size() + 1;
	
	mActions[action].try_emplace(id, callback);

	return id;
}

inline void Techstorm::InputRegistry::unregisterAction(InputAction* action) {
	mActions.erase(action);
}

inline void Techstorm::InputRegistry::unregisterCallback(InputAction* action, int id) {
	mActions[action].erase(id);
}

inline void Techstorm::InputRegistry::checkAll() {
	// Check all registered InputActions
	for(auto const& actions : mActions) {
		// Check all registered callbacks
		for (auto const& checks : actions.second) {
			checks.second(actions.first);
		}
	}
}
