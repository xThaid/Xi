#pragma once

#include <vector>

#include "component\componentBase.h"

namespace xiengine
{
	class Entity
	{
	public:

	private:
		std::vector<Entity*> childrens;
		std::vector<ComponentBase> components;
	};
}