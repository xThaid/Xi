#pragma once

#include "../math/ximath.h"
#include "../scene/component.h"

class Camera;
class Geometry;
class IndexBuffer;

struct Batch
{
	Geometry* geometry_;
	Matrix3x4 transform_;
};

class Drawable : public Component
{
public:
	Drawable();
	virtual ~Drawable();

	virtual void update() = 0;

	virtual void getBatches(Camera* cullCamera, std::vector<Batch>& batches) = 0;

	virtual void drawDebugGeometry(DebugRenderer* debug) override;

	virtual StringHash getType() override { return "Drawable"; }

	BoundingBox getWorldBoundingBox();

protected:
	bool worldBoundingBoxDirty_;
	BoundingBox worldBoundingBox_;

	virtual void onNodeSet() override;
	virtual void onMarkedDirty() override;

	virtual void onWorldBoundingBoxUpdate() = 0;
};