#include "scene.h"

#include "../graphics/camera.h"

Scene::Scene()
{
	viewCamera_ = std::shared_ptr<Camera>(new Camera());
	cullCamera_ = viewCamera_;

	rootNode_ = new SceneNode(this, "root");
}

Scene::~Scene()
{
	destroy();
}

void Scene::setViewCamera(Camera* camera)
{
	viewCamera_ = std::shared_ptr<Camera>(camera);
}

void Scene::setViewCamera(const std::shared_ptr<Camera>& camera)
{
	viewCamera_ = camera;
}

void Scene::setCullCamera(Camera* camera)
{
	cullCamera_ = std::shared_ptr<Camera>(camera);
}

void Scene::setCullCamera(const std::shared_ptr<Camera>& camera)
{
	cullCamera_ = camera;
}

void Scene::update()
{
	rootNode_->update();
}

void Scene::destroy()
{
	delete rootNode_;
}
