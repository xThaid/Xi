#include "event.h"

namespace xiengine
{
	void Event::addEventHandler(std::function<void(void)> func)
	{
		handlers.push_back(func);
	}

	void Event::handleEvents()
	{
		for (auto & handler : handlers)
			handler();
	}

}