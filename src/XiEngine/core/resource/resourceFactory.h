#pragma once

#include <string>
#include <typeinfo>

namespace xiengine
{
	typedef size_t ResourceType;

	class Resource;

	class ResourceFactory
	{
		friend class ResourceManager;
		
		template<class T>
		friend class ResourceHandle;

	public:
		ResourceFactory();
		~ResourceFactory();

		bool isLoaded();

	protected:
		std::string name;

		Resource* currentResource;

		virtual Resource* load() = 0;
		virtual void unload() = 0;
		virtual size_t getSize() = 0;

		virtual ResourceType getTypeOfResource() = 0;

	private:
		bool loaded;
		bool forceLoaded;

		unsigned int refCount;

		void _load();
		void _unload();

		void reference();
		void dereference();

		void forceLoad();
	};
}