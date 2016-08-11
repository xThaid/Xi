#include "resourceManager.h"

#include <algorithm>
#include <typeinfo>

#include "resource.h"

#include "../../utils/logger.h"

namespace xiengine
{
	ResourceManager::ResourceManager()
	{
		lastID = 0;
	}

	ResourceManager::~ResourceManager()
	{
	}

	bool ResourceManager::addResource(const std::string& name, ResourceFactory& factory)
	{
		if (indices.find(name) != indices.end())
		{
			Logger::info(name + " resource has been already added!");
			return false;
		}

		factory.name = name;
		factories.push_back(factory);
		indices[name] = lastID;
		lastID++;

		return true;
	}

	template<class T>
	void ResourceManager::setDefaultResource(const std::string& name)
	{
		setDefaultResource(getResourceID(name));
	}

	template<class T>
	void ResourceManager::setDefaultResource(ResourceID id)
	{
		if (id == INVAILD_ID)
		{
			Logger::warn("Cannot set invaild ID to default resource!");
			return;
		}

		if (factories[id]->getTypeOfResource() != typeid(T).hash_code())
		{
			Logger::info(factories[id]->name + " resource isnt a " + typeid(T).name());
			return;
		}

		defaultResources[typeid(T)] = id;
		factories[id].forceLoad();
	}

	template<class T>
	ResourceID ResourceManager::getDefaultResourceID()
	{
		std::map<ResourceType, ResourceHandle>::iterator it = defaultResource.find(typeid(T).hash_code());
		if (it != defaultResource.end())
			return it->second;
		else
		{
			Logger::error("Default resource for " + typeid(T).name() + " isnt set!");
			throw;
		}
	}

	template<class T>
	T* ResourceManager::getDefaultResource()
	{
		ResourceID id = getDefaultResourceID<T>();

		return static_cast<T*>(factories[id].currentResource);
	}

	template<class T>
	ResourceHandle<T> ResourceManager::getResource(const std::string& name)
	{
		return getResource(getResourceID(name));
	}

	template<class T>
	ResourceHandle<T> ResourceManager::getResource(ResourceID id)
	{
		if (id == INVALID_ID)
			return ResourceHandle<T>(getDefaultResource<T>(), this);

		return ResourceHandle<T>(id, this);
	}

	size_t ResourceManager::getResourceID(const std::string& name)
	{
		std::map<std::string, ResourceID>::iterator it = indices.find(name);
		if (it == indices.end())
		{
			Logger::warn("Couldnt find ID of resource: " + name);
			return INVALID_ID;
		}

		return it->second;
	}

	ResourceFactory* ResourceManager::getResourceFactory(const std::string& name)
	{
		return getResourceFactory(getResourceID(name));
	}

	ResourceFactory* ResourceManager::getResourceFactory(ResourceID id)
	{
		if (id == INVALID_ID)
			return nullptr;

		return &factories[id];
	}
}