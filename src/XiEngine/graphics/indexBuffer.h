#pragma once

class Graphics;

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	bool create(unsigned int indexCount, bool largeIndices);

	bool setData(const void* data);

	inline unsigned int getEBO() { return EBO_; }
	inline unsigned int getIndexSize() { return indexSize_; }
	inline unsigned int getIndexCount() { return indexCount_; }

private:
	Graphics* graphics_;

	unsigned int EBO_;

	unsigned int indexCount_;
	unsigned int indexSize_;

	void release();
};