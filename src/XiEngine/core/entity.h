#pragma once

#include <vector>

class Model;

class Entity
{
public:
	Entity();
	~Entity();

	void addChild(Entity* entity);
	std::vector<Entity*>& getChildren() { return children; }

	void setModel(Model* model);
	inline Model* getModel() { return model; }

private:
	std::vector<Entity*> children;

	Model* model;
};