#pragma once

#include "../graphics/drawable.h"

const int QUAD_TREE_PATCH_EDGE_SIZE = 16;
const int QUAD_TREE_MAX_DEPTH = 5;
const int QUAD_TREE_MAX_DEPTH_DIFF = 4;
const float QUAD_TREE_SPLIT_DISTANCE_SCALE = 2.0f;

class IndexBuffer;
class QuadTreeNode;
class QuadTreePatchTopology;

class QuadTree : public Drawable
{
public:
	QuadTree();
	~QuadTree();

	virtual void update() override;

	virtual void getBatches(Camera* cullCamera, std::vector<Batch>& batches);

	virtual void drawDebugGeometry(DebugRenderer* debug) override;

	inline QuadTreePatchTopology* getPatchTopology(unsigned int detailNorth, unsigned int detailWest, unsigned int detailSouth, unsigned int detailEast) 
	{ return topologies_[detailNorth][detailWest][detailSouth][detailEast]; }

protected:
	virtual void onWorldBoundingBoxUpdate() override;

private:
	QuadTreeNode* rootNode_;

	QuadTreePatchTopology* topologies_[QUAD_TREE_MAX_DEPTH_DIFF + 1][QUAD_TREE_MAX_DEPTH_DIFF + 1][QUAD_TREE_MAX_DEPTH_DIFF + 1][QUAD_TREE_MAX_DEPTH_DIFF + 1];
};