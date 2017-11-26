#include "entity.h"

#include "../rendering/model.h"

#include "../utils/logger.h"

Entity::Entity()
{
	parent = nullptr;
	model = nullptr;
}

Entity::~Entity()
{
	for (Entity* entity : children)
		delete entity;

	if (model != nullptr)
		delete model;
}

void Entity::addChild(Entity* entity)
{
	entity->parent = this;
	children.push_back(entity);

	transform.addChild(&entity->transform);
}

void Entity::setModel(Model* model)
{
	if (this->model != nullptr)
		delete this->model;

	this->model = model;
}
