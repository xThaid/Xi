#include "entity.h"

namespace xiengine
{
	void Entity::setParent(Entity* entity)
	{
		parent = entity;
	}

	void Entity::addChildren(Entity entity)
	{
		//SPRAWDZIC CZY MOZNA
		childrens.push_back(entity);
	}

	void Entity::addComponent(ComponentBase& component)
	{
		//SPRAWDZIC CZY JUZ NIE MA CZASEM
		components.push_back(component);
	}

	ComponentBase* Entity::getComponent(std::string& componentName)
	{
		return nullptr;
	}
}