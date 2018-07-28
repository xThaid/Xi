#pragma once

#include "../precompiled.h"

class File
{
public:
	File(const std::string& filePath);

	std::string loadText() const;

	inline std::string getPath() const { return path_; }
	inline std::string getFileName() const { return fileName_; }
	inline std::string getDirectory() const { return directory_; }

	bool exist() const;

private:
	std::string path_;
	std::string fileName_;
	std::string directory_;
};
