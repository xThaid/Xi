#pragma once

#include "../precompiled.h"

#include "../resource/resource.h"
#include "../utils/stringHash.h"

struct ResourceGroup
{
	ResourceGroup() :
		memoryUse_(0)
	{
	}

	unsigned int memoryUse_;

	std::map<StringHash, Resource*> resources_;
};

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	bool addResource(Resource* resource);
	
	void releaseResource(StringHash type, const std::string& name);
	void releaseGroup(StringHash type);
	void releaseAll();

	Resource* getResource(StringHash type, const std::string& name);
	std::map<StringHash, Resource*>* getResources(StringHash type);

	bool existsResource(StringHash type, const std::string& name);

	template <class T> void releaseResource(const std::string& name);
	template <class T> void releaseGroup();
	
	template <class T> T* getResource(const std::string& name);
	template <class T> std::map<StringHash, Resource*>* getResources();

	template <class T> bool existsResource(const std::string& name);

private:
	std::map<StringHash, ResourceGroup> resourceGroups_;

	Resource* findResource(StringHash type, StringHash nameHash);

	bool existsResourceGroup(StringHash type);
	void updateResourceGroup(StringHash type);

	void setupResource(Resource* resource);
	void deleteResource(Resource* resource);
};

template <class T> void ResourceManager::releaseResource(const std::string& name)
{
	StringHash type = T::getTypeNameStatic();
	releaseResource(type, name);
}

template <class T> void ResourceManager::releaseGroup()
{
	StringHash type = T::getTypeNameStatic();
	releaseGroup(type);
}

template <class T> T* ResourceManager::getResource(const std::string& name)
{
	StringHash type = T::getTypeNameStatic();
	return static_cast<T*>(getResource(type, name));
}

template <class T> std::map<StringHash, Resource*>* ResourceManager::getResources()
{
	StringHash type = T::getTypeNameStatic();
	return getResources(type);
}

template<class T> bool ResourceManager::existsResource(const std::string& name)
{
	StringHash type = T::getTypeNameStatic();
	return existsResource(type, name);
}
