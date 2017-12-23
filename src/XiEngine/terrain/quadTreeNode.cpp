#include "quadTreeNode.h"

#include "../graphics/camera.h"
#include "../graphics/debugRenderer.h"
#include "../graphics/drawable.h"
#include "../terrain/quadTree.h"
#include "../terrain/quadTreePatch.h"
#include "../utils/logger.h"

QuadTreeNode::QuadTreeNode(QuadTreeNode* parent, Quadrant quadrant, Vector2 center, float size) :
	parent_(parent),
	quadrant_(quadrant),
	depth_(parent ? parent_->depth_ + 1: 0),
	center_(center),
	size_(size)
{
	for (int i = 0; i < 4; i++)
		children_[i] = nullptr;
}

QuadTreeNode::~QuadTreeNode()
{
	if (!isLeaf())
	{
		for (int i = 0; i < 4; i++)
			delete children_[i];
	}

	if (patch_ != nullptr)
		delete patch_;
}

void QuadTreeNode::update(const FrameInfo& frame)
{
	Vector3 nodeCenter = Vector3(center_.x_, 0.0f, -center_.y_);
	float distanceToCamera = (nodeCenter - frame.camera_->position).length();

	bool shouldSplit = distanceToCamera < size_ * QUAD_TREE_SPLIT_DISTANCE_SCALE;

	if (!shouldSplit)
	{
		if(!isLeaf())
			merge();
	
		return;
	}
	
	if (isLeaf())
		split();

	if (!isLeaf())
	{
		for (int i = 0; i < 4; i++)
			children_[i]->update(frame);
	}
}

void QuadTreeNode::drawDebugGeometry(DebugRenderer* debug)
{
	if (isLeaf())
		debug->addQuad(Vector3(center_.x_, 0.0f, -center_.y_), size_, size_, Color::ORANGE);
	else
	{
		for (int i = 0; i < 4; i++)
			children_[i]->drawDebugGeometry(debug);
	}
}

bool QuadTreeNode::isLeaf() const
{
	return !children_[0];
}

float QuadTreeNode::getScale() const
{
	return 1.0f / (1 << depth_);
}

void QuadTreeNode::split()
{
	if (!isLeaf() || depth_ >= QUAD_TREE_MAX_DEPTH)
		return;

	children_[NORTH_EAST] = new QuadTreeNode(this, NORTH_EAST, Vector2(center_.x_ + size_ / 4.0f, center_.y_ + size_ / 4.0f), size_ / 2.0f);
	children_[NORTH_WEST] = new QuadTreeNode(this, NORTH_WEST, Vector2(center_.x_ - size_ / 4.0f, center_.y_ + size_ / 4.0f), size_ / 2.0f);
	children_[SOUTH_WEST] = new QuadTreeNode(this, SOUTH_WEST, Vector2(center_.x_ - size_ / 4.0f, center_.y_ - size_ / 4.0f), size_ / 2.0f);
	children_[SOUTH_EAST] = new QuadTreeNode(this, SOUTH_EAST, Vector2(center_.x_ + size_ / 4.0f, center_.y_ - size_ / 4.0f), size_ / 2.0f);
}

void QuadTreeNode::merge()
{
	if (isLeaf())
		return;

	for (int i = 0; i < 4; i++)
	{
		delete children_[i];
		children_[i] = nullptr;
	}
}
