#pragma once

#include "../math/ximath.h"

struct Batch;

class Camera;
class DebugRenderer;
class QuadTreeFace;
class QuadTreePatch;

enum Quadrant
{
	NORTH_EAST = 0,
	NORTH_WEST,
	SOUTH_WEST,
	SOUTH_EAST
};

enum Side
{
	NORTH = 0,
	WEST,
	SOUTH,
	EAST
};

class QuadTreeNode
{
public:
	QuadTreeNode(QuadTreeFace* face, QuadTreeNode* parent, Quadrant quadrant, Vector2 center, float size);
	~QuadTreeNode();

	void update(const Vector3& viewPos);

	void getBatches(Camera* cullCamera, std::vector<Batch>& batches);
	void drawDebugGeometry(DebugRenderer* debug);

	bool isLeaf() const;

	float getScale() const;

	Vector2 localToFacePos(const Vector2& localPos);

	inline bool lieOnNorth() { return isOnSide(quadrant_, NORTH); }
	inline bool lieOnEast() { return isOnSide(quadrant_, EAST); }

	inline QuadTreeFace* getFace() { return face_; }
	inline QuadTreeNode* getParent() { return parent_; }
	inline QuadTreePatch* getPatch() { return patch_; }

	inline float getSize() const { return size_; }

private:
	QuadTreeFace* face_;

	QuadTreeNode* parent_;
	QuadTreeNode* children_[4];

	QuadTreeNode* neighbors_[4];
	unsigned int neighborsDepthDiff_[4];

	const Quadrant quadrant_;
	const unsigned int depth_;

	Matrix4 nodeTransform_;
	const Vector2 center_;
	const float size_;

	QuadTreePatch* patch_;

	void setNeighbor(Side side, QuadTreeNode* neighbor);
	void propagateDownNeighbor(Side side);

	void split();
	void merge();

	bool areChildrenReadyToRender();

	inline static Side mirrorSide(unsigned int side) { return (Side)((side + 2) % 4); }
	inline static bool isOnSide(unsigned int quadrant, unsigned int side) { return ((4 + quadrant - side) % 4) <= 1; }
	inline static Quadrant reflectQuadrant(unsigned int quadrant, unsigned int side) 
	{ return (Quadrant)(side % 2 ? (quadrant % 2 ? quadrant - 1 : quadrant + 1) : 3 - quadrant); }
};