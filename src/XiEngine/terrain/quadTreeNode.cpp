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
	size_(size),
	drawBorders_(false)
{
	patch_ = new QuadTreePatch(face_->getTerrain()->getNextPatchID(), this, QUAD_TREE_PATCH_EDGE_SIZE);

	nodeTransform_ = Matrix3x4();

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
				neighbors_[s]->neighbors_[mirrorSide(s)] = nullptr;
			else if (depth_ == neighbors_[s]->depth_)
			{
				neighbors_[s]->neighbors_[mirrorSide(s)] = parent_;
				neighbors_[s]->neighborsDepthDiff_[mirrorSide(s)]++;
				neighbors_[s]->propagateDownNeighbor(mirrorSide(s));
			}
		}
	}

	if(face_->getTerrain()->getTerrainGenerator() != nullptr)
	{
		face_->getTerrain()->getTerrainGenerator()->dismiss(patch_->getID());
		std::unique_lock<std::mutex> lk(patchMutex_);
		patchCV_.wait(lk, [this] {return patch_->getStatus() != PatchStatus::LOADING; });
	}

	delete patch_;
}

void QuadTreeNode::update(const Vector3& viewPos)
{
	if (patch_->getStatus() == PatchStatus::RAM_LOADED)
		patch_->prepareGeometry();

	drawBorders_ = true;
	borderColor_ = Color::BLACK;

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

void QuadTreeNode::cullNodesToRender(Camera* cullCamera, std::vector<QuadTreeNode*>& nodes)
{
	if (cullCamera->getFrustum().intersect(patch_->getBoundingBox().transformed(nodeTransform_)) == OUTSIDE)
		return;

	Vector2 scr = cullCamera->worldToScreenPoint(patch_->getBoundingBox().center());

	Color col[4] = {
		Color::RED,
		Color::YELLOW,
		Color::WHITE,
		Color::ORANGE
	};
	
	if (false)
	{
		if (quadrant_ == NORTH_EAST)
			borderColor_ = Color::BLUE;
		else
			borderColor_ = Color::RED;
	}
	else
	{
		if (abs(scr.x_ - 0.5f) < 0.1f && abs(scr.y_ - 0.5f) < 0.1f)
		{
			borderColor_ = Color::BLUE;

			for (unsigned int s = 0; s < 4; s++)
			{
				if (neighbors_[s])
				{
					neighbors_[s]->borderColor_ = col[s];
				}
			}
		}
	}

	if (areChildrenReadyToRender())
	{
		for (unsigned int q = 0; q < 4; q++)
			children_[q]->cullNodesToRender(cullCamera, nodes);
	}
	else
	{
		if (patch_->getStatus() == PatchStatus::READY_TO_USE)
		{
			nodes.push_back(this);
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
		if(patch_->getStatus() >= PatchStatus::RAM_LOADED)
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

QuadTreePatchTopology* QuadTreeNode::getPatchTopology()
{
	return QuadTreePatch::getTopology(neighborsDepthDiff_[0], neighborsDepthDiff_[1], neighborsDepthDiff_[2], neighborsDepthDiff_[3]);
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
		if (children_[q]->getPatch()->getStatus() == PatchStatus::LOADING)
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
			if (children_[q]->getPatch()->getStatus() != PatchStatus::READY_TO_USE)
				childrenReady = false;
		}
	}
	
	return childrenReady;
}

Side QuadTreeNode::mirrorSide(unsigned int side)
{
	if (!neighbors_[side])
		return mirror(side);

	unsigned int f0 = face_->getFaceType();
	unsigned int f1 = neighbors_[side]->face_->getFaceType();

	if (f0 == f1 || ((f0 <= 2 || f0 == 4) && (f1 <= 2 || f1 == 4)))
		return mirror(side);

	if (f0 == FACE_TOP || f1 == FACE_TOP)
		return mirror(side);

	int res = sideMirrors[f0][f1];

	if (res == -1)
	{
		Logger::error("Side mirror is -1");
		return NORTH;
	}

	return (Side)res;
}

Quadrant QuadTreeNode::reflectQuadrant(unsigned int quadrant, unsigned int side)
{
	if (!neighbors_[side])
		return reflect(quadrant, side);

	if (!isOnSide(quadrant, side))
		return NORTH_EAST;

	unsigned int f0 = face_->getFaceType();
	unsigned int f1 = neighbors_[side]->face_->getFaceType();

	if (f0 == f1 || ((f0 <= 2 || f0 == 4) && (f1 <= 2 || f1 == 4)))
		return reflect(quadrant, side);

	if (f0 == FACE_TOP || f1 == FACE_TOP)
		return reflect(quadrant, side);

	int res = quadrantRelfections[f0][f1][quadrant];

	if (res == -1)
	{
		Logger::error("Quadrant reflection is -1");
		return NORTH_EAST;
	}

	return (Quadrant)res;
}

const int QuadTreeNode::sideMirrors[6][6] =
{
	{  -1 , -1 , -1 , -1 , -1 , -1  },
	{  -1 , -1 , -1 ,  1 , -1 ,  3  },
	{  -1 , -1 , -1 ,  2 , -1 ,  2  },
	{  -1 ,  1 ,  1 , -1 ,  1 , -1  },
	{  -1 , -1 , -1 ,  0 , -1 ,  0  },
	{  -1 ,  3 ,  3 , -1 ,  3 , -1  }
};

const int QuadTreeNode::quadrantRelfections[6][6][4] =
{
	{ { -1, -1, -1, -1 },{ -1, -1, -1, -1 },{ -1, -1, -1, -1 },{ -1, -1, -1, -1 },{ -1, -1, -1, -1 },{ -1, -1, -1, -1 } },
	{ { -1, -1, -1, -1 },{ -1, -1, -1, -1 },{ -1, -1, -1, -1 },{ -1, 2, 1, -1 },{ -1, -1, -1, -1 },{ 3, -1, -1, 0 } },
	{ { -1, -1, -1, -1 },{ -1, -1, -1, -1 },{ -1, -1, -1, -1 },{ -1, 3, 2, -1 },{ -1, -1, -1, -1 },{ 2, -1, -1, 3 } },
	{ { -1, -1, -1, -1 },{ -1, 2, 1, -1 },{ -1, -1, 2, 1 },{ -1, -1, -1, -1 },{ 2, 1, -1, -1 },{ -1, -1, -1, -1 } },
	{ { -1, -1, -1, -1 },{ -1, -1, -1, -1 },{ -1, -1, -1, -1 },{ -1, 1, 0, -1 },{ -1, -1, -1, -1 },{ 0, -1, -1, 1 } },
	{ { -1, -1, -1, -1 },{ 3, -1, -1, 0 },{ -1, -1, 0, 3 },{ -1, -1, -1, -1 },{ 0, 3, -1, -1 },{ -1, -1, -1, -1 } }
};