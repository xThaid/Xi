#pragma once

#include <vector>

#include "entity.h"

class Camera;

class Scene
{
public:
	Scene();
	~Scene();

	void addEntity(Entity* entity);

	inline Camera* getMainCamera() { return mainCamera; }
	inline std::vector<Entity*>& getEntites() { return entities; }

	void update();
private:
	Camera* mainCamera;

	std::vector<Entity*> entities;

	void destroy();
};