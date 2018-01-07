#pragma once

#include "../precompiled.h"

#include "../graphics/graphicsDefs.h"
#include "../math/ximath.h"

class Camera;
class Graphics;
class Shader;
class VertexBuffer;

struct DebugLine
{
	Vector3 start;
	Vector3 end;
	unsigned int color;

	DebugLine()
	{
	}

	DebugLine(const Vector3& start, const Vector3& end, unsigned int color) :
		start(start),
		end(end),
		color(color)
	{
	}
};

struct DebugTriangle
{
	Vector3 v1;
	Vector3 v2;
	Vector3 v3;
	unsigned int color;

	DebugTriangle()
	{
	}

	DebugTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, unsigned int color) :
		v1(v1),
		v2(v2),
		v3(v3),
		color(color)
	{
	}
};

class DebugRenderer
{
public:
	DebugRenderer(Graphics* graphics);
	~DebugRenderer();

	void setView(Camera* camera);

	void addLine(const Vector3& start, const Vector3& end, unsigned int color);
	void addLine(const Vector3& start, const Vector3& end, const Color& color);

	void addTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, unsigned int color);
	void addTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Color& color);

	void addPolygon(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, unsigned int color);
	void addPolygon(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, const Color& color);

	void addQuad(const Vector3& center, float width, float height, const Color& color);

	void addBoundingBox(const BoundingBox& box, const Matrix3x4& transform, const Color& color, bool solid = false);
	void addBoundingBox(const BoundingBox& box, const Color& color, bool solid = false);

	void addFrustum(const Frustum& frustum, const Color& color);

	void render();

	void handleEndFrame();

private:
	Graphics* graphics_;

	Shader* debugShader_;

	VertexBuffer* vertexBuffer_;

	std::vector<DebugLine> lines_;
	std::vector<DebugTriangle> triangles_;

	Matrix3x4 view_;
	Matrix4 projection_;
};