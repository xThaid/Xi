#pragma once

#include <vector>

#include "component\components.h"

namespace xiengine
{
	class Entity
	{
		friend class RenderingEngine;

	public:
		
		void setParent(Entity* entity);

		void addChildren(Entity entity);
		void addComponent(ComponentBase& component);

		ComponentBase* getComponent(std::string& componentName);

		bool hasComponent();

	private:
		Entity* parent;

		std::vector<Entity> childrens;
		std::vector<ComponentBase> components;

		Transform transform;
	};
}