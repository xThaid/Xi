#include "scene.h"

#include "../graphics/camera.h"

Scene::Scene()
{
	mainCamera_ = new Camera();
	rootNode_ = new SceneNode("root");
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
	delete mainCamera_;
	delete rootNode_;
}
