#include "scene.h"

#include "camera.h"

Scene::Scene()
{
	mainCamera = new Camera();
}

Scene::~Scene()
{
	destroy();
}

void Scene::addEntity(Entity* entity)
{
	entities.push_back(entity);
}

void Scene::update()
{

}

void Scene::destroy()
{
	delete mainCamera;
	for (Entity* entity : entities)
		delete entity;
}
