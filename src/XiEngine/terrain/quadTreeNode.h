#pragma once

#include "../math/ximath.h"

struct Batch;

class Camera;
class DebugRenderer;
class QuadTree;
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
	QuadTreeNode(QuadTree* owner, QuadTreeNode* parent, Quadrant quadrant, Vector2 center, float size);
	~QuadTreeNode();

	void update(const Vector3& viewPos);

	void getBatches(Camera* cullCamera, std::vector<Batch>& batches);
	void drawDebugGeometry(DebugRenderer* debug);

	bool isLeaf() const;

	float getScale() const;

	inline QuadTree* getQuadTree() { return owner_; }

	inline Vector3 getWorldCenter() { return Vector3(center_.x_, 0.0f, -center_.y_); }
	inline float getSize() { return size_; }

private:
	QuadTree* owner_;

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