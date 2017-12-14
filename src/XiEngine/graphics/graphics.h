#pragma once

#include "../math/ximath.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	void beginFrame();
	void endFrame();

	void clear(const Vector3& color);

	void draw();

	void setViewport();
};