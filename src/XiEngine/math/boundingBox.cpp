#include "boundingBox.h"

BoundingBox::BoundingBox() :
	min_(Vector3(M_INFINITY)),
	max_(Vector3(-M_INFINITY))
{
}

BoundingBox::BoundingBox(const Vector3& min, const Vector3& max) :
	min_(min),
	max_(max)
{
}

BoundingBox::BoundingBox(float min, float max) :
	min_(Vector3(min)),
	max_(Vector3(max))
{
}

BoundingBox::BoundingBox(const Vector3* vertices, unsigned int numVerices)
{
	define(vertices, numVerices);
}

BoundingBox& BoundingBox::operator=(const BoundingBox& rhs)
{
	min_ = rhs.min_;
	max_ = rhs.max_;

	return *this;
}

void BoundingBox::define(const Vector3& min, const Vector3& max)
{
	min_ = min;
	max_ = max;
}

void BoundingBox::define(const Vector3* vertices, unsigned int numVertices)
{
	clear();
	merge(vertices, numVertices);
}

void BoundingBox::merge(const Vector3& point)
{
	if (point.x_ < min_.x_)
		min_.x_ = point.x_;
	if (point.y_ < min_.y_)
		min_.y_ = point.y_;
	if (point.z_ < min_.z_)
		min_.z_ = point.z_;
	if (point.x_ > max_.x_)
		max_.x_ = point.x_;
	if (point.y_ > max_.y_)
		max_.y_ = point.y_;
	if (point.z_ > max_.z_)
		max_.z_ = point.z_;
}

void BoundingBox::merge(const Vector3* vertices, unsigned int numVertices)
{
	for (unsigned int i = 0; i < numVertices; i++)
		merge(vertices[i]);
}

void BoundingBox::clear()
{
	min_ = Vector3(M_INFINITY);
	max_ = Vector3(-M_INFINITY);
}
