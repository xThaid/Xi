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
	VertexBuffer* vertexBuffer = new VertexBuffer(MASK_POSITION | MASK_NORMAL);
	geometry_ = new Geometry(PrimitiveTopology::TRIANGLES, vertexBuffer, nullptr);
	
	unsigned int vertexCount = (patchEdgeSize_ + 1) * (patchEdgeSize_ + 1);

	heightData_ = new float[vertexCount];
	normals_ = new Vector3[vertexCount];
}

QuadTreePatch::~QuadTreePatch()
{
	delete geometry_;

	delete[] heightData_;
	delete[] normals_;
}

void QuadTreePatch::prepareVertices()
{
	for (unsigned int x = 0; x <= patchEdgeSize_; x++)
	{
		for (unsigned int y = 0; y <= patchEdgeSize_; y++)
		{
			Vector2 localPos = verticesNumToLocalPos(x, y);
			float height = node_->calcHeightFromLocalPos(localPos);
			heightData_[x * (patchEdgeSize_ + 1) + y] =  height;

			Vector3 point(localPos.x_, height, localPos.y_);
			boundingBox_.merge(point);
		}
	}

	for (unsigned int x = 0; x <= patchEdgeSize_; x++)
	{
		for (unsigned int y = 0; y <= patchEdgeSize_; y++)
		{
			Vector3 normal;
			if (x == 0 || x == patchEdgeSize_ || y == 0 || y == patchEdgeSize_)
				normal = Vector3(0.0f, 1.0f, 0.0f);
			else
			{
				normal.y_ = 2.0f;
				normal.x_ = (getHeight(x - 1, y) - getHeight(x + 1, y)) / node_->getScale();
				normal.z_ = (getHeight(x, y - 1) - getHeight(x, y + 1)) / node_->getScale();

				normal.normalize();
			}

			normals_[x * (patchEdgeSize_ + 1) + y] = normal;
		}
	}
}

void QuadTreePatch::prepareGeometry()
{
	std::shared_ptr<VertexBuffer> vertexBuffer = geometry_->getVertexBuffer();
	
	unsigned int vertexCount = (patchEdgeSize_ + 1) * (patchEdgeSize_ + 1);
	vertexBuffer->create(vertexCount);

	float* data = new float[vertexCount * 6];
	
	unsigned int dataCounter = 0;
	for (unsigned int x = 0; x <= patchEdgeSize_; x++)
	{
		for (unsigned int y = 0; y <= patchEdgeSize_; y++)
		{
			Vector2 localPos = verticesNumToLocalPos(x, y);
			data[dataCounter++] = localPos.x_;
			data[dataCounter++] = getHeight(x, y);
			data[dataCounter++] = localPos.y_;

			Vector3 normal = getNormal(x, y);

			data[dataCounter++] = normal.x_;
			data[dataCounter++] = normal.y_;
			data[dataCounter++] = normal.z_;
		}
	}

	vertexBuffer->setData((void*)data);
	delete data;
}

Vector2 QuadTreePatch::verticesNumToLocalPos(int x, int y)
{
	Vector2 localPos = Vector2((float)x, (float)y) / (float)patchEdgeSize_;
	localPos -= Vector2(0.5f);
	localPos *= 2.0f;

	return localPos;
}

QuadTreePatchTopology::QuadTreePatchTopology(
	unsigned int edgeSize,
	unsigned int detailNorth, unsigned int detailWest, unsigned int detailSouth, unsigned int detailEast) :
	edgeSize_(edgeSize),
	detailNorth_(detailNorth),
	detailWest_(detailWest),
	detailSouth_(detailSouth),
	detailEast_(detailEast),
	indexBuffer_(new IndexBuffer())
{
	prepare();
}

QuadTreePatchTopology::~QuadTreePatchTopology()
{
	delete indexBuffer_;
}

void QuadTreePatchTopology::prepare()
{
	counter_ = 0;
	data_ = new unsigned short[edgeSize_ * edgeSize_ * 6];

	prepareCenter();

	prepareEdge(NORTH, detailNorth_);
	prepareEdge(WEST, detailWest_);
	prepareEdge(SOUTH, detailSouth_);
	prepareEdge(EAST, detailEast_);

	indexBuffer_->create(counter_, false);
	indexBuffer_->setData(data_);

	delete[] data_;
}

