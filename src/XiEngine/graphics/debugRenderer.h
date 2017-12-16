#pragma once

#include "../precompiled.h"

#include "../graphics/graphicsDefs.h"
#include "../math/ximath.h"

class Camera;
class VertexBuffer;

struct DebugLine
{
	Vector3 start_;
	Vector3 end_;
	Vector3 color_;

	DebugLine()
	{
	}

	DebugLine(const Vector3& start, const Vector3& end, const Vector3& color) :
		start_(start),
		end_(end),
		color_(color)
	{
	}
};

class DebugRenderer
{
public:
	DebugRenderer();
	~DebugRenderer();

	void setView(Camera* camera);

	void addLine(const Vector3& start, const Vector3& end, const Vector3& color);
	void addQuad(const Vector3& center, float width, float height, const Vector3& color);

	void render();

	void handleEndFrame();

private:
	VertexBuffer* vertexBuffer_;

	std::vector<DebugLine> lines_;

	Matrix4 view_;
	Matrix4 projection_;
};