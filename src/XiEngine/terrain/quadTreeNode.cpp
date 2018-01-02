#include "quadTreeNode.h"

#include "../graphics/camera.h"
#include "../graphics/debugRenderer.h"
#include "../graphics/drawable.h"
#include "../terrain/quadTreeFace.h"
#include "../terrain/quadTreePatch.h"
#include "../terrain/terrain.h"
#include "../terrain/terrainGenerator.h"
#include "../utils/logger.h"

QuadTreeNode::QuadTreeNode(QuadTreeFace* face, QuadTreeNode* parent, Quadrant quadrant, Vector2 center, float size) :
	face_(face),
	parent_(parent),
	children_(),
	neighbors_(),
	neighborsDepthDiff_(),
	quadrant_(quadrant),
	depth_(parent ? parent_->depth_ + 1: 0),
	center_(center),
	size_(size)
{
	patch_ = new QuadTreePatch(face_->getTerrain()->getNextPatchID(), this, QUAD_TREE_PATCH_EDGE_SIZE);

	nodeTransform_ = Matrix4();

	face_->getTerrain()->getTerrainGenerator()->pushQueue(patch_);
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

	if(face_->getTerrain()->getTerrainGenerator() != nullptr)
		face_->getTerrain()->getTerrainGenerator()->dismiss(patch_->getID());

	delete patch_;
}

void QuadTreeNode::update(const Vector3& viewPos)
{
	if (patch_->getStatus() == RAM_LOADED)
		patch_->prepareGeometry();

	Vector3 nodeCenter = patch_->getBoundingBox().center();
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
	if (cullCamera->getFrustum().intersect(patch_->getBoundingBox().transformed(nodeTransform_)) == OUTSIDE)
		return;

	if (areChildrenReadyToRender())
	{
		for (unsigned int q = 0; q < 4; q++)
			children_[q]->getBatches(cullCamera, batches);
	}
	else
	{
		if (patch_->getStatus() == READY_TO_USE)
		{
			Batch batch;
			batch.geometry_ = patch_->getGeometry();
			batch.transform_ = nodeTransform_;
			batch.customIndexBuffer_ = QuadTreePatch::getTopology(
				neighborsDepthDiff_[0], neighborsDepthDiff_[1], neighborsDepthDiff_[2], neighborsDepthDiff_[3]
			)->getIndexBuffer();

			batches.push_back(batch);
		}
	}
}

void QuadTreeNode::drawDebugGeometry(DebugRenderer* debug)
{
	if (areChildrenReadyToRender())
	{
		for (int q = 0; q < 4; q++)
			children_[q]->drawDebugGeometry(debug);
	}
	else
	{
		if(patch_->getStatus() >= RAM_LOADED)
			debug->addBoundingBox(patch_->getBoundingBox().transformed(nodeTransform_), Color::GREEN);
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

Vector2 QuadTreeNode::localToFacePos(const Vector2& localPos)
{
	Vector2 result = localPos * (size_ / 2.0f);
	result += Vector2(center_.x_, -center_.y_);

	return result;
}

void QuadTreeNode::setNeighbor(Side side, QuadTreeNode* neighbor)
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

	children_[NORTH_EAST] = new QuadTreeNode(face_, this, NORTH_EAST, Vector2(center_.x_ + size_ / 4.0f, center_.y_ + size_ / 4.0f), size_ / 2.0f);
	children_[NORTH_WEST] = new QuadTreeNode(face_, this, NORTH_WEST, Vector2(center_.x_ - size_ / 4.0f, center_.y_ + size_ / 4.0f), size_ / 2.0f);
	children_[SOUTH_WEST] = new QuadTreeNode(face_, this, SOUTH_WEST, Vector2(center_.x_ - size_ / 4.0f, center_.y_ - size_ / 4.0f), size_ / 2.0f);
	children_[SOUTH_EAST] = new QuadTreeNode(face_, this, SOUTH_EAST, Vector2(center_.x_ + size_ / 4.0f, center_.y_ - size_ / 4.0f), size_ / 2.0f);

	children_[NORTH_EAST]->setNeighbor(WEST, children_[NORTH_WEST]);
	children_[NORTH_WEST]->setNeighbor(SOUTH, children_[SOUTH_WEST]);
	children_[SOUTH_WEST]->setNeighbor(EAST, children_[SOUTH_EAST]);
	children_[SOUTH_EAST]->setNeighbor(NORTH, children_[NORTH_EAST]);

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
						children_[q]->setNeighbor((Side) s, neighbor);
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

	bool canClear = true;
	for (unsigned int q = 0; q < 4; q++)
	{
		if (children_[q]->getPatch()->getStatus() == LOADING)
			canClear = false;
	}

	if (!canClear)
		return;

	for (int q = 0; q < 4; q++)
	{
		delete children_[q];
		children_[q] = nullptr;
	}
}

bool QuadTreeNode::areChildrenReadyToRender()
{
	bool childrenReady = true;
	if (isLeaf())
	{
		childrenReady = false;
	}
	else
	{
		for (unsigned int q = 0; q < 4; q++)
		{
			if (children_[q]->getPatch()->getStatus() != READY_TO_USE)
				childrenReady = false;
		}
	}
	
	return childrenReady;
}
