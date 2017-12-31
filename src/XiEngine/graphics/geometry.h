#pragma once

#include "../graphics/graphicsDefs.h"

class IndexBuffer;
class Graphics;
class VertexBuffer;

class Geometry
{
public:
	Geometry(PrimitiveTopology topology, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer = nullptr);
	Geometry(PrimitiveTopology topology, VertexBuffer* vertexBuffer, std::shared_ptr<IndexBuffer>& indexBuffer);
	~Geometry();

	void draw(Graphics* graphics);
	void draw(Graphics* graphics, IndexBuffer* indexBuffer);

	inline std::shared_ptr<VertexBuffer> getVertexBuffer() { return vertexBuffer_; }

private:
	PrimitiveTopology topology_;
	
	std::shared_ptr<VertexBuffer> vertexBuffer_;
	std::shared_ptr<IndexBuffer> indexBuffer_;
};