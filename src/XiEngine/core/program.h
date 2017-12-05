#pragma once

#include "../scene/sceneNode.h"

class Program
{
public:
	void init();
	void update();

private:
	bool mouseLocked = true;

	SceneNode* axis;

	SceneNode* myEntity;
	SceneNode* myEntity2;
	SceneNode* myEntity3;
};
