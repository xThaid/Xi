#pragma once

namespace xiengine
{
	class ResourceManager;
	class ResourceFactory;

	template<class T>
	class ResourceHandle
	{
		friend class ResourceManager;

	public:
		~ResourceHandle();

		T& operator*() const;
	private:
		ResourceFactory* resFactory;
		ResourceManager* managerInstance;

		ResourceHandle(ResourceFactory* resFactory, ResourceManager* managerInstance);
	};
}