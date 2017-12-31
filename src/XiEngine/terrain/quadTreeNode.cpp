#include "quadTreeNode.h"

#include "../lib/SimplexNoise.h"

#include "../graphics/camera.h"
#include "../graphics/debugRenderer.h"
#include "../graphics/drawable.h"
#include "../terrain/quadTree.h"
#include "../terrain/quadTreePatch.h"
#include "../utils/logger.h"

QuadTreeNode::QuadTreeNode(QuadTree* owner, QuadTreeNode* parent, Quadrant quadrant, Vector2 center, float size) :
	owner_(owner),
	parent_(parent),
	children_(),
	neighbors_(),
	neighborsDepthDiff_(),
	quadrant_(quadrant),
	depth_(parent ? parent_->depth_ + 1: 0),
	center_(center),
	size_(size)
{
	patch_ = new QuadTreePatch(this, QUAD_TREE_PATCH_EDGE_SIZE);
	patch_->prepareVertices();
	patch_->prepareGeometry();
}

QuadTreeNode::~QuadTreeNode()
{
	if (!isLeaf())
	{
		for (unsigned int q = 0; q < 4; q++)
			delete children_[q];
	}

	for (unsigned int s = 0; s < 4; s++)
	{
		if (neighbors_[s])
		{
			if (parent_ == neighbors_[s]->parent_)
				neighbors_[s]->parent_ = nullptr;
			else if (depth_ == neighbors_[s]->depth_)
			{
				neighbors_[s]->neighbors_[mirrorSide(s)] = parent_;
				neighbors_[s]->neighborsDepthDiff_[mirrorSide(s)]++;
				neighbors_[s]->propagateDownNeighbor(mirrorSide(s));
			}
		}
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
		for (int q = 0; q < 4; q++)
			children_[q]->update(viewPos);
	}
}

void QuadTreeNode::getBatches(Camera* cullCamera, std::vector<Batch>& batches)
{
	if (cullCamera->getFrustum().intersect(patch_->getBoundingBox().transformed(getTransform())) == OUTSIDE)
		return;

	if (isLeaf())
	{
		Batch batch;
		batch.geometry_ = patch_->getGeometry();
		batch.transform_ = getTransform();
		batch.customIndexBuffer_ = owner_->getPatchTopology(
			neighborsDepthDiff_[0], neighborsDepthDiff_[1], neighborsDepthDiff_[2], neighborsDepthDiff_[3]
		)->getIndexBuffer();

		batches.push_back(batch);
	}
	else
	{
		for (unsigned int q = 0; q < 4; q++)
		{
			children_[q]->getBatches(cullCamera, batches);
		}
	}
}

void QuadTreeNode::drawDebugGeometry(DebugRenderer* debug)
{
	if (isLeaf())
	{
		if (false)
		{
			debug->addBoundingBox(patch_->getBoundingBox().transformed(getTransform()), Color::GREEN);
		}
		else
		{
			debug->addQuad(getWorldCenter(), size_, size_, Color::GREEN);
		}
	}
	else
	{
		for (int q = 0; q < 4; q++)
			children_[q]->drawDebugGeometry(debug);
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

Vector3 QuadTreeNode::localToWorldPos(const Vector2& localPos)
{
	Vector3 result(localPos.x_, 0.0f, localPos.y_);
	result *= size_ / 2.0f;
	result += getWorldCenter();
	
	return result;
}

float QuadTreeNode::getHeightFromLocalPos(const Vector2& localPos)
{
	Vector3 worldPos = localToWorldPos(localPos);

	SimplexNoise simplex = SimplexNoise(0.01f, 2.0f);
	float height = simplex.fractal(8, worldPos.x_, worldPos.z_);

	return 5.0f * height;
}

void QuadTreeNode::setNeighborDual(Side side, QuadTreeNode* neighbor)
{
	neighbors_[side] = neighbor;
	neighborsDepthDiff_[side] = 0;

	neighbor->neighbors_[mirrorSide(side)] = this;
	neighbor->neighborsDepthDiff_[mirrorSide(side)] = 0;
}

void QuadTreeNode::propagateDownNeighbor(Side side)
{
	if (isLeaf())
		return;

	for (unsigned int q = 0; q < 4; q++)
	{
		if (isOnSide(q, side))
		{
			children_[q]->neighbors_[side] = neighbors_[side];
			children_[q]->neighborsDepthDiff_[side] = neighborsDepthDiff_[side] + 1;
			children_[q]->propagateDownNeighbor(side);
		}
	}
}

void QuadTreeNode::split()
{
	if (!isLeaf() || depth_ >= QUAD_TREE_MAX_DEPTH)
		return;

	children_[NORTH_EAST] = new QuadTreeNode(owner_, this, NORTH_EAST, Vector2(center_.x_ + size_ / 4.0f, center_.y_ + size_ / 4.0f), size_ / 2.0f);
	children_[NORTH_WEST] = new QuadTreeNode(owner_, this, NORTH_WEST, Vector2(center_.x_ - size_ / 4.0f, center_.y_ + size_ / 4.0f), size_ / 2.0f);
	children_[SOUTH_WEST] = new QuadTreeNode(owner_, this, SOUTH_WEST, Vector2(center_.x_ - size_ / 4.0f, center_.y_ - size_ / 4.0f), size_ / 2.0f);
	children_[SOUTH_EAST] = new QuadTreeNode(owner_, this, SOUTH_EAST, Vector2(center_.x_ + size_ / 4.0f, center_.y_ - size_ / 4.0f), size_ / 2.0f);

	children_[NORTH_EAST]->setNeighborDual(WEST, children_[NORTH_WEST]);
	children_[NORTH_WEST]->setNeighborDual(SOUTH, children_[SOUTH_WEST]);
	children_[SOUTH_WEST]->setNeighborDual(EAST, children_[SOUTH_EAST]);
	children_[SOUTH_EAST]->setNeighborDual(NORTH, children_[NORTH_EAST]);

	for (unsigned int s = 0; s < 4; s++)
	{
		if (neighbors_[s])
		{
			if (neighbors_[s]->isLeaf())
			{
				propagateDownNeighbor((Side) s);
			}
			else
			{
				for (unsigned int q = 0; q < 4; q++)
				{
					if (isOnSide(q, s))
					{
						QuadTreeNode* neighbor = neighbors_[s]->children_[reflectQuadrant(q, s)];
						children_[q]->setNeighborDual((Side) s, neighbor);
						neighbor->propagateDownNeighbor(mirrorSide(s));
					}
				}
			}
		}
	}
}

void QuadTreeNode::merge()
{
	if (isLeaf())
		return;

	for (int q = 0; q < 4; q++)
	{
		delete children_[q];
		children_[q] = nullptr;
	}
}

Matrix4 QuadTreeNode::getTransform() const
{
	Matrix4 patchTransform = Matrix4::translationMatrix(getWorldCenter());
	patchTransform.scale(size_ / 2.0f, 1.0f, size_ / 2.0f);
	return patchTransform;
}