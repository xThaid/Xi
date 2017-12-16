#pragma once

#include "../precompiled.h"

#include "../graphics/graphics.h"
#include "../graphics/graphicsDefs.h"

class VertexBuffer
{
public:
	VertexBuffer(unsigned int elementMask);
	~VertexBuffer();

	bool create(unsigned int vertexCount);

	bool setData(const void* data);

	inline unsigned int getVBO() { return VBO_; }

	inline std::vector<std::pair<VertexElement, unsigned int> >& getElements() { return elements_; }
	inline unsigned int getVertexSize() { return vertexSize_; }

private:
	Graphics* graphics_;

	unsigned int VBO_;

	std::vector<std::pair<VertexElement, unsigned int> > elements_;
	unsigned int vertexSize_;
	unsigned int vertexCount_;

	void release();

	void parseElementsAndCalcOffsets(unsigned int elementMask);
};