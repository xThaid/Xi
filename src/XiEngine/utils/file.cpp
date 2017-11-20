#include "file.h"

#include "logger.h"

File::File(const std::string& filePath)
{
	path = filePath;

	if (!exist())
		Logger::warn("File " + path + " doesn't exist");
}

std::string File::loadText()
{
	std::ifstream file;

	file.exceptions(std::ifstream::badbit);

	try
	{
		file.open(path);
		std::stringstream stream;
		stream << file.rdbuf();
		file.close();
		return stream.str();
	}
	catch (std::ifstream::failure e)
	{
		return "";
	}
}

bool File::exist()
{
	std::ifstream f(path);
	return f.good();
}