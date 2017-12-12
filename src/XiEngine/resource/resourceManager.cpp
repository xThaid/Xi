#include "resourceManager.h"

#include "../core/core.h"
#include "../utils/logger.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	releaseAll();
}

bool ResourceManager::addResource(Resource* resource)
{
	if (!resource)
		return false;

	if (resource->getName().empty())
	{
		Logger::error("Trying to add resource with empty name");
		return false;
	}

	if (findResource(resource->getType(), resource->getNameHash()) != nullptr)
	{
		Logger::warn("There already exists resource with name " + resource->getName());
		return false;
	}

	setupResource(resource);

	resourceGroups_[resource->getType()].resources_[resource->getNameHash()] = resource;
	updateResourceGroup(resource->getType());
	return true;
}

void ResourceManager::releaseResource(StringHash type, const std::string& name)
{
	StringHash nameHash(name);
	Resource* resource = findResource(type, nameHash);
	if (!resource)
		return;

	resourceGroups_[type].resources_.erase(nameHash);
	deleteResource(resource);
	
	updateResourceGroup(type);
}

void ResourceManager::releaseGroup(StringHash type)
{
	std::map<StringHash, ResourceGroup>::iterator group = resourceGroups_.find(type);
	if (group == resourceGroups_.end())
		return;

	for (std::map<StringHash, Resource*>::iterator i = group->second.resources_.begin(); i != group->second.resources_.end(); ++i)
	{
		deleteResource(i->second);
	}

	group->second.resources_.clear();
	updateResourceGroup(type);
}

void ResourceManager::releaseAll()
{
	for (std::map<StringHash, ResourceGroup>::iterator it = resourceGroups_.begin(); it != resourceGroups_.end(); it++)
		releaseGroup(it->first);

	resourceGroups_.clear();
}

Resource* ResourceManager::getResource(StringHash type, const std::string& name)
{
	if(name.empty())
		return nullptr;

	StringHash nameHash(name);
	Resource* resource = findResource(type, nameHash);
	if (!resource)
		return nullptr;

	return resource;
}

std::map<StringHash, Resource*>* ResourceManager::getResources(StringHash type)
{
	return &resourceGroups_[type].resources_;
}

bool ResourceManager::existsResource(StringHash type, const std::string& name)
{
	return findResource(type, name) != nullptr;
}

Resource* ResourceManager::findResource(StringHash type, StringHash nameHash)
{
	std::map<StringHash, ResourceGroup>::iterator group = resourceGroups_.find(type);
	if (group == resourceGroups_.end())
		return nullptr;

	std::map<StringHash, Resource*>::iterator resource = group->second.resources_.find(nameHash);
	if (resource == group->second.resources_.end())
		return nullptr;

	return resource->second;
}

bool ResourceManager::existsResourceGroup(StringHash type)
{
	std::map<StringHash, ResourceGroup>::iterator group = resourceGroups_.find(type);
	return group != resourceGroups_.end();
}

void ResourceManager::updateResourceGroup(StringHash type)
{
	std::map<StringHash, ResourceGroup>::iterator group = resourceGroups_.find(type);
	if (group == resourceGroups_.end())
		return;
	
	unsigned int totalMemoryUse = 0;

	for (std::map<StringHash, Resource*>::iterator i = group->second.resources_.begin(); i != group->second.resources_.end(); ++i)
	{
		totalMemoryUse += i->second->getMemoryUse();
	}

	group->second.memoryUse_ = totalMemoryUse;
}

void ResourceManager::setupResource(Resource* resource)
{
	bool result = resource->load();

	if (!result)
		Logger::warn("Couldn't load resource: " + resource->getName());

	//Logger::trace("[Resource Manager] Loading resource: " + resource->getName() + " of type " + resource->getTypeName());
}

void ResourceManager::deleteResource(Resource* resource)
{
	//Logger::trace("[Resource Manager] Deleting resource: " + resource->getName() + " of type " + resource->getTypeName());

	resource->unload();
	delete resource;
}