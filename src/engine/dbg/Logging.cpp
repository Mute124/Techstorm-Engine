#include "Logging.h"
#include "../Common.h"


void Techstorm::Logger::log(const std::string& message, ELogLevel level, const std::source_location& location)
{
    std::string locFileName = location.file_name();

    // shorten the filename to only the last part of it
	locFileName = locFileName.substr(locFileName.find_last_of("/\\") + 1);


    int locLine = location.line();

    std::string finalMessage = "[" + locFileName + ":" + std::to_string(locLine) + "] " + message;

    switch (level)
    {
    case Techstorm::ELogLevel::TRACE:
        mLogger->trace(finalMessage);
        break;
    case Techstorm::ELogLevel::DEBUG:
		mLogger->debug(finalMessage);
        break;
    case Techstorm::ELogLevel::INFO:
		mLogger->info(finalMessage);
        break;
    case Techstorm::ELogLevel::WARNING:
		mLogger->warn(finalMessage);
        break;
    case Techstorm::ELogLevel::ERROR:
		mLogger->error(finalMessage);
        break;
    case Techstorm::ELogLevel::FATAL:
		mLogger->critical(finalMessage);
        break;
    case Techstorm::ELogLevel::NONE:
        break;
    default:
#ifdef RELEASE
        // if on release, log this as an error
        std::string failMsg = "Failed to log the message: " + finalMessage;
        failMsg << "Because the log level " << level << " is not supported!";
		mLogger->error(failMsg);

#else
		mLogger->trace(finalMessage);
#endif
        break;
    }
}

void Techstorm::TerminalSink::init()
{
    mColorSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    mColorSink->set_level(spdlog::level::warn);
    mColorSink->set_pattern(mFormat);
}

std::string Techstorm::TerminalSink::getFormat()
{
    return this->mFormat;
}

std::string Techstorm::CreateLogFileName() {
    // Filename should follow this format: YYYY-MM-DD_HH-MM-SS.log
    time_t now = time(0);
    struct tm tstruct;
    localtime_s(&tstruct, &now);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", &tstruct);

    std::string name = std::string(TS_TEMP_DIR);
	name += "logs/";
	name += std::string(buf);
	name += ".log";

    return name;
}

spdlog::level::level_enum Techstorm::GetSpdlogLevel(ELogLevel level) {
    return static_cast<spdlog::level::level_enum>(level);
}

void Techstorm::Log(const std::string& message, ELogLevel level, const std::source_location& location) {
    Logger::Instance().log(message, level, location);
}
