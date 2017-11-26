#pragma once

#include "../math/ximath.h"

#include <vector>

class Transform
{
public:
	xim::Vector3 position;
	xim::Vector3 scale;
	float pitch, yaw;

	Transform();
	void addChild(Transform* transform);

	void applyTranformToChildren();

	xim::Matrix4 getModelMatrix() { return lastModelMatrix; }

private:
	Transform* parent;
	std::vector<Transform*> children;

	xim::Matrix4 lastModelMatrix;

	void calculateModelMatrix();
};