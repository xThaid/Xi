#include "textureResource.h"

namespace xiengine
{
	void TextureFactory::load()
	{

	}

	void TextureFactory::unload()
	{

	}

	size_t TextureFactory::getSize()
	{

	}

	ResourceType TextureFactory::getTypeOfResource()
	{
		return typeid(Texture).hash_code;
	}
}