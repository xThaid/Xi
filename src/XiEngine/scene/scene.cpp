#include "scene.h"

#include "../graphics/camera.h"

Scene::Scene()
{
	mainCamera_ = new Camera();
	rootNode_ = new SceneNode(this, "root");
}

Scene::~Scene()
{
	destroy();
}

void Scene::update()
{
	rootNode_->update();
}

void Scene::destroy()
{
	delete mainCamera_;
	delete rootNode_;
}
