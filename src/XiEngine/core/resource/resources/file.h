#pragma once

#include "../resource.h"
#include "../resourceFactory.h"

namespace xiengine
{
	class File : public Resource
	{
	private:
		char* data;
	};

	class FileFactory : public ResourceFactory
	{
	public:
		FileFactory(std::string filePath);

	protected:
		Resource* load();
		void unload();
		size_t getSize();

		ResourceType getTypeOfResource();

	private:
		std::string filePath;
	};
}