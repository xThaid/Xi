#pragma once

#include <string>
#include <fstream>
#include <sstream>

class File
{
public:
	File(const std::string& filePath);

	std::string loadText();

	inline std::string getPath() { return path; }
	inline std::string getFileName() { return fileName; }
	inline std::string getDirectory() { return directory; }

private:
	std::string path;
	std::string fileName;
	std::string directory;

	bool exist();
};
