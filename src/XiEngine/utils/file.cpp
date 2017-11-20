#include "file.h"

File::File(const std::string& filePath)
{
	path = filePath;
		
	file = std::ifstream();
}


std::string File::getPath()
{
	return path;
}


const bool File::loadFromFile(const std::string& pathToFile, const char* buffer)
{
	std::ifstream file;

	file.exceptions(std::ifstream::badbit);

	try
	{
		file.open(pathToFile);
		std::stringstream stream;
		stream << file.rdbuf();
		file.close();
		buffer = stream.str().c_str();
	}
	catch (std::ifstream::failure e)
	{
		//TODO error

		return false;
	}

	return true;
}