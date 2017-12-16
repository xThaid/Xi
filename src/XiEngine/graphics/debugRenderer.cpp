#include "debugRenderer.h"

#include "../core/camera.h"
#include "../graphics/graphics.h"
#include "../graphics/shader.h"
#include "../graphics/vertexBuffer.h"
#include "../resource/resourceManager.h"
#include "../utils/logger.h"

DebugRenderer::DebugRenderer()
{
	vertexBuffer_ = new VertexBuffer(MASK_POSITION | MASK_COLOR);
}

DebugRenderer::~DebugRenderer()
{
	delete vertexBuffer_;
}

void DebugRenderer::setView(Camera* camera)
{
	view_ = camera->getView();
	projection_ = camera->getProjection();
}

void DebugRenderer::addLine(const Vector3& start, const Vector3& end, unsigned int color)
{
	DebugLine line(start, end, color);
	lines_.push_back(line);
}

void DebugRenderer::addLine(const Vector3& start, const Vector3& end, const Color& color)
{
	addLine(start, end, color.toUInt());
}

void DebugRenderer::addQuad(const Vector3& center, float width, float height, const Color& color)
{
	Vector3 v0(center.x_ - width / 2, center.y_, center.z_ - height / 2);
	Vector3 v1(center.x_ + width / 2, center.y_, center.z_ - height / 2);
	Vector3 v2(center.x_ + width / 2, center.y_, center.z_ + height / 2);
	Vector3 v3(center.x_ - width / 2, center.y_, center.z_ + height / 2);

	addLine(v0, v1, color);
	addLine(v1, v2, color);
	addLine(v2, v3, color);
	addLine(v3, v0, color);
}

void DebugRenderer::render()
{
	Graphics* graphics = Graphics::getInstance();
	
	Shader* shader = ResourceManager::getInstance()->getResource<Shader>("debug shader");

	unsigned int numVertices = lines_.size() * 2;

	vertexBuffer_->create(numVertices);

	float* data = (float*) new unsigned char[numVertices * vertexBuffer_->getVertexSize()];

	unsigned int dest = 0;
	for (unsigned int i = 0; i < lines_.size(); i++)
	{
		DebugLine& line_ = lines_[i];
		data[dest + 0] = line_.start_.x_;
		data[dest + 1] = line_.start_.y_;
		data[dest + 2] = line_.start_.z_;
		
		((unsigned int&)data[dest + 3]) = line_.color_;
		
		data[dest + 4] = line_.end_.x_;
		data[dest + 5] = line_.end_.y_;
		data[dest + 6] = line_.end_.z_;

		((unsigned int&)data[dest + 7]) = line_.color_;
	
		dest += 8;
	}

	vertexBuffer_->setData(data);
	delete data;

	shader->useShader();
	shader->setMatrix4("model", Matrix4());
	shader->setMatrix4("view", view_);
	shader->setMatrix4("projection", projection_);
	
	graphics->setShader(shader);
	graphics->setVertexBuffer(vertexBuffer_);

	graphics->draw(PrimitiveTopology::LINES, lines_.size() * 2);
}

void DebugRenderer::handleEndFrame()
{
	lines_.clear();
}
