#pragma once

#include "../math/ximath.h"

#include "../terrain/terrain.h"
#include "quadTreeNode.h"

class Geometry;
class IndexBuffer;
class QuadTreeNode;
class QuadTreePatchTopology;

enum class PatchStatus
{
	UNLOADED = 0,
	LOADING,
	RAM_LOADED,
	READY_TO_USE,
};

class QuadTreePatch
{
public:
	QuadTreePatch(unsigned int ID, QuadTreeNode* node, unsigned int edgeSize);
	~QuadTreePatch();
	
	void prepareGeometry();

	PatchStatus getStatus() const;

	inline unsigned int getID() { return ID_; }

	inline QuadTreeNode* getNode() { return node_; }

	inline BoundingBox& getBoundingBox() { return boundingBox_; }
	inline Geometry* getGeometry() { return geometry_; }

	inline unsigned int getEdgeSize() { return edgeSize_; }
	inline Vector3 getVertex(unsigned int x, unsigned int y) { return positions_[ind(x, y)]; }

	inline static QuadTreePatchTopology* getTopology(unsigned int detailNorth, unsigned int detailWest, unsigned int detailSouth, unsigned int detailEast)
	{ return topologies_[detailNorth][detailWest][detailSouth][detailEast]; }

private:
	static int instances_;
	static QuadTreePatchTopology* topologies_[QUAD_TREE_MAX_DEPTH_DIFF + 1][QUAD_TREE_MAX_DEPTH_DIFF + 1][QUAD_TREE_MAX_DEPTH_DIFF + 1][QUAD_TREE_MAX_DEPTH_DIFF + 1];

	unsigned int ID_;

	QuadTreeNode* node_;
	QuadTreePatch* parentPatch_;

	std::atomic<PatchStatus> status_;

	BoundingBox boundingBox_;
	Geometry* geometry_;

	unsigned int edgeSize_;
	Vector3* positions_;
	Vector3* normals_;
	Vector2* texCoord_;

	void generateTopologies();
	void deleteTopologies();

	inline unsigned int ind(unsigned int x, unsigned int y) { return x * (edgeSize_ + 1) + y; }

	friend class TerrainGenerator;
};

class QuadTreePatchTopology
{
public:
	QuadTreePatchTopology(unsigned int edgeSize, unsigned int detailNorth, unsigned int detailWest, unsigned int detailSouth, unsigned int detailEast);
	~QuadTreePatchTopology();

	inline IndexBuffer* getIndexBuffer() { return indexBuffer_; }

private:
	unsigned int edgeSize_;
	unsigned int detailNorth_;
	unsigned int detailWest_;
	unsigned int detailSouth_;
	unsigned int detailEast_;

	IndexBuffer* indexBuffer_;

	unsigned short* data_;
	unsigned int counter_;

	void prepare();

	void prepareCenter();
	void prepareEdge(Side side, unsigned int detail);

	void addTriangle(unsigned short v1, unsigned short v2, unsigned short v3);

	unsigned short ind(unsigned int x, unsigned int y, Side side);
	void rotate(unsigned int& x, unsigned int& y, Side side);
};