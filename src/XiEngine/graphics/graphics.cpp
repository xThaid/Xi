#include "graphics.h"

#include "../graphics/indexBuffer.h"
#include "../graphics/shader.h"
#include "../graphics/vertexBuffer.h"
#include "../graphics/window.h"
#include "../utils/logger.h"

Graphics* Graphics::instance_ = nullptr;

static const unsigned glCmpFunc[] =
{
	GL_ALWAYS,
	GL_EQUAL,
	GL_NOTEQUAL,
	GL_LESS,
	GL_LEQUAL,
	GL_GREATER,
	GL_GEQUAL
};

static const unsigned glElementTypes[] =
{
	GL_INT,
	GL_FLOAT,
	GL_FLOAT,
	GL_FLOAT,
	GL_FLOAT,
	GL_UNSIGNED_BYTE
};

static const unsigned glElementComponents[] =
{
	1,
	1,
	2,
	3,
	4,
	4
};

static const unsigned glFillMode[] =
{
	GL_FILL,
	GL_LINE,
	GL_POINT
};

void Graphics::getGLPrimitiveType(unsigned int elementCount, PrimitiveTopology topology, unsigned int& primitiveCount, GLenum& glPrimitiveType)
{
	switch (topology)
	{
	case PrimitiveTopology::TRIANGLES:
		primitiveCount = elementCount / 3;
		glPrimitiveType = GL_TRIANGLES;
		break;

	case PrimitiveTopology::LINES:
		primitiveCount = elementCount / 2;
		glPrimitiveType = GL_LINES;
		break;

	case PrimitiveTopology::POINTS:
		primitiveCount = elementCount;
		glPrimitiveType = GL_POINTS;
		break;

	case PrimitiveTopology::TRIANGLE_STRIP:
		primitiveCount = elementCount - 2;
		glPrimitiveType = GL_TRIANGLE_STRIP;
		break;

	case PrimitiveTopology::LINE_STRIP:
		primitiveCount = elementCount - 1;
		glPrimitiveType = GL_LINE_STRIP;
		break;

	case PrimitiveTopology::TRIANGLE_FAN:
		primitiveCount = elementCount - 2;
		glPrimitiveType = GL_TRIANGLE_FAN;
		break;
	}
}

Graphics::Graphics(Window* window) :
	window_(window),
	numPrimitives_(0),
	numBatches_(0),
	vertexBufferDirty_(false)
{
	instance_ = this;

	init();

	resetState();
}

Graphics::~Graphics()
{
	release();
}

void Graphics::beginFrame()
{
	numPrimitives_ = 0;
	numBatches_ = 0;

	clear(Vector3(0.1f));
}

void Graphics::endFrame()
{
	window_->swapBuffers();
}

void Graphics::clear(const Vector3& color)
{
	glClearColor(color.x_, color.y_, color.z_, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::draw(PrimitiveTopology topology, unsigned int start, unsigned int vertexCount)
{
	if (!vertexCount || !vertexBuffer_)
		return;

	prepareDraw();

	unsigned int primitiveCount;
	GLenum glPrimitiveType;
	getGLPrimitiveType(vertexCount, topology, primitiveCount, glPrimitiveType);
	
	glDrawArrays(glPrimitiveType, start, vertexCount);

	numPrimitives_ += primitiveCount;
	numBatches_++;
}

void Graphics::drawElement(PrimitiveTopology topology, unsigned int indexStart, unsigned int indexCount)
{
	if (!indexCount || !indexBuffer_)
		return;

	prepareDraw();

	unsigned int primitiveCount;
	GLenum glPrimitiveType;
	getGLPrimitiveType(indexCount, topology, primitiveCount, glPrimitiveType);

	unsigned int indexSize = indexBuffer_->getIndexSize();
	GLenum indexType = indexSize == sizeof(unsigned short) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
	glDrawElements(glPrimitiveType, indexCount, indexType, reinterpret_cast<const GLvoid*>(indexStart * indexSize));

	numPrimitives_ += primitiveCount;
	numBatches_++;
}

void Graphics::setViewport()
{
}

void Graphics::setFillMode(FillMode fillMode)
{
	if (fillMode != fillMode_)
	{
		glPolygonMode(GL_FRONT_AND_BACK, glFillMode[fillMode]);
		fillMode_ = fillMode;
	}
}

void Graphics::setDepthTest(CompareMode mode)
{
	if (mode != depthTestMode_)
	{
		glDepthFunc(glCmpFunc[mode]);
		depthTestMode_ = mode;
	}
}

void Graphics::setVBO(unsigned int VBO)
{
	if (boundVBO_ != VBO)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		boundVBO_ = VBO;
	}
}

void Graphics::setVertexBuffer(VertexBuffer* vertexBuffer)
{
	if (vertexBuffer_ != vertexBuffer)
	{
		vertexBuffer_ = vertexBuffer;
		vertexBufferDirty_ = true;

		if (vertexBuffer == nullptr)
			setVBO(0);
	}
}

void Graphics::setIndexBuffer(IndexBuffer* indexBuffer)
{
	if (indexBuffer_ != indexBuffer)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer ? indexBuffer->getEBO() : 0);

		indexBuffer_ = indexBuffer;
	}
}

void Graphics::setShader(Shader* shader)
{
	if (shader_ != shader)
	{
		shader_ = shader;
		shader_->useShader();
	}
}

void Graphics::init()
{
	if (window_ == nullptr)
		return; 

	if (!glfwInit())
	{
		Logger::error("Failed to initialize GLFW");
		return;
	}

	window_->create();

	glfwMakeContextCurrent(window_->getGLFWWindow());

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Logger::error("Failed to initialize GLAD");
		return;
	}

	Logger::info("Graphics initialization completed");
	Logger::info("OpenGL version: " + std::string((char*)glGetString(GL_VERSION)));

	glViewport(0, 0, window_->getRenderWidth(), window_->getRenderHeight());

	createVAO();
}

void Graphics::release()
{
	destroyVAO();

	glfwTerminate();
}

void Graphics::resetState()
{
	depthTestMode_ = CMP_ALWAYS;
	fillMode_ = FILL_SOLID;

	boundVAO_ = 0;
	boundVBO_ = 0;

	vertexBuffer_ = nullptr;
	indexBuffer_ = nullptr;

	enabledVertexAttributes_ = 0;
	shader_ = nullptr;

	glEnable(GL_DEPTH_TEST);
	setDepthTest(CMP_LESSEQUAL);
}

void Graphics::prepareDraw()
{
	if (shader_ == nullptr)
		return;

	if (vertexBufferDirty_)
	{
		if (vertexBuffer_ != nullptr)
		{
			setVBO(vertexBuffer_->getVBO());

			auto& elements = vertexBuffer_->getElements();
			for (auto& element : elements)
			{
				VertexElement vertexElement = element.first;
				VertexElementDescription vertexElementDesc = VERTEXELEMENTS[vertexElement];
				unsigned int offset = element.second;

				int location = shader_->getVertexAttributeLocation(vertexElement);
				if (location >= 0)
				{
					unsigned int locationMask = 1 << location;

					if (!(enabledVertexAttributes_ & locationMask))
					{
						glEnableVertexAttribArray(location);
						enabledVertexAttributes_ |= locationMask;
					}
				}

				glVertexAttribPointer(location, 
					glElementComponents[vertexElementDesc.type_], glElementTypes[vertexElementDesc.type_], 
					vertexElementDesc.type_ == TYPE_UBYTE4_NORM ? GL_TRUE : GL_FALSE, 
					vertexBuffer_->getVertexSize(), (const void *)offset);
			}
		}

		unsigned int disableVertexAttributes = enabledVertexAttributes_ & (~shader_->getUsedVertexAttributes_());
		unsigned int location = 0;
		while (disableVertexAttributes)
		{
			if (disableVertexAttributes & 1)
			{
				glDisableVertexAttribArray(location);
				enabledVertexAttributes_ &= ~(1 << location);
			}
			++location;
			disableVertexAttributes >>= 1;
		}


		vertexBufferDirty_ = false;
	}
}

void Graphics::createVAO()
{
	if (!boundVAO_)
	{
		glGenVertexArrays(1, &boundVAO_);
		glBindVertexArray(boundVAO_);
	}
}

void Graphics::destroyVAO()
{
	if (boundVAO_)
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &boundVAO_);
		boundVAO_ = 0;
	}
}