void QuadTreePatchTopology::prepareCenter()
{
	for (unsigned int x = 1; x < edgeSize_ - 1; x += 2)
	{
		for (unsigned int y = 1; y < edgeSize_ - 1; y += 2)
		{
			addTriangle(x * (edgeSize_ + 1) + y, x * (edgeSize_ + 1) + y + 1, (x + 1) * (edgeSize_ + 1) + y + 1);
			addTriangle(x * (edgeSize_ + 1) + y, (x + 1) * (edgeSize_ + 1) + y + 1, (x + 1) * (edgeSize_ + 1) + y);
			addTriangle((x + 1)* (edgeSize_ + 1) + y, (x + 1) * (edgeSize_ + 1) + y + 1, (x + 2) * (edgeSize_ + 1) + y);
			addTriangle((x + 2) * (edgeSize_ + 1) + y, (x + 1) * (edgeSize_ + 1) + y + 1, (x + 2) * (edgeSize_ + 1) + y + 1);
			
			addTriangle(x * (edgeSize_ + 1) + y + 1, x * (edgeSize_ + 1) + y + 1 + 1, (x + 1) * (edgeSize_ + 1) + y + 1);
			addTriangle((x + 1) * (edgeSize_ + 1) + y + 1, x * (edgeSize_ + 1) + y + 1 + 1, (x + 1) * (edgeSize_ + 1) + y + 1 + 1);
			addTriangle((x + 1)* (edgeSize_ + 1) + y + 1, (x + 1) * (edgeSize_ + 1) + y + 1 + 1, (x + 2) * (edgeSize_ + 1) + y + 1 + 1);
			addTriangle((x + 1) * (edgeSize_ + 1) + y + 1, (x + 2) * (edgeSize_ + 1) + y + 1 + 1, (x + 2) * (edgeSize_ + 1) + y + 1);
		}
	}
}

void QuadTreePatchTopology::prepareEdge(Side side, unsigned int detail)
{
	if (detail == 0 || detail > QUAD_TREE_MAX_DEPTH_DIFF)
	{
		for (unsigned int i = 0; i < edgeSize_ - 1; i += 2)
		{
			addTriangle(ind(0, i, side), ind(0, i + 1, side), ind(1, i + 1, side));
			addTriangle(ind(0, i + 2, side), ind(1, i + 1, side), ind(0, i + 1, side));
		}

		for (unsigned int i = 1; i < edgeSize_ - 1; i += 2)
		{
			addTriangle(ind(1, i, side), ind(1, i + 1, side), ind(0, i + 1, side));
			addTriangle(ind(1, i + 2, side), ind(1, i + 1, side), ind(0, i + 1, side));
		}
		
		return;
	}

	unsigned int step = (1 << detail);
	unsigned int start = 1;

	for (unsigned y = 0; y < edgeSize_; y += step)
	{
		addTriangle(ind(0, y, side), ind(0, y + step, side), ind(1, (step + 1) / 2 + y, side));

		for (unsigned int i = start; i < ((step + 1) / 2 + y); i++)
			addTriangle(ind(0, y, side),ind(1, i, side), ind(1, i + 1, side));

		start = ((step + 1) / 2 + y);
	}

	for (unsigned int i = start; i < edgeSize_ - 1; i++)
		addTriangle(ind(0, edgeSize_, side), ind(1, i, side), ind(1, i + 1, side));
}

void QuadTreePatchTopology::addTriangle(unsigned short v1, unsigned short v2, unsigned short v3)
{
	unsigned short temp[3] = { v1, v2, v3 };
	std::sort(temp, temp + 3);

	int x1 = v1 / (edgeSize_ + 1), y1 = v1 % (edgeSize_ + 1);
	int x2 = v2 / (edgeSize_ + 1), y2 = v2 % (edgeSize_ + 1);
	int x3 = v3 / (edgeSize_ + 1), y3 = v3 % (edgeSize_ + 1);

	x2 -= x1; y2 -= y1;
	x3 -= x1; y3 -= y1;

	if (x2 * y3 - x3 * y2 > 0)
	{
		data_[counter_++] = v1;
		data_[counter_++] = v3;
		data_[counter_++] = v2;
	}
	else
	{
		data_[counter_++] = v1;
		data_[counter_++] = v2;
		data_[counter_++] = v3;

	}
}

unsigned short QuadTreePatchTopology::ind(unsigned int x, unsigned int y, Side side)
{
	rotate(x, y, side);

	return x * (edgeSize_ + 1) + y;
}

void QuadTreePatchTopology::rotate(unsigned int& x, unsigned int& y, Side side)
{
	switch (side)
	{
	case WEST:
		return;
	case EAST:
		x = edgeSize_ - x;
		return;
	case NORTH:
		std::swap(x, y);
		return;
	case SOUTH:
		x = edgeSize_ - x;
		std::swap(x, y);
		return;
	}
}