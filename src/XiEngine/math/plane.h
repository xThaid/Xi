#pragma once

#include "../math/vector3.h"

class Plane
{
public:
	static const Plane UP;

	Vector3 normal_;
	float d_;

	Plane();
	Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2);
	Plane(const Vector3& normal, const Vector3& point);

	void define(const Vector3& v0, const Vector3& v1, const Vector3& v2);
	void define(const Vector3& normal, const Vector3& point);

	float distance(const Vector3& point) const;
};