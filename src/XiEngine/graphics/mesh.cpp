#include "mesh.h"

#include <glad/glad.h>

#include "../graphics/indexBuffer.h"
#include "../graphics/geometry.h"
#include "../graphics/vertexBuffer.h"
#include "../utils/logger.h"

MeshGeometry::MeshGeometry(PrimitiveTopology topology,
	std::vector<unsigned int>* indices,
	std::vector<Vector3>* positions,
	std::vector<Vector3>* normals,
	std::vector<Vector2>* texCoords) :
	topology_(topology),
	indices_(indices),
	positions_(positions),
	normals_(normals),
	texCoords_(texCoords)
{
}

MeshGeometry::~MeshGeometry()
{
	if (indices_ != nullptr)
		delete indices_;

	if (positions_ != nullptr)
		delete positions_;
	if (normals_ != nullptr)
		delete normals_;
	if (texCoords_ != nullptr)
		delete texCoords_;
}

bool MeshGeometry::hasIndices()
{
	return indices_ != nullptr && indices_->size() >= 0;
}

bool MeshGeometry::hasPositions()
{
	return positions_ != nullptr && positions_->size() >= 0;
}

bool MeshGeometry::hasNormals()
{
	return normals_ != nullptr && normals_->size() >= 0;
}

bool MeshGeometry::hasTexCoords()
{
	return texCoords_ != nullptr && texCoords_->size() >= 0;
}

unsigned int* MeshGeometry::getIndicesData()
{
	return &(*indices_)[0];
}

float* MeshGeometry::prepareVertexData()
{
	unsigned int vertexSize = 3;
	if (hasNormals()) vertexSize += 3;
	if (hasTexCoords()) vertexSize += 2;

	float* data = new float[getNumVertices() * vertexSize];

	unsigned int dataCounter = 0;
	for (unsigned int i = 0; i < getNumVertices(); i++)
	{
		data[dataCounter++] = (*positions_)[i].x_;
		data[dataCounter++] = (*positions_)[i].y_;
		data[dataCounter++] = (*positions_)[i].z_;

		if (hasNormals())
		{
			data[dataCounter++] = (*normals_)[i].x_;
			data[dataCounter++] = (*normals_)[i].y_;
			data[dataCounter++] = (*normals_)[i].z_;
		}

		if (hasTexCoords())
		{
			data[dataCounter++] = (*texCoords_)[i].x_;
			data[dataCounter++] = (*texCoords_)[i].y_;
		}
	}

	return data;
}

bool MeshGeometry::isCorrect()
{
	if (!hasPositions())
		return false;

	if (hasNormals() && normals_->size() != getNumVertices())
		return false;

	if (hasTexCoords() && texCoords_->size() != getNumVertices())
		return false;

	return true;
}

unsigned int MeshGeometry::getMemoryUse()
{
	unsigned int memoryUse = sizeof(Vector3) * getNumVertices();
	if (hasIndices()) memoryUse += sizeof(unsigned int) * getNumIndices();
	if (hasNormals()) memoryUse += sizeof(Vector3) * getNumVertices();
	if (hasTexCoords()) memoryUse += sizeof(Vector2) * getNumVertices();
	
	return memoryUse;
}

Mesh::Mesh(const std::string& name, MeshGeometry* meshGeometry) :
	Resource(name),
	meshGeometry_(meshGeometry),
	geometry_(nullptr)
{
}
	
Mesh::~Mesh()
{
	if (meshGeometry_ != nullptr)
		delete meshGeometry_;
}

bool Mesh::beginLoad()
{
	if (!meshGeometry_->isCorrect())
		return false;

	setMemoryUse(meshGeometry_->getMemoryUse());

	boundingBox_.define(meshGeometry_->getPositions(), meshGeometry_->getNumVertices());

	return true;
}

bool Mesh::endLoad()
{
	unsigned int elementMask = MASK_POSITION;
	if (meshGeometry_->hasNormals()) elementMask |= MASK_NORMAL;
	if (meshGeometry_->hasTexCoords()) elementMask |= MASK_TEXCOORD;

	VertexBuffer* vertexBuffer = new VertexBuffer(elementMask);
	vertexBuffer->create(meshGeometry_->getNumVertices());

	float* data = meshGeometry_->prepareVertexData();

	vertexBuffer->setData((void*) data);
	delete data;

	IndexBuffer* indexBuffer = nullptr;
	
	if (meshGeometry_->hasIndices())
	{
		indexBuffer = new IndexBuffer();
		indexBuffer->create(meshGeometry_->getNumIndices(), true);
		indexBuffer->setData(meshGeometry_->getIndicesData());
	}

	geometry_ = new Geometry(meshGeometry_->getPrimitiveTopology(), vertexBuffer, indexBuffer);

	return true;
}

void Mesh::release()
{
	delete geometry_;
}