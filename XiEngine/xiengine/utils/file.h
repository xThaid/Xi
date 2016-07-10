#pragma once

#include <string>
#include <fstream>
#include <sstream>

namespace TDEngine
{
	class File
	{
	public:
		File(const std::string& filePath);
		~File();

		void open();
		void close();

		std::string getPath();

		static const bool loadFromFile(const std::string& filePath, const char* buffer);

	private:
		std::string path;
		std::ifstream file;

		bool open;
	};
}