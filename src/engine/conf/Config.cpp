#include <iostream>
#include "Config.h"
#include <raylib.h>
Techstorm::ConfigFileRegistry::ConfigFileRegistry(const std::string& searchPath)
{
	/*
		FilePathList files = LoadDirectoryFilesEx(searchPath.c_str(), nullptr, true);

		for (int i = 0; i < files.count; i++) {
			std::string path = files.paths[i];
			std::string filename = path.substr(path.find_last_of("\\") + 1);
			std::string extension = filename.substr(filename.find_last_of(".") + 1);

			//std::cout << "File: " << filename << std::endl << "\tat: " << path << std::endl << "\t\tWith Extension of : " << extension << std::endl;
		}
	*/
}

Techstorm::ConfigFileRegistry::ConfigFileRegistry()
{
}

Techstorm::ConfigFileRegistry::~ConfigFileRegistry()
{
}
