#include "../fs/FileSystem.h"
#include "Config.h"
#include "libconfig.h++"
#include <any>
#include <memory>
#include <string>
#include "../dbg/Logging.h"

std::any LoadConfigFile(std::shared_ptr<Techstorm::FileMeta> fileMeta) {
	using namespace Techstorm;

	return std::make_any<uint16_t>(3);
}

Techstorm::ConfigFileRegistry::ConfigFileRegistry()
{


}

Techstorm::ConfigFileRegistry::~ConfigFileRegistry()
{
}

void Techstorm::ConfigFileRegistry::init() {
	Log("Initializing config registry.");

	// only show this in the log file
	Log("Setting config file load functions.", ELogLevel::TRACE);
	AddFileRegistryLoadFunction("cfg", [](std::shared_ptr<FileMeta> fileMeta) {
		Log("Loading config file: " + fileMeta->path, ELogLevel::TRACE);
		libconfig::Config* conf = new libconfig::Config();
		conf->readFile(fileMeta->path);
		return std::make_any<libconfig::Config*>(conf);
	});
}

void Techstorm::ConfigFileRegistry::readConfigFiles()
{
}

void Techstorm::ConfigFileRegistry::readConfigFile(const std::string& name)
{
	std::shared_ptr<RegisteredFile> file = GetFile(name);
}

void Techstorm::ConfigFileRegistry::writeConfigFiles()
{
}

void Techstorm::ConfigFileRegistry::registerConfigFiles(const std::string& searchPath)
{
}

void Techstorm::ConfigFileRegistry::registerConfigFile(const std::string& name, const std::string& path)
{
}

void Techstorm::ConfigFileRegistry::unregisterConfigFiles()
{
}

void Techstorm::ConfigFileRegistry::unregisterConfigFile(const std::string& name)
{
}

libconfig::Setting& Techstorm::ConfigFileRegistry::lookup(const std::string& fileName, const std::string& lookupTarget)
{
	libconfig::Config const* conf = GetFile(fileName).get()->get<libconfig::Config*>();
	libconfig::Setting& setting = conf->lookup(lookupTarget);

	Log("Looking up value in :" + fileName + " for key: " + lookupTarget + " and found value: " + setting.c_str(), ELogLevel::TRACE);
	
	return setting;
	
}

/*
libconfig::Config& Techstorm::ConfigFileRegistry::operator[](const std::string& name)
{
	// TODO: insert return statement here
}
*/

Techstorm::ConfigFileRegistry& Techstorm::GetConfigFileRegistry() { return ConfigFileRegistry::Instance(); }

void Techstorm::InitializeConfigRegistry() { ConfigFileRegistry::Instance().init(); }

libconfig::Setting& Techstorm::LookupConfig(const std::string& fileName, const std::string& lookupTarget) { return ConfigFileRegistry::Instance().lookup(fileName, lookupTarget); }

const char* Techstorm::GetConfigString(std::string fileName, std::string lookupTarget) { return LookupConfig(fileName, lookupTarget).c_str(); }
