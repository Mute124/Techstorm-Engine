#pragma once
#include <eventpp/eventdispatcher.h>

namespace Techstorm {
	using InputEvents = eventpp::EventDispatcher<int, void()>;

	class InputDispatcher {
	public:
		void update();

		void addObserver(int id, void(*callback)());
	private:
		InputEvents mEvents;
	};
}