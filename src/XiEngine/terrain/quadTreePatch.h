#pragma once

#include "../math/ximath.h"

#include "../terrain/terrain.h"

class Geometry;
class IndexBuffer;
class QuadTreeNode;
class QuadTreePatchTopology;

enum Side;

class QuadTreePatch
{
public:
	QuadTreePatch(QuadTreeNode* node, unsigned int patchEdgeSize);
	~QuadTreePatch();
	
	void prepareVertices();

	void prepareGeometry();

	inline QuadTreeNode* getNode() { return node_; }

	inline BoundingBox& getBoundingBox() { return boundingBox_; }
	inline Geometry* getGeometry() { return geometry_; }

	inline static QuadTreePatchTopology* getTopology(unsigned int detailNorth, unsigned int detailWest, unsigned int detailSouth, unsigned int detailEast)
	{ return topologies_[detailNorth][detailWest][detailSouth][detailEast]; }

private:
	static int instances_;
	static QuadTreePatchTopology* topologies_[QUAD_TREE_MAX_DEPTH_DIFF + 1][QUAD_TREE_MAX_DEPTH_DIFF + 1][QUAD_TREE_MAX_DEPTH_DIFF + 1][QUAD_TREE_MAX_DEPTH_DIFF + 1];

	QuadTreeNode* node_;

	BoundingBox boundingBox_;
	Geometry* geometry_;

	unsigned int patchEdgeSize_;
	Vector3* positions_;
	Vector3* normals_;

	void generateTopologies();
	void deleteTopologies();

	inline unsigned int ind(unsigned int x, unsigned int y) { return x * (patchEdgeSize_ + 1) + y; }
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