#pragma once

#include "transform.h"

#include <vector>

class Model;

class Entity
{
public:
	Entity();
	~Entity();

	void addChild(Entity* entity);
	std::vector<Entity*>& getChildren() { return children; }

	inline bool hasParent() { return parent != nullptr; }
	Entity* getParent() { return parent; }

	void setModel(Model* model);
	inline Model* getModel() { return model; }

	Transform* getTransform() { return &transform; }

private:
	Entity* parent;
	std::vector<Entity*> children;

	Transform transform;

	Model* model;
};