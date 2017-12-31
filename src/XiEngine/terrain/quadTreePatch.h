#pragma once

#include "../math/ximath.h"

class Geometry;
class IndexBuffer;
class QuadTreeNode;

enum Side;

class QuadTreePatch
{
public:
	QuadTreePatch(QuadTreeNode* owner_, unsigned int patchEdgeSize);
	~QuadTreePatch();
	
	void prepareVertices();

	void prepareGeometry();

	inline QuadTreeNode* getNode() { return node_; }

	inline BoundingBox& getBoundingBox() { return boundingBox_; }
	inline Geometry* getGeometry() { return geometry_; }

	inline float getHeight(int x, int y) { return heightData_[x * (patchEdgeSize_ + 1) + y]; }
	inline Vector3 getNormal(int x, int y) { return normals_[x * (patchEdgeSize_ + 1) + y]; }

private:
	QuadTreeNode* node_;

	BoundingBox boundingBox_;
	Geometry* geometry_;

	unsigned int patchEdgeSize_;
	float* heightData_;
	Vector3* normals_;

	Vector2 verticesNumToLocalPos(int x, int y);
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