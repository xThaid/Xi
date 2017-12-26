#pragma once

#include "../math/ximath.h"

class Geometry;
class QuadTreeNode;

class QuadTreePatch
{
public:
	QuadTreePatch(QuadTreeNode* owner_, unsigned int patchEdgeSize);
	~QuadTreePatch();
	
	void prepareGeometry();

	inline QuadTreeNode* getNode() { return node_; }

	inline Geometry* getGeometry() { return geometry_; }

private:
	QuadTreeNode* node_;

	Geometry* geometry_;

	unsigned int patchEdgeSize_;
};