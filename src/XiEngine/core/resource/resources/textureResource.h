#pragma once

#include "../resource.h"
#include "../resourceFactory.h"

namespace xiengine
{
	class Texture : public Resource
	{
		
	};

	class TextureFactory : public ResourceFactory
	{
	protected:
		void load();
		void unload();
		size_t getSize();

		ResourceType getTypeOfResource();
	};

}