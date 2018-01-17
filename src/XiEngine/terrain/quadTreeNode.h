#pragma once

#include "../math/ximath.h"

struct Batch;

class Camera;
class DebugRenderer;
class QuadTreeFace;
class QuadTreePatch;
class QuadTreePatchTopology;

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

	void cullNodesToRender(Camera* cullCamera, std::vector<QuadTreeNode*>& nodes);

	void drawDebugGeometry(DebugRenderer* debug);

	void setNeighbor(Side side, QuadTreeNode* neighbor);

	bool isLeaf() const;

	float getScale() const;

	Vector2 localToFacePos(const Vector2& localPos);

	QuadTreePatchTopology* getPatchTopology();

	inline bool lieOnNorth() { return isOnSide(quadrant_, NORTH); }
	inline bool lieOnEast() { return isOnSide(quadrant_, EAST); }

	inline QuadTreeFace* getFace() { return face_; }
	inline QuadTreeNode* getParent() { return parent_; }
	inline QuadTreePatch* getPatch() { return patch_; }

	inline QuadTreeNode* getNeighbor(Side side) { return neighbors_[side]; }

	inline float getSize() const { return size_; }

	inline bool shouldDrawBorders() { return drawBorders_; }
	inline Color borderColor() { return borderColor_; }

private:
	QuadTreeFace* face_;

	QuadTreeNode* parent_;
	QuadTreeNode* children_[4];

	QuadTreeNode* neighbors_[4];
	unsigned int neighborsDepthDiff_[4];

	const Quadrant quadrant_;
	const unsigned int depth_;

	Matrix3x4 nodeTransform_;
	const Vector2 center_;
	const float size_;

	std::condition_variable patchCV_;
	std::mutex patchMutex_;
	QuadTreePatch* patch_;

	bool drawBorders_;
	Color borderColor_;

	void propagateDownNeighbor(Side side);

	void split();
	void merge();

	bool areChildrenReadyToRender();

	static const int sideMirrors[6][6];
	static const int quadrantRelfections[6][6][4];

	inline static bool isOnSide(unsigned int quadrant, unsigned int side) { return ((4 + quadrant - side) % 4) <= 1; }

	inline static Side mirror(unsigned int side) { return (Side)((side + 2) % 4); }
	inline static Quadrant reflect(unsigned int quadrant, unsigned int side) 
	{ return (Quadrant)(side % 2 ? (quadrant % 2 ? quadrant - 1 : quadrant + 1) : 3 - quadrant); }

	Side mirrorSide(unsigned int side);
	Quadrant reflectQuadrant(unsigned int quadrant, unsigned int side);

	friend class TerrainGenerator;
};