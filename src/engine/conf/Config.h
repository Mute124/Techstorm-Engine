#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <libconfig.h++>
#include "../utils/Singleton.h"

namespace Techstorm {
	class ConfigFileRegistry : public Singleton<ConfigFileRegistry> {
	public:
		ConfigFileRegistry();
		~ConfigFileRegistry();

		void readConfigFiles();
		void readConfigFile(const std::string& name);
		void writeConfigFiles(); // Unimplemented

		void registerConfigFiles(const std::string& searchPath);
		void registerConfigFile(const std::string& name, const std::string& path);

		void unregisterConfigFiles();
		void unregisterConfigFile(const std::string& name);

		libconfig::Setting& lookup(const std::string& name);
		std::unordered_map<std::string, std::shared_ptr<RegisteredFile>> mConfigFiles;
	private:
	};
}
