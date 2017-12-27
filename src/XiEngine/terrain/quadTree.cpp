#include "quadTree.h"

#include "../graphics/camera.h"
#include "../graphics/indexBuffer.h"
#include "../scene/scene.h"
#include "../scene/sceneNode.h"
#include "../terrain/quadTreeNode.h"

QuadTree::QuadTree()
{
	patchIndexBuffer_ = std::shared_ptr<IndexBuffer>(new IndexBuffer());
	prepareIndexBuffer();

	rootNode_ = new QuadTreeNode(this, nullptr, NORTH_EAST, Vector2(0.0f, 0.0f), 100.0f);
}

QuadTree::~QuadTree()
{
	delete rootNode_;
}

void QuadTree::update()
{
	rootNode_->update(node_->getScene()->getCullCamera()->position);
}

void QuadTree::getBatches(Camera* cullCamera, std::vector<Batch>& batches)
{
	rootNode_->getBatches(cullCamera, batches);
}

void QuadTree::drawDebugGeometry(DebugRenderer* debug)
{
	rootNode_->drawDebugGeometry(debug);
}

void QuadTree::onWorldBoundingBoxUpdate()
{
	worldBoundingBox_ = BoundingBox(-2.0f, 2.0f);
}

void QuadTree::prepareIndexBuffer()
{
	unsigned int indicesCount = QUAD_TREE_PATCH_EDGE_SIZE * 2 * (QUAD_TREE_PATCH_EDGE_SIZE + 1);
	patchIndexBuffer_->create(indicesCount, true);

	unsigned int* data = new unsigned int[indicesCount];

	bool oddRow = false;
	int indicesCounter = 0;
	for (unsigned int y = 0; y < QUAD_TREE_PATCH_EDGE_SIZE; y++)
	{
		if (!oddRow)
		{
			for (unsigned int x = 0; x <= QUAD_TREE_PATCH_EDGE_SIZE; x++)
			{
				data[indicesCounter++] = y * (QUAD_TREE_PATCH_EDGE_SIZE + 1) + x;
				data[indicesCounter++] = (y + 1) * (QUAD_TREE_PATCH_EDGE_SIZE + 1) + x;
			}
		}
		else
		{
			for (int x = QUAD_TREE_PATCH_EDGE_SIZE; x >= 0; x--)
			{
				data[indicesCounter++] = (y + 1) * (QUAD_TREE_PATCH_EDGE_SIZE + 1) + x;
				data[indicesCounter++] = y * (QUAD_TREE_PATCH_EDGE_SIZE + 1) + x;
			}
		}

		oddRow = !oddRow;
	}

	patchIndexBuffer_->setData(data);
	
	delete data;
}
