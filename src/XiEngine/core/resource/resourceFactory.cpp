#include "resourceFactory.h"

#include "../../utils/logger.h"

namespace xiengine
{
	ResourceFactory::ResourceFactory() :
		loaded(false),
		forceLoaded(false)
	{
	}

	ResourceFactory::~ResourceFactory()
	{
		if (currentResource != nullptr)
			delete currentResource;
	}

	bool ResourceFactory::isLoaded()
	{
		return loaded;
	}

	void ResourceFactory::_load()
	{
		if (loaded)
			return;

		Resource* res = load();

		if (res != nullptr)
			loaded = true;

		currentResource = res;
	}

	void ResourceFactory::_unload()
	{
		if (!loaded)
			return;

		unload();
		loaded = false;

		delete currentResource;
	}

	void ResourceFactory::reference()
	{
		if (refCount == 0)
			_load();

		refCount++;
	}

	void ResourceFactory::dereference()
	{
		if (refCount == 0)
		{
			Logger::warn("Cant dereference " + name + " resouce when there arent any references");
			return;
		}

		refCount--;
		if (refCount == 0 && !forceLoaded)
			_unload();
	}

	void ResourceFactory::forceLoad()
	{
		forceLoaded = true;
		_load();
	}
}