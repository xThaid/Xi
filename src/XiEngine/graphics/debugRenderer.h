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
	unsigned int color_;

	DebugLine()
	{
	}

	DebugLine(const Vector3& start, const Vector3& end, unsigned int color) :
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

	void addLine(const Vector3& start, const Vector3& end, unsigned int color);
	void addLine(const Vector3& start, const Vector3& end, const Color& color);

	void addQuad(const Vector3& center, float width, float height, const Color& color);

	void render();

	void handleEndFrame();

private:
	VertexBuffer* vertexBuffer_;

	std::vector<DebugLine> lines_;

	Matrix4 view_;
	Matrix4 projection_;
};