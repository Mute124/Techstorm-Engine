#pragma once
#include "../Common.h"
#include <raylib.h>
#include "../utils/Singleton.h"
#include "ELoggingMode.h"
#include "ELogLevel.h"

#include <source_location>
#include <string>
#include <spdlog/spdlog.h>
#include "spdlog/cfg/env.h"   // support for loading levels from the environment variable
#include "spdlog/fmt/ostr.h"  // support for user defined types
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <unordered_map>
#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <cstdarg>
#include <memory>
#include <vadefs.h>
#include <fmt/format.h>

#define TS_DEFAULT_LOG_LEVEL Techstorm::ELogLevel::TRACE


namespace Techstorm {	

	/// <summary>
	/// This is NOT what will print to the terminal, rather this is an interface where the logger will pass logging messages to. Use this for in-game consoles or something like that.
	/// </summary>
	class IConsoleSink abstract {
	public:
		virtual void parseLog(const std::string& message, ELogLevel level, const std::source_location& location) = 0;
		virtual void parsePrompt(const std::string& message) = 0;

		virtual std::vector<std::string>& getBuffer() = 0;
	};

	using DefaultColorSink = std::shared_ptr<spdlog::sinks::stdout_color_sink_mt>;

	template<typename ColorSinkType>
	class ITerminalSink abstract  {
	public:
		virtual void init() = 0;
		virtual std::string getFormat() = 0;

	protected:
		ColorSinkType mColorSink;
	};

	class TerminalSink : public ITerminalSink<DefaultColorSink>{
	public:
		void init() override;
		std::string getFormat() override;
		void setFormat(std::string const& format) { mFormat = format; }

	private:
		std::string mFormat = "[Techstorm] [%^%l%$] %v";
	};
	
	std::string CreateLogFileName();

	struct LoggerConfig {
		ELoggingMode mode = ELoggingMode::UNKNOWN;
		ELogLevel terminalLogLevel = ELogLevel::DEBUG;
		ELogLevel fileLogLevel = ELogLevel::TRACE;
		ELogLevel loggerLevel = ELogLevel::TRACE;
		
		std::string format = "[Techstorm] [%^%l%$] %v";
		std::string logFile =  CreateLogFileName();
	};

	spdlog::level::level_enum GetSpdlogLevel(ELogLevel level);

	class Logger : public Singleton<Logger> {
	public:

		Logger()
		{

		}

		void init(LoggerConfig config) {
			this->mConfig = config;
			InitSpdlog();
			log("Logger initialized");
		}

		void log(const std::string& message, ELogLevel level = ELogLevel::DEBUG, const std::source_location& location = std::source_location::current());

		static inline void RaylibLogCallback(int logLevel, const char* message, va_list args) {
			
			// Determine the length of the formatted string
			va_list argsCopy;
			va_copy(argsCopy, args);
			int length = vsnprintf(nullptr, 0, message, argsCopy);
			va_end(argsCopy);

			if (length < 0) {
				// Error handling if formatting fails
				
			}

			// Allocate a buffer of the required size (+1 for null terminator)
			std::string formattedString(length, '\0');

			// Format the string into the allocated buffer
			vsnprintf(&formattedString[0], length + 1, message, args);

			// -1 is being done here because we do not have the same number of levels as raylib.
			Logger::Instance().log(formattedString, static_cast<ELogLevel>(logLevel -1), std::source_location::current());
		}
	private:
		LoggerConfig mConfig;

		spdlog::logger* mLogger;



		void InitSpdlog()
		{
			auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			console_sink->set_level(GetSpdlogLevel(mConfig.terminalLogLevel));
			console_sink->set_pattern(mConfig.format);



			auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(mConfig.logFile, true);
			file_sink->set_level(GetSpdlogLevel(mConfig.fileLogLevel));
			
			std::string loggerName = typeid(*this).name();

			// shorten down the name to just the typename. In this case, "Techstorm::Logger"
			loggerName = loggerName.substr(loggerName.find_last_of("::") + 1);

			// remove anything to the right of the typename, so it looks like "Techstorm::Logger"
			loggerName = loggerName.substr(0, loggerName.find_last_of("::"));
	

			mLogger = new spdlog::logger(loggerName, {console_sink, file_sink});
			mLogger->set_level(GetSpdlogLevel(mConfig.loggerLevel));

			SetTraceLogCallback(&RaylibLogCallback);
		}
	};

	void Log(const std::string& message, ELogLevel level = ELogLevel::DEBUG, const std::source_location& location = std::source_location::current());
}