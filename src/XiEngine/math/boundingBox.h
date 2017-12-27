#pragma once

#include "../math/matrix4.h"
#include "../math/mathDefs.h"
#include "../math/vector3.h"

class BoundingBox
{
public:
	Vector3 min_;
	Vector3 max_;

	BoundingBox();
	BoundingBox(const Vector3& min, const Vector3& max);
	BoundingBox(float min, float max);

	BoundingBox(const Vector3* vertices, unsigned int numVerices);

	BoundingBox& operator=(const BoundingBox& rhs);

	void define(const Vector3& min, const Vector3& max);
	void define(const Vector3* vertices, unsigned int numVertices);

	void merge(const Vector3& point);
	void merge(const Vector3* vertices, unsigned int numVertices);

	Vector3 center() const;
	Vector3 size() const;

	BoundingBox transformed(const Matrix4& transform) const;

	void clear();
};