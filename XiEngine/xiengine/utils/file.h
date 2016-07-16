#pragma once

#include <string>
#include <fstream>
#include <sstream>

namespace xiengine
{
	class File
	{
	public:
		File(const std::string& filePath);

		std::string getPath();

		static const bool loadFromFile(const std::string& filePath, const char* buffer);

	private:
		std::string path;
		std::ifstream file;
	};
}