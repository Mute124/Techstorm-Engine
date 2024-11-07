#pragma once
#include <unordered_map>
#include <string>
#include <libconfig.h++>

namespace Techstorm {
	class ConfigFileRegistry {
	public:
		ConfigFileRegistry(const std::string& searchPath);
		ConfigFileRegistry();
		~ConfigFileRegistry();

	protected:
		std::unordered_map<std::string, libconfig::Config> mRegistry;
	};
}
