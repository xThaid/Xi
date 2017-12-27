#include "quadTreeNode.h"

#include "../graphics/camera.h"
#include "../graphics/debugRenderer.h"
#include "../graphics/drawable.h"
#include "../terrain/quadTree.h"
#include "../terrain/quadTreePatch.h"
#include "../utils/logger.h"

QuadTreeNode::QuadTreeNode(QuadTree* owner, QuadTreeNode* parent, Quadrant quadrant, Vector2 center, float size) :
	owner_(owner),
	parent_(parent),
	quadrant_(quadrant),
	depth_(parent ? parent_->depth_ + 1: 0),
	center_(center),
	size_(size),
	patch_(new QuadTreePatch(this, QUAD_TREE_PATCH_EDGE_SIZE))
{
	for (int i = 0; i < 4; i++)
		children_[i] = nullptr;

	patch_->prepareGeometry();

	boundingBox_.define(getWorldCenter() - Vector3(size_, 0.0f, size_) / 2.0f, getWorldCenter() + Vector3(size_, 0.0f, size_) / 2.0f);
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

void QuadTreeNode::update(const Vector3& viewPos)
{
	Vector3 nodeCenter = getWorldCenter();
	float distanceToCamera = (nodeCenter - viewPos).length();

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
			children_[i]->update(viewPos);
	}
}

void QuadTreeNode::getBatches(Camera* cullCamera, std::vector<Batch>& batches)
{
	if (cullCamera->getFrustum().intersect(boundingBox_) == OUTSIDE)
		return;

	if (isLeaf())
	{
		Batch batch;
		batch.geometry_ = patch_->getGeometry();

		Matrix4 patchTransform = Matrix4::translationMatrix(getWorldCenter());
		patchTransform.scale(size_ / 2.0f);

		batch.transform_ = patchTransform;

		batches.push_back(batch);
	}
	else
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			children_[i]->getBatches(cullCamera, batches);
		}
	}
}

void QuadTreeNode::drawDebugGeometry(DebugRenderer* debug)
{
	if (isLeaf())
		debug->addBoundingBox(boundingBox_, Color::GREEN);
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

	children_[NORTH_EAST] = new QuadTreeNode(owner_, this, NORTH_EAST, Vector2(center_.x_ + size_ / 4.0f, center_.y_ + size_ / 4.0f), size_ / 2.0f);
	children_[NORTH_WEST] = new QuadTreeNode(owner_, this, NORTH_WEST, Vector2(center_.x_ - size_ / 4.0f, center_.y_ + size_ / 4.0f), size_ / 2.0f);
	children_[SOUTH_WEST] = new QuadTreeNode(owner_, this, SOUTH_WEST, Vector2(center_.x_ - size_ / 4.0f, center_.y_ - size_ / 4.0f), size_ / 2.0f);
	children_[SOUTH_EAST] = new QuadTreeNode(owner_, this, SOUTH_EAST, Vector2(center_.x_ + size_ / 4.0f, center_.y_ - size_ / 4.0f), size_ / 2.0f);
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
