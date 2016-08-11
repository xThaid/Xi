#include "file.h"

namespace xiengine
{

	FileFactory::FileFactory(std::string filePath) :
		filePath(filePath)
	{

	}

	Resource* FileFactory::load()
	{

	}

	void FileFactory::unload()
	{

	}

	size_t FileFactory::getSize()
	{

	}

	ResourceType FileFactory::getTypeOfResource()
	{
		return typeid(File).hash_code;
	}
}