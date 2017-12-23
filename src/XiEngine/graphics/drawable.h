#pragma once

#include "../math/ximath.h"
#include "../scene/component.h"

class Camera;
class Geometry;
class Material;

struct FrameInfo
{
	Camera* camera_;
};

struct SourceBatch
{
	Geometry* geometry_;
	Material* material_;
	Matrix4 worldTransform_;
};

class Drawable : public Component
{
public:
	Drawable();
	virtual ~Drawable();

	virtual void update(const FrameInfo& frame) = 0;

	virtual void drawDebuGeometry(DebugRenderer* debug) override;

	virtual std::type_index getType() = 0;

	BoundingBox getWorldBoundingBox();

protected:
	bool worldBoundingBoxDirty_;
	BoundingBox worldBoundingBox_;

	virtual void onNodeSet() override;
	virtual void onMarkedDirty() override;

	virtual void onWorldBoundingBoxUpdate() = 0;
};