#include "resourceHandle.h"

#include "resourceManager.h"

#include "../../utils/logger.h"

namespace xiengine
{
	template <class T>
	ResourceHandle<T>::ResourceHandle(ResourceFactory* resFactory, ResourceManager* managerInstance) :
		resFactory(resFactory),
		managerInstance(managerInstance)
	{
		resFactory->reference();
	}

	template <class T>
	ResourceHandle<T>::~ResourceHandle()
	{
		resFactory->dereference();
	}

	template <class T>
	T& ResourceHandle<T>::operator*() const 
	{		
		if (resFactory->currentResource == nullptr)
		{
			Logger::info(resFactory->name + " resource is nullptr. Using default resouce");

			return managerInstance->getDefaultResource<T>();
		}

		return static_cast<T>(resFactory->currentResource);
	}
}