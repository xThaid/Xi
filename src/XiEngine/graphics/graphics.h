#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../graphics/graphicsDefs.h"
#include "../math/ximath.h"

class IndexBuffer;
class Shader;
class VertexBuffer;
class Window;

class Graphics
{
public:
	inline static Graphics* getInstance() { return instance_; }

	Graphics(Window* window);
	~Graphics();

	void beginFrame();
	void endFrame();

	void clear(const Vector3& color);

	void draw(PrimitiveTopology topology, unsigned int start, unsigned int vertexCount);
	void drawElement(PrimitiveTopology topology, unsigned int indexStart, unsigned int indexCount);

	void setViewport();

	void setFillMode(FillMode fillMode);

	void setVBO(unsigned int VBO);

	void setVertexBuffer(VertexBuffer* vertexBuffer);
	void setIndexBuffer(IndexBuffer* indexBuffer);

	void setShader(Shader* shader);

	inline VertexBuffer* getVertexBuffer() { return vertexBuffer_; }
	inline IndexBuffer* getIndexBuffer() { return indexBuffer_; }

private:
	static Graphics* instance_;

	static void getGLPrimitiveType(unsigned int elementCount, PrimitiveTopology topology, unsigned int& primitiveCount, GLenum& glPrimitiveType);

	Window* window_;

	unsigned int numPrimitives_;
	unsigned int numBatches_;

	FillMode fillMode_;

	unsigned int boundVAO_;
	unsigned int boundVBO_;

	bool vertexBufferDirty_;
	VertexBuffer* vertexBuffer_;

	IndexBuffer* indexBuffer_;

	unsigned int enabledVertexAttributes_;

	Shader* shader_;

	void init();
	void release();

	void prepareDraw();

	void createVAO();
	void destroyVAO();
};