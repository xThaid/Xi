#pragma once

#include "../graphics/graphicsDefs.h"

class IndexBuffer;
class Graphics;
class VertexBuffer;

class Geometry
{
public:
	Geometry(PrimitiveTopology topology, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer = nullptr);
	~Geometry();

	void draw(Graphics* graphics);

private:
	PrimitiveTopology topology_;
	
	VertexBuffer* vertexBuffer_;
	IndexBuffer* indexBuffer_;
};