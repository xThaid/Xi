#include "transform.h"

Transform::Transform()
{
	pitch = 0.0f;
	yaw = 0.0f;
	scale = xim::Vector3(1.0f, 1.0f, 1.0f);
}

void Transform::addChild(Transform* transform)
{
	transform->parent = this;
	children.push_back(transform);
}

void Transform::applyTranformToChildren()
{
	calculateModelMatrix();

	for (Transform* transform : children)
	{
		transform->applyTranformToChildren();
	}
}

void Transform::calculateModelMatrix()
{
	xim::Matrix4 model = xim::Matrix4();
	model.translate(position);
	model.rotateY(yaw);
	model.rotateX(pitch);
	model.scale(scale);

	if (parent != nullptr)
		lastModelMatrix = parent->getModelMatrix() * model;
	else
		lastModelMatrix = model;
}