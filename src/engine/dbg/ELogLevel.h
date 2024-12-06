#pragma once
#include <cstdint>

namespace Techstorm {	
	/// <summary>
	/// What level of logging to use. This will affect the output color, severity, etc. 
	/// \note This is not the same as spdlog's log level. Also, this inherits from uint8_t.
	/// </summary>
	enum class ELogLevel : uint8_t {
		TRACE = 0,
		DEBUG,
		INFO,
		WARNING,
		ERROR,
		FATAL
	};
}