#pragma once

#include "../precompiled.h"

#include "../scene/sceneNode.h"

class Camera;

class Scene
{
public:
	Scene();
	~Scene();

	inline Camera* getMainCamera() { return mainCamera_; }
	inline SceneNode* getRootNode() { return rootNode_; }

	void update();
private:
	Camera* mainCamera_;

	SceneNode* rootNode_;

	void destroy();
};