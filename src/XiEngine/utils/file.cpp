#include "file.h"

#include "../utils/logger.h"

File::File(const std::string& filePath) :
	path_(filePath)
{
	int index = path_.find_last_of('/');
	if (index != std::string::npos)
	{
		fileName_ = path_.substr(index + 1);
		directory_ = path_.substr(0, index);
	}
	else
	{
		fileName_ = path_;
		directory_ = "";
	}

	if (!exist())
		Logger::warn("File " + path_ + " doesn't exist");
}

std::string File::loadText() const
{
	std::ifstream file_;

	file_.exceptions(std::ifstream::badbit);

	try
	{
		file_.open(path_);
		std::stringstream stream;
		stream << file_.rdbuf();
		file_.close();
		return stream.str();
	}
	catch (std::ifstream::failure e)
	{
		return "";
	}
}

bool File::exist() const
{
	std::ifstream f(path_);
	return f.good();
}