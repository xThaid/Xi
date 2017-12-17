#include "plane.h"

const Plane Plane::UP(Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0, 0.0, 0.0));

Plane::Plane() :
	normal_(Vector3()),
	d_(0.0f)
{
}

Plane::Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2)
{
	define(v0, v1, v2);
}

Plane::Plane(const Vector3& normal, const Vector3& point)
{
	define(normal, point);
}

void Plane::define(const Vector3& v0, const Vector3& v1, const Vector3& v2)
{
	Vector3 dist1 = v1 - v0;
	Vector3 dist2 = v2 - v0;

	Vector3 normal = dist1.crossProduct(dist2);
	define(normal, v0);
}

void Plane::define(const Vector3& normal, const Vector3& point)
{
	normal_ = normal.normalized();
	d_ = -normal_.dotProduct(point);
}

float Plane::distance(const Vector3& point) const
{
	return normal_.dotProduct(point) + d_;
}

