#pragma once

#include "../graphics/drawable.h"

const int QUAD_TREE_PATCH_EDGE_SIZE = 8;
const int QUAD_TREE_MAX_DEPTH = 6;
const float QUAD_TREE_SPLIT_DISTANCE_SCALE = 2.0f;

class IndexBuffer;
class QuadTreeNode;

class QuadTree : public Drawable
{
public:
	QuadTree();
	~QuadTree();

	virtual void update() override;

	virtual void getBatches(Camera* cullCamera, std::vector<Batch>& batches);

	virtual void drawDebugGeometry(DebugRenderer* debug) override;

	inline std::shared_ptr<IndexBuffer> getIndexBuffer() { return patchIndexBuffer_; }

protected:
	virtual void onWorldBoundingBoxUpdate() override;

private:
	QuadTreeNode* rootNode_;

	std::shared_ptr<IndexBuffer> patchIndexBuffer_;

	void prepareIndexBuffer();
};