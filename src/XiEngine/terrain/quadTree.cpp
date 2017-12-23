#include "quadTree.h"

#include "../terrain/quadTreeNode.h"

QuadTree::QuadTree()
{
	rootNode_ = new QuadTreeNode(nullptr, NORTH_WEST, Vector2(0.0f, 0.0f), 10.0f);
}

QuadTree::~QuadTree()
{
	delete rootNode_;
}

void QuadTree::update(const FrameInfo& frame)
{
	rootNode_->update(frame);
}

void QuadTree::drawDebuGeometry(DebugRenderer* debug)
{
	rootNode_->drawDebugGeometry(debug);
}

std::type_index QuadTree::getType()
{
	return typeid(this);
}

void QuadTree::onWorldBoundingBoxUpdate()
{
	worldBoundingBox_ = BoundingBox(-2.0f, 2.0f);
}
