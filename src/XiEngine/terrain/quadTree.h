#pragma once

#include "../graphics/drawable.h"

#define QUAD_TREE_MAX_DEPTH 10
#define QUAD_TREE_SPLIT_DISTANCE_SCALE 2.0f

class QuadTreeNode;

class QuadTree : public Drawable
{
public:
	QuadTree();
	~QuadTree();

	virtual void update(const FrameInfo& frame);

	virtual void drawDebuGeometry(DebugRenderer* debug) override;
	virtual std::type_index getType() override;

protected:
	virtual void onWorldBoundingBoxUpdate() override;

private:
	QuadTreeNode* rootNode_;
};