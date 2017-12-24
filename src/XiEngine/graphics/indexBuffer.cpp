#include "indexBuffer.h"

#include "../graphics/graphics.h"

IndexBuffer::IndexBuffer() :
	graphics_(Graphics::getInstance()),
	EBO_(0),
	indexSize_(0),
	indexCount_(0)
{
}

IndexBuffer::~IndexBuffer()
{
	release();
}

bool IndexBuffer::create(unsigned int indexCount, bool largeIndices)
{
	indexCount_ = indexCount;
	indexSize_ = (unsigned)(largeIndices ? sizeof(unsigned) : sizeof(unsigned short));

	if (indexCount_ == 0)
	{
		release();
		return false;
	}

	if (!EBO_)
		glGenBuffers(1, &EBO_);

	graphics_->setIndexBuffer(this);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount_ * indexSize_, nullptr, GL_STATIC_DRAW);

	return true;
}

bool IndexBuffer::setData(const void* data)
{
	if (data == 0)
		return false;

	if (EBO_)
	{
		graphics_->setIndexBuffer(this);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount_ * indexSize_, data, GL_STATIC_DRAW);
	}

	return true;
}

void IndexBuffer::release()
{
	if (EBO_)
	{
		if(graphics_->getIndexBuffer() == this)
			graphics_->setIndexBuffer(nullptr);

		glDeleteBuffers(1, &EBO_);

		EBO_ = 0;
	}
}
