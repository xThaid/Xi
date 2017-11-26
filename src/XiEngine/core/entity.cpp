#include "entity.h"

#include "../rendering/model.h"

#include "../utils/logger.h"

Entity::Entity()
{
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
	children.push_back(entity);
}

void Entity::setModel(Model* model)
{
	if (this->model != nullptr)
		delete this->model;

	this->model = model;
}
