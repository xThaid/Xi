#include "mesh.h"

#include <glad\glad.h>

#include "../utils/logger.h"

Mesh::Mesh(const std::string& name,
	MeshTopology topology,
	std::vector<unsigned int>* indices,
	std::vector<xim::Vector3>* positions,
	std::vector<xim::Vector2>* UV,
	std::vector<xim::Vector3>* normals) :
	Resource(name),
	topology_(topology),
	indices_(indices),
	positions_(positions),
	UV_(UV),
	normals_(normals),
	VAO_(0)
{
}
	
Mesh::~Mesh()
{
	if (positions_ != nullptr)
		delete positions_;
	if (UV_ != nullptr)
		delete UV_;
	if (normals_ != nullptr)
		delete normals_;

	if (indices_ != nullptr)
		delete indices_;
}

bool Mesh::beginLoad()
{
	if (!hasPositions())
		return false;

	unsigned int numVertex = positions_->size();

	if (hasUV() && UV_->size() != numVertex)
		return false;

	if (hasUV() && normals_->size() != numVertex)
		return false;

	unsigned int memoryUse = sizeof(xim::Vector3) * positions_->size();
	if (hasUV()) memoryUse += sizeof(xim::Vector2) * UV_->size();
	if (hasNormals()) memoryUse += sizeof(xim::Vector3) * normals_->size();
	if (hasIndices()) memoryUse += sizeof(unsigned int) * indices_->size();

	setMemoryUse(memoryUse);

	return true;
}

bool Mesh::endLoad()
{
	return uploadToGPU(true);
}

void Mesh::release()
{

}

bool Mesh::hasPositions()
{ 
	return positions_ != nullptr && positions_->size() >= 0; 
}

bool Mesh::hasUV()
{
	return UV_ != nullptr && UV_->size() >= 0; 
}

bool Mesh::hasNormals() 
{
	return normals_ != nullptr && normals_->size() >= 0;
}

bool Mesh::hasIndices() 
{
	return indices_ != nullptr && indices_->size() >= 0; 
}

void Mesh::setPositions(std::vector<xim::Vector3>* positions)
{
	positions_ = positions;
}

void Mesh::setUV(std::vector<xim::Vector2>* UV)
{
	UV_ = UV;
}

void Mesh::setNormals(std::vector<xim::Vector3>* normals)
{
	normals_ = normals;
}

void Mesh::setIndices(std::vector<unsigned int>* indices)
{
	indices_ = indices;
}

bool Mesh::uploadToGPU(bool interleaved)
{
	std::vector<float> data;
	prepareData(data, interleaved);

	glGenVertexArrays(1, &VAO_);
	glGenBuffers(1, &VBO_);
	glGenBuffers(1, &EBO_);

	glBindVertexArray(VAO_);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

	if (hasIndices())
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_->size() * sizeof(unsigned int), &(*indices_)[0], GL_STATIC_DRAW);
	}

	if (interleaved)
	{
		unsigned int      stride  = 3 * sizeof(float);
		if (hasUV())      stride += 2 * sizeof(float);
		if (hasNormals()) stride += 3 * sizeof(float);
	
		unsigned int offset = 0;

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
		offset += 3 * sizeof(float);
		
		if (hasUV())
		{
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
			offset += 2 * sizeof(float);
		}

		if (hasNormals())
		{
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
			offset += 3 * sizeof(float);
		}
	}
	else
	{
		unsigned int numVertex = positions_->size();
		unsigned int offset = 0;

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)offset);
		offset += numVertex * sizeof(float) * 3;
		if (hasUV())
		{
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (GLvoid*)offset);
			offset += numVertex * sizeof(float) * 2;
		}
		if (hasNormals())
		{
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)offset);
			offset += numVertex * sizeof(float) * 3;
		}
	}

	return true;
}

void Mesh::prepareData(std::vector<float>& data, bool interleaved)
{
	if (!hasPositions())
		return;

	int floatsPerVertex = 3;
	if (hasUV()) floatsPerVertex += 2;
	if (hasNormals()) floatsPerVertex += 3;

	int numVertex = positions_->size();

	data.resize(floatsPerVertex * numVertex);

	int dataCounter = 0;
	if (interleaved)
	{
		for (int i = 0; i < numVertex; i++)
		{
			data[dataCounter++] = (*positions_)[i].data[0];
			data[dataCounter++] = (*positions_)[i].data[1];
			data[dataCounter++] = (*positions_)[i].data[2];

			if (hasUV())
			{
				data[dataCounter++] = (*UV_)[i].data[0];
				data[dataCounter++] = (*UV_)[i].data[1];
			}

			if (hasNormals())
			{
				data[dataCounter++] = (*normals_)[i].data[0];
				data[dataCounter++] = (*normals_)[i].data[1];
				data[dataCounter++] = (*normals_)[i].data[2];
			}
		}
	}
	else
	{
		for (int i = 0; i < numVertex; i++)
		{
			data[dataCounter++] = (*positions_)[i].data[0];
			data[dataCounter++] = (*positions_)[i].data[1];
			data[dataCounter++] = (*positions_)[i].data[2];
		}

		if (hasUV())
		{
			for (int i = 0; i < numVertex; i++)
			{
				data[dataCounter++] = (*UV_)[i].data[0];
				data[dataCounter++] = (*UV_)[i].data[1];
			}
		}

		if (hasNormals())
		{
			for (int i = 0; i < numVertex; i++)
			{
				data[dataCounter++] = (*normals_)[i].data[0];
				data[dataCounter++] = (*normals_)[i].data[1];
				data[dataCounter++] = (*normals_)[i].data[2];
			}
		}
	}
}
