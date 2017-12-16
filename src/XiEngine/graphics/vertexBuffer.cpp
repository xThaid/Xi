#include "vertexBuffer.h"

#include <glad/glad.h>

VertexBuffer::VertexBuffer(unsigned int elementMask) :
	graphics_(Graphics::getInstance()),
	VBO_(0),
	vertexSize_(0),
	vertexCount_(0)
{
	parseElementsAndCalcOffsets(elementMask);
}

VertexBuffer::~VertexBuffer()
{
	release();
}

bool VertexBuffer::create(unsigned int vertexCount)
{
	vertexCount_ = vertexCount;
	if (vertexCount_ == 0 || elements_.size() == 0)
	{
		release();
		return false;
	}

	if (!VBO_)
		glGenBuffers(1, &VBO_);

	graphics_->setVBO(VBO_);
	glBufferData(GL_ARRAY_BUFFER, vertexCount_ * vertexSize_, nullptr, GL_STATIC_DRAW);

	return true;
}

bool VertexBuffer::setData(const void* data)
{
	if (data == 0 || vertexSize_ == 0)
		return false;

	if (VBO_)
	{
		graphics_->setVBO(VBO_);
		glBufferData(GL_ARRAY_BUFFER, vertexCount_ * vertexSize_, data, GL_STATIC_DRAW);
	}

	return true;
}

void VertexBuffer::release()
{
	if (VBO_)
	{
		graphics_->setVBO(0);
		glDeleteBuffers(1, &VBO_);
		
		VBO_ = 0;
	}
}

void VertexBuffer::parseElementsAndCalcOffsets(unsigned int elementMask)
{
	elements_.clear();

	unsigned int elementOffset = 0;

	for (int i = 0; i < MAX_VERTEX_ELEMENT; i++)
	{
		if (elementMask & (1 << i))
		{
			elements_.push_back({ (VertexElement)i, elementOffset });
			elementOffset += ELEMENT_TYPESIZES[VERTEXELEMENTS[i].type_];
		}
	}

	vertexSize_ = elementOffset;
}
