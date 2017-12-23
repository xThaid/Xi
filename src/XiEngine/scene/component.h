#pragma once

#include "../precompiled.h"

class DebugRenderer;
class SceneNode;

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void drawDebuGeometry(DebugRenderer* debug) = 0;
	
	virtual std::type_index getType() = 0;

protected:
	SceneNode* node_;

	virtual void onNodeSet() = 0;
	virtual void onMarkedDirty() = 0;

	friend class SceneNode;
};