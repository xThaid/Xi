#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../graphics/graphicsDefs.h"
#include "../math/ximath.h"

class IndexBuffer;
class Shader;
class VertexBuffer;
class GLTexture2D;
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

	void setViewport(const IntVector2& viewport);

	void setFillMode(FillMode fillMode);
	
	void setBlendMode(bool blendMode);
	void setDepthTest(CompareMode mode);

	void setTexture(unsigned int index, GLTexture2D* texture);

	void setVBO(unsigned int VBO);

	void setVertexBuffer(VertexBuffer* vertexBuffer);
	void setIndexBuffer(IndexBuffer* indexBuffer);

	void setShader(Shader* shader);

	inline IntVector2 getViewport() { return viewport_; }

	inline VertexBuffer* getVertexBuffer() { return vertexBuffer_; }
	inline IndexBuffer* getIndexBuffer() { return indexBuffer_; }

	inline unsigned int getPrimitivesCount() { return numPrimitives_; }
	inline unsigned int getBatchesCount() { return numBatches_; }

private:
	static Graphics* instance_;

	static void getGLPrimitiveType(unsigned int elementCount, PrimitiveTopology topology, unsigned int& primitiveCount, GLenum& glPrimitiveType);

	Window* window_;

	IntVector2 viewport_;

	unsigned int numPrimitives_;
	unsigned int numBatches_;

	FillMode fillMode_;

	bool blendMode_;
	CompareMode depthTestMode_;

	unsigned int activeTexture_;
	GLTexture2D* textures_[32];

	unsigned int boundVAO_;
	unsigned int boundVBO_;

	bool vertexBufferDirty_;
	VertexBuffer* vertexBuffer_;

	IndexBuffer* indexBuffer_;

	unsigned int enabledVertexAttributes_;

	Shader* shader_;

	void init();
	void release();

	void resetState();

	void prepareDraw();

	void createVAO();
	void destroyVAO();
};