#include "quadTree.h"

#include "../graphics/camera.h"
#include "../graphics/indexBuffer.h"
#include "../scene/scene.h"
#include "../scene/sceneNode.h"
#include "../terrain/quadTreeNode.h"
#include "../terrain/quadTreePatch.h"

QuadTree::QuadTree()
{
	rootNode_ = new QuadTreeNode(this, nullptr, NORTH_EAST, Vector2(0.0f, 0.0f), 100.0f);

	for (unsigned int a = 0; a <= QUAD_TREE_MAX_DEPTH_DIFF; a++)
		for (unsigned int b = 0; b <= QUAD_TREE_MAX_DEPTH_DIFF; b++)
			for (unsigned int c = 0; c <= QUAD_TREE_MAX_DEPTH_DIFF; c++)
				for (unsigned int d = 0; d <= QUAD_TREE_MAX_DEPTH_DIFF; d++)
					topologies_[a][b][c][d] = new QuadTreePatchTopology(QUAD_TREE_PATCH_EDGE_SIZE, a, b, c, d);
}

QuadTree::~QuadTree()
{
	delete rootNode_;

	for (unsigned int a = 0; a <= QUAD_TREE_MAX_DEPTH_DIFF; a++)
		for (unsigned int b = 0; b <= QUAD_TREE_MAX_DEPTH_DIFF; b++)
			for (unsigned int c = 0; c <= QUAD_TREE_MAX_DEPTH_DIFF; c++)
				for (unsigned int d = 0; d <= QUAD_TREE_MAX_DEPTH_DIFF; d++)
					delete topologies_[a][b][c][d];
}

void QuadTree::update()
{
	rootNode_->update(node_->getScene()->getCullCamera()->position);
}

void QuadTree::getBatches(Camera* cullCamera, std::vector<Batch>& batches)
{
	rootNode_->getBatches(cullCamera, batches);
}

void QuadTree::drawDebugGeometry(DebugRenderer* debug)
{
	rootNode_->drawDebugGeometry(debug);
}

void QuadTree::onWorldBoundingBoxUpdate()
{
}