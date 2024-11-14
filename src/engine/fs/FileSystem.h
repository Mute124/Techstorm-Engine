#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>

namespace Techstorm {
	using DirectoryFiles = std::vector<std::string>;

	using FileSystemMeta = struct {
		std::string extension;
		std::string path;
		std::string filename;
	};

	bool FileSystemIsProperlyFormatted(const char* rootPath, const char* directoryMapPath);

	//DirectoryFiles GetDirectoryFiles(const char* directoryMapPath);

	class FileSystemRegistry {
	public:
		FileSystemRegistry(const char* rootPath);
	private:

		std::unordered_map<std::string, FileSystemMeta> files;
	};
}
