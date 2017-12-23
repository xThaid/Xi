#pragma once

#include "../scene/sceneNode.h"

class QuadTree;

class Program
{
public:
	void init();
	void update();

private:
	bool mouseLocked = true;

	
	QuadTree* terrain;
};
