#pragma once

#include "../graphics/drawable.h"

const int QUAD_TREE_PATCH_EDGE_SIZE = 16;
const int QUAD_TREE_MAX_DEPTH = 4;
const int QUAD_TREE_MAX_DEPTH_DIFF = 4;
const float QUAD_TREE_SPLIT_DISTANCE_SCALE = 200.0f;

class Camera;
class QuadTreeFace;
class QuadTreeNode;
class TerrainGenerator;

class Terrain : public Drawable
{
public:
	Terrain();
	virtual ~Terrain();

	virtual void update() override;

	virtual void getBatches(Camera* cullCamera, std::vector<Batch>& batches) override;

	virtual void drawDebugGeometry(DebugRenderer* debug) override;

	virtual float getTerrainHeight(const Vector3& point) const = 0;
	virtual Vector3 projectOnSurface(const Vector3& point) const = 0;

	Camera* getCullCamera();

	unsigned int getNextPatchID();

	inline TerrainGenerator* getTerrainGenerator() { return generator_; }

protected:
	TerrainGenerator* generator_;

	std::vector<QuadTreeFace*> faces_;

	unsigned int nextPatchID_;

	virtual void onWorldBoundingBoxUpdate() override;

private:
	
};