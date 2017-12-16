#include "mesh.h"

#include <glad\glad.h>

#include "../utils/logger.h"

MeshGeometry::MeshGeometry(PrimitiveTopology topology,
	std::vector<unsigned int>* indices,
	std::vector<Vector3>* positions,
	std::vector<Vector2>* UV,
	std::vector<Vector3>* normals) :
	topology_(topology),
	indices_(indices),
	positions_(positions),
	UV_(UV),
	normals_(normals)
{
}

MeshGeometry::~MeshGeometry()
{
	if (indices_ != nullptr)
		delete indices_;

	if (positions_ != nullptr)
		delete positions_;
	if (UV_ != nullptr)
		delete UV_;
	if (normals_ != nullptr)
		delete normals_;
}

bool MeshGeometry::hasIndices()
{
	return indices_ != nullptr && indices_->size() >= 0;
}

bool MeshGeometry::hasPositions()
{
	return positions_ != nullptr && positions_->size() >= 0;
}

bool MeshGeometry::hasUV()
{
	return UV_ != nullptr && UV_->size() >= 0;
}

bool MeshGeometry::hasNormals()
{
	return normals_ != nullptr && normals_->size() >= 0;
}

unsigned int* MeshGeometry::getIndicesData()
{
	return &(*indices_)[0];
}

void MeshGeometry::prepareData(std::vector<float>& data, bool interleaved)
{
}

bool MeshGeometry::isCorrect()
{
	if (!hasPositions())
		return false;

	if (hasUV() && UV_->size() != getNumVertices())
		return false;

	if (hasNormals() && normals_->size() != getNumVertices())
		return false;

	return true;
}

unsigned int MeshGeometry::getMemoryUse()
{
	unsigned int memoryUse = sizeof(Vector3) * getNumVertices();
	if (hasUV()) memoryUse += sizeof(Vector2) * getNumVertices();
	if (hasNormals()) memoryUse += sizeof(Vector3) * getNumVertices();
	if (hasIndices()) memoryUse += sizeof(unsigned int) * getNumIndices();

	return memoryUse;
}

Mesh::Mesh(const std::string& name, MeshGeometry* meshGeometry) :
	Resource(name),
	meshGeometry_(meshGeometry),
	VAO_(0),
	drawMode_(0)
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

	return true;
}

bool Mesh::endLoad()
{
	parseTopology();
	return uploadToGPU(true);
}

void Mesh::release()
{
	glDeleteBuffers(1, &VBO_);
	glDeleteBuffers(1, &EBO_);

	glDeleteVertexArrays(1, &VAO_);
}

bool Mesh::uploadToGPU(bool interleaved)
{
	std::vector<float> data;
	meshGeometry_->prepareData(data, interleaved);

	glGenVertexArrays(1, &VAO_);
	glGenBuffers(1, &VBO_);
	glGenBuffers(1, &EBO_);

	glBindVertexArray(VAO_);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

	if (meshGeometry_->hasIndices())
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshGeometry_->getNumIndices() * sizeof(unsigned int), meshGeometry_->getIndicesData(), GL_STATIC_DRAW);
	}

	if (interleaved)
	{
		unsigned int      stride  = 3 * sizeof(float);
		if (meshGeometry_->hasUV())      stride += 2 * sizeof(float);
		if (meshGeometry_->hasNormals()) stride += 3 * sizeof(float);
	
		unsigned int offset = 0;

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
		offset += 3 * sizeof(float);
		
		if (meshGeometry_->hasUV())
		{
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
			offset += 2 * sizeof(float);
		}

		if (meshGeometry_->hasNormals())
		{
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
			offset += 3 * sizeof(float);
		}
	}
	else
	{
		unsigned int numVertex = meshGeometry_->getNumVertices();
		unsigned int offset = 0;

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)offset);
		offset += numVertex * sizeof(float) * 3;
		if (meshGeometry_->hasUV())
		{
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (GLvoid*)offset);
			offset += numVertex * sizeof(float) * 2;
		}
		if (meshGeometry_->hasNormals())
		{
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)offset);
			offset += numVertex * sizeof(float) * 3;
		}
	}

	return true;
}

void Mesh::parseTopology()
{
	switch (meshGeometry_->getPrimitiveTopology())
	{
	case PrimitiveTopology::POINTS:
		drawMode_ = GL_POINTS;
		break;
	case PrimitiveTopology::LINES:
		drawMode_ = GL_LINES;
		break;
	case PrimitiveTopology::LINE_STRIP:
		drawMode_ = GL_LINE_STRIP;
		break;
	case PrimitiveTopology::TRIANGLES:
		drawMode_ = GL_TRIANGLES;
		break;
	case PrimitiveTopology::TRIANGLE_STRIP:
		drawMode_ = GL_TRIANGLE_STRIP;
		break;
	case PrimitiveTopology::TRIANGLE_FAN:
		drawMode_ = GL_TRIANGLE_FAN;
		break;
	}
}
