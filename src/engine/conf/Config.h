#pragma once
#include <unordered_map>
#include <string>
#include <libconfig.h++>

namespace Techstorm {
	class ConfigFileRegistry {
	public:
		explicit ConfigFileRegistry(const std::string& searchPath);
		ConfigFileRegistry();
		~ConfigFileRegistry();

	private:
		std::unordered_map<std::string, libconfig::Config> mRegistry;
	};
}
