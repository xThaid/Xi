#include "scene.h"

#include "../camera.h"

Scene::Scene()
{
	mainCamera = new Camera();
}

Scene::~Scene()
{
	destroy();
}

void Scene::update()
{

}

void Scene::destroy()
{
	delete mainCamera;
}
