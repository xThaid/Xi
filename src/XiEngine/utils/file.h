#pragma once

#include <string>
#include <fstream>
#include <sstream>

class File
{
public:
	File(const std::string& filePath);

	std::string loadText();
private:
	std::string path;

	bool exist();
};
