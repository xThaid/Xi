#include "debugRenderer.h"

#include "../graphics/camera.h"
#include "../graphics/graphics.h"
#include "../graphics/shader.h"
#include "../graphics/vertexBuffer.h"
#include "../resource/resourceManager.h"
#include "../utils/logger.h"

DebugRenderer::DebugRenderer(Graphics* graphics) :
	graphics_(graphics),
	debugShader_(ResourceManager::getInstance()->getResource<Shader>("debug shader"))
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

void DebugRenderer::addTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, unsigned int color)
{
	DebugTriangle triangle(v1, v2, v3, color);
	triangles_.push_back(triangle);
}

void DebugRenderer::addTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Color& color)
{
	addTriangle(v1, v2, v3, color.toUInt());
}

void DebugRenderer::addPolygon(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, unsigned int color)
{
	addTriangle(v1, v2, v3, color);
	addTriangle(v3, v4, v1, color);
}

void DebugRenderer::addPolygon(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, const Color& color)
{
	addTriangle(v1, v2, v4, color);
	addTriangle(v3, v4, v1, color);
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

void DebugRenderer::addBoundingBox(const BoundingBox& box, const Matrix3x4& transform, const Color& color, bool solid)
{
	const Vector3& min = box.min_;
	const Vector3& max = box.max_;

	Vector3 v0(transform * min);
	Vector3 v1(transform * Vector3(max.x_, min.y_, min.z_));
	Vector3 v2(transform * Vector3(max.x_, max.y_, min.z_));
	Vector3 v3(transform * Vector3(min.x_, max.y_, min.z_));
	Vector3 v4(transform * Vector3(min.x_, min.y_, max.z_));
	Vector3 v5(transform * Vector3(max.x_, min.y_, max.z_));
	Vector3 v6(transform * Vector3(min.x_, max.y_, max.z_));
	Vector3 v7(transform * max);

	unsigned int uintColor = color.toUInt();

	if (!solid)
	{
		addLine(v0, v1, uintColor);
		addLine(v1, v2, uintColor);
		addLine(v2, v3, uintColor);
		addLine(v3, v0, uintColor);
		addLine(v4, v5, uintColor);
		addLine(v5, v7, uintColor);
		addLine(v7, v6, uintColor);
		addLine(v6, v4, uintColor);
		addLine(v0, v4, uintColor);
		addLine(v1, v5, uintColor);
		addLine(v2, v7, uintColor);
		addLine(v3, v6, uintColor);
	}
	else
	{
		addPolygon(v0, v1, v2, v3, uintColor);
		addPolygon(v4, v5, v7, v6, uintColor);
		addPolygon(v0, v4, v6, v3, uintColor);
		addPolygon(v1, v5, v7, v2, uintColor);
		addPolygon(v3, v2, v7, v6, uintColor);
		addPolygon(v0, v1, v5, v4, uintColor);
	}
}

void DebugRenderer::addBoundingBox(const BoundingBox& box, const Color& color, bool solid)
{
	addBoundingBox(box, Matrix3x4(), color, solid);
}

void DebugRenderer::addFrustum(const Frustum& frustum, const Color& color)
{
	const Vector3* vertices = frustum.vertices_;
	unsigned int uintColor = color.toUInt();

	addLine(vertices[0], vertices[1], uintColor);
	addLine(vertices[1], vertices[2], uintColor);
	addLine(vertices[2], vertices[3], uintColor);
	addLine(vertices[3], vertices[0], uintColor);
	addLine(vertices[4], vertices[5], uintColor);
	addLine(vertices[5], vertices[6], uintColor);
	addLine(vertices[6], vertices[7], uintColor);
	addLine(vertices[7], vertices[4], uintColor);
	addLine(vertices[0], vertices[4], uintColor);
	addLine(vertices[1], vertices[5], uintColor);
	addLine(vertices[2], vertices[6], uintColor);
	addLine(vertices[3], vertices[7], uintColor);
}

void DebugRenderer::render()
{
	unsigned int numVertices = lines_.size() * 2 + triangles_.size() * 3;

	vertexBuffer_->create(numVertices);

	float* data = (float*) new unsigned char[numVertices * vertexBuffer_->getVertexSize()];

	unsigned int dest = 0;
	for (unsigned int i = 0; i < lines_.size(); i++)
	{
		DebugLine& line = lines_[i];
		data[dest + 0] = line.start.x_;
		data[dest + 1] = line.start.y_;
		data[dest + 2] = line.start.z_;
		
		((unsigned int&)data[dest + 3]) = line.color;
		
		data[dest + 4] = line.end.x_;
		data[dest + 5] = line.end.y_;
		data[dest + 6] = line.end.z_;

		((unsigned int&)data[dest + 7]) = line.color;
	
		dest += 8;
	}

	for (unsigned int i = 0; i < triangles_.size(); i++)
	{
		DebugTriangle triangle = triangles_[i];
		data[dest + 0] = triangle.v1.x_;
		data[dest + 1] = triangle.v1.y_;
		data[dest + 2] = triangle.v1.z_;

		((unsigned int&)data[dest + 3]) = triangle.color;

		data[dest + 4] = triangle.v2.x_;
		data[dest + 5] = triangle.v2.y_;
		data[dest + 6] = triangle.v2.z_;

		((unsigned int&)data[dest + 7]) = triangle.color;

		data[dest + 8] = triangle.v3.x_;
		data[dest + 9] = triangle.v3.y_;
		data[dest + 10] = triangle.v3.z_;

		((unsigned int&)data[dest + 11]) = triangle.color;

		dest += 12;
	}

	vertexBuffer_->setData(data);
	delete data;


	graphics_->setShader(debugShader_);

	debugShader_->setMatrix3x4("model", Matrix3x4());
	debugShader_->setMatrix3x4("view", view_);
	debugShader_->setMatrix4("projection", projection_);
	
	graphics_->setVertexBuffer(vertexBuffer_);
	
	graphics_->setDepthTest(CMP_ALWAYS);

	if (lines_.size() > 0)
	{
		graphics_->draw(PrimitiveTopology::LINES, 0, lines_.size() * 2);
	}

	if (triangles_.size() > 0)
	{
		graphics_->draw(PrimitiveTopology::TRIANGLES, lines_.size() * 2, triangles_.size() * 3);
	}

	graphics_->setDepthTest(CMP_LESSEQUAL);
}

void DebugRenderer::handleEndFrame()
{
	lines_.clear();
	triangles_.clear();
}
