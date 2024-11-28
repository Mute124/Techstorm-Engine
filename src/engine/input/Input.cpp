#include "Input.h"

int Techstorm::InputRegistry::registerActionCallback(InputAction* action, std::function<void(InputAction*)> const& callback) {
	// Since callbacks are stored in an unordered_map, the next available id/slot is the map's size + 1.
	int id = mActions[action].size() + 1;
	
	mActions[action].try_emplace(id, callback);

	return id;
}

void Techstorm::InputRegistry::unregisterAction(InputAction* action) {
	mActions.erase(action);
}

void Techstorm::InputRegistry::unregisterCallback(InputAction* action, int id) {
	mActions[action].erase(id);
}

void Techstorm::InputRegistry::checkAll() {
	/*
	* Iterate through all registered actions in mActions (and then through all of it's callbacks)
	*/
	for(auto const& actions : mActions) {

		// Check all registered callbacks
		for (auto const& checks : actions.second) {
			checks.second(actions.first);
		}
	
	}
}
#ifdef TS_ENABLE_CONTROLLER_SUPPORT



#endif