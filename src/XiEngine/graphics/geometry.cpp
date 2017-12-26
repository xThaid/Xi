#include "geometry.h"

#include "../graphics/graphics.h"
#include "../graphics/indexBuffer.h"
#include "../graphics/vertexBuffer.h"

Geometry::Geometry(PrimitiveTopology topology, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) :
	topology_(topology),
	vertexBuffer_(vertexBuffer),
	indexBuffer_(indexBuffer)
{
}

Geometry::Geometry(PrimitiveTopology topology, VertexBuffer* vertexBuffer, std::shared_ptr<IndexBuffer>& indexBuffer) :
	topology_(topology),
	vertexBuffer_(vertexBuffer),
	indexBuffer_(indexBuffer)
{
}

Geometry::~Geometry()
{
}

void Geometry::draw(Graphics* graphics)
{
	if (!vertexBuffer_)
		return;

	graphics->setVertexBuffer(vertexBuffer_.get());

	if (indexBuffer_)
	{
		graphics->setIndexBuffer(indexBuffer_.get());
		graphics->drawElement(topology_, 0, indexBuffer_->getIndexCount());
	}
	else
	{
		graphics->draw(topology_, 0, vertexBuffer_->getVertexCount());
	}
}
