#pragma once

#include "../math/ximath.h"

class DebugRenderer;
struct FrameInfo;
class QuadTreePatch;

enum Quadrant
{
	NORTH_EAST = 0,
	NORTH_WEST,
	SOUTH_WEST,
	SOUTH_EAST
};

class QuadTreeNode
{
public:
	QuadTreeNode(QuadTreeNode* parent, Quadrant quadrant, Vector2 center, float size);
	~QuadTreeNode();

	void update(const FrameInfo& frame);

	void drawDebugGeometry(DebugRenderer* debug);

	bool isLeaf() const;

	float getScale() const;

private:
	const QuadTreeNode* parent_;
	QuadTreeNode* children_[4];

	const Quadrant quadrant_;
	const unsigned int depth_;

	const Vector2 center_;
	const float size_;

	QuadTreePatch* patch_;

	BoundingBox boundingBox_;

	void split();
	void merge();
};