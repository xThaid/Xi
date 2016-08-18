#pragma once

#include <vector>
#include <functional>

namespace xiengine
{
	class Event
	{
	public:
		void addEventHandler(std::function<void(void)> func);

		void handleEvents();
	private:
		std::vector<std::function<void(void)> > handlers;
	};
}