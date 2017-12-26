#pragma once

#include "../precompiled.h"

#include "../math/ximath.h"

class DebugRenderer;
class SceneNode;

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void update() = 0;

	virtual void drawDebugGeometry(DebugRenderer* debug) = 0;
	
	virtual StringHash getType() = 0;

protected:
	SceneNode* node_;

	virtual void onNodeSet() = 0;
	virtual void onMarkedDirty() = 0;

	friend class SceneNode;
};