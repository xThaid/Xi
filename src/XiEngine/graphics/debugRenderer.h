#pragma once

#include "../precompiled.h"

#include "../math/ximath.h"

class Camera;

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

	void render();

	void handleEndFrame();

private:
	std::vector<DebugLine> lines_;

	Matrix4 view_;
	Matrix4 projection_;
};