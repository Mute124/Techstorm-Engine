#include "FileSystem.h"
#include <raylib.h>
bool Techstorm::FileSystemIsProperlyFormatted(const char* rootPath, const char* directoryMapPath)
{
	return false;
}

Techstorm::FileSystemRegistry::FileSystemRegistry(const char* rootPath)
{
	FilePathList files = LoadDirectoryFilesEx(rootPath, nullptr, true);

	for (int i = 0; i < files.count; i++) {
		std::string path = files.paths[i];
		std::string filename = path.substr(path.find_last_of("\\") + 1);
		std::string extension = filename.substr(filename.find_last_of(".") + 1);

		FileSystemMeta meta;
		meta.path = path;
		meta.filename = filename;
		meta.extension = extension;

		this->files[filename] = meta;

		std::cout << "File: " << filename << std::endl << "\tat: " << path << std::endl << "\t\tWith Extension of : " << extension << std::endl;
	}
}
