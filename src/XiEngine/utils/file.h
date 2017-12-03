#pragma once

#include <string>
#include <fstream>
#include <sstream>

class File
{
public:
	File(const std::string& filePath);

	std::string loadText();

	inline std::string getPath() const { return path; }
	inline std::string getFileName() const { return fileName; }
	inline std::string getDirectory() const { return directory; }

	bool exist();

private:
	std::string path;
	std::string fileName;
	std::string directory;
};
