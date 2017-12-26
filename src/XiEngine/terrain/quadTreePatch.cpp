#include "quadTreePatch.h"

#include "../graphics/indexBuffer.h"
#include "../graphics/geometry.h"
#include "../graphics/graphicsDefs.h"
#include "../graphics/vertexBuffer.h"
#include "../terrain/quadTree.h"
#include "../terrain/quadTreeNode.h"

QuadTreePatch::QuadTreePatch(QuadTreeNode* node, unsigned int patchEdgeSize) :
	node_(node),
	patchEdgeSize_(patchEdgeSize)
{
	VertexBuffer* vertexBuffer = new VertexBuffer(MASK_POSITION);
	geometry_ = new Geometry(PrimitiveTopology::TRIANGLE_STRIP, vertexBuffer, node_->getQuadTree()->getIndexBuffer());
}

QuadTreePatch::~QuadTreePatch()
{
}

void QuadTreePatch::prepareGeometry()
{
	std::shared_ptr<VertexBuffer> vertexBuffer = geometry_->getVertexBuffer();
	
	unsigned int vertexCount = (patchEdgeSize_ + 1) * (patchEdgeSize_ + 1);
	vertexBuffer->create(vertexCount);

	float* data = new float[vertexCount * 3];
	
	unsigned int dataCounter = 0;
	for (unsigned int x = 0; x <= patchEdgeSize_; x++)
	{
		for (unsigned int y = 0; y <= patchEdgeSize_; y++)
		{
			Vector3 position = Vector3((float) x, 0, (float) y);

			position = ((position / (float)patchEdgeSize_) - Vector3(0.5f, 0.0f, 0.5f)) * 2.0f;

			data[dataCounter++] = position.x_;
			data[dataCounter++] = position.y_;
			data[dataCounter++] = position.z_;
		}
	}

	vertexBuffer->setData((void*)data);
	delete data;

}
