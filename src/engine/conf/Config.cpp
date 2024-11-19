#include "../fs/FileSystem.h"
#include "Config.h"
#include "libconfig.h++"
#include <any>
#include <memory>
#include <string>

// TODO: This needs to have readConfigFile implemented.
std::any LoadConfigFile(std::shared_ptr<Techstorm::FileMeta> fileMeta) {
	using namespace Techstorm;
	libconfig::Config cfg;

	cfg.readFile(fileMeta->path);

	return std::make_any<libconfig::Config*>(&cfg);
}

Techstorm::ConfigFileRegistry::ConfigFileRegistry()
{
	AddFileRegistryLoadFunction("cfg", LoadConfigFile);
}

Techstorm::ConfigFileRegistry::~ConfigFileRegistry()
{
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

libconfig::Setting& Techstorm::ConfigFileRegistry::lookup(const std::string& name)
{
	libconfig::Config const* cfg = std::any_cast<libconfig::Config*>(GetFile(name)->data);
	return cfg->lookup(name);
}

/*
libconfig::Config& Techstorm::ConfigFileRegistry::operator[](const std::string& name)
{
	// TODO: insert return statement here
}
*/
