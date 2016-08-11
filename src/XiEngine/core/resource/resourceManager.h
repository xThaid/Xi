#pragma once

#include <map>
#include <vector>
#include <string>

#include "resource.h"
#include "resourceHandle.h"
#include "resourceFactory.h"

namespace xiengine
{
	typedef unsigned int ResourceID;
	typedef size_t ResourceType;

	class ResourceManager
	{
	public:
		const static ResourceID INVALID_ID = UINT_MAX;

		ResourceManager();
		~ResourceManager();

		bool addResource(const std::string& name, ResourceFactory& factory);

		template<class T>
		void setDefaultResource(const std::string& name);
		template<class T>
		void setDefaultResource(ResourceID id);

		template<class T>
		ResourceID getDefaultResourceID();

		template<class T>
		T* getDefaultResource();

		template<class T>
		ResourceHandle getResource(const std::string& name);
		template<class T>
		ResourceHandle getResource(ResourceID id);

		ResourceID getResourceID(const std::string& name);

		ResourceFactory* getResourceFactory(const std::string& name);
		ResourceFactory* getResourceFactory(ResourceID id);

	private:
		std::vector<ResourceFactory> factories;
		std::map<std::string, ResourceID> indices;
		std::map<ResourceType, ResourceID> defaultResources;

		ResourceID lastID;
	};
}