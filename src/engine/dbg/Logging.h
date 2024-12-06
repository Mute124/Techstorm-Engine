#pragma once

#include "../utils/Singleton.h"
#include "ELoggingMode.h"
#include "ELogLevel.h"

#include <source_location>
#include <string>

namespace Techstorm {	

	/// <summary>
	/// This is NOT what will print to the terminal, rather this is an interface where the logger will pass logging messages to. Use this for in-game consoles or something like that.
	/// </summary>
	class IConsoleLogger abstract {
	public:
	};

	class Logger : public Singleton<Logger> {
	public:

		Logger();

		void Log(const std::string& message, const std::source_location& location = std::source_location::current());
	};
}