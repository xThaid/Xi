#include "drawable.h"

#include "../graphics/debugRenderer.h"

Drawable::Drawable() :
	worldBoundingBoxDirty_(true)
{
}

Drawable::~Drawable()
{
}

void Drawable::drawDebuGeometry(DebugRenderer* debug)
{
	debug->addBoundingBox(getWorldBoundingBox(), Color::GREEN);
}

BoundingBox Drawable::getWorldBoundingBox()
{
	if (worldBoundingBoxDirty_)
		onWorldBoundingBoxUpdate();

	return worldBoundingBox_;
}

void Drawable::onNodeSet()
{
}

void Drawable::onMarkedDirty()
{
	worldBoundingBoxDirty_ = true;
}