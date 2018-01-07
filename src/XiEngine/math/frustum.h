#pragma once

#include "../math/boundingBox.h"
#include "../math/mathDefs.h"
#include "../math/matrix4.h"
#include "../math/plane.h"
#include "../math/vector3.h"

enum FrustumPlane
{
	PLANE_NEAR = 0,
	PLANE_LEFT,
	PLANE_RIGHT,
	PLANE_UP,
	PLANE_DOWN,
	PLANE_FAR,
};

static const unsigned NUM_FRUSTUM_PLANES = 6;
static const unsigned NUM_FRUSTUM_VERTICES = 8;

class Frustum
{
public:
	Plane planes_[NUM_FRUSTUM_PLANES];
	Vector3 vertices_[NUM_FRUSTUM_VERTICES];

	Frustum();

	Frustum& operator=(const Frustum& rhs);

	void define(const Vector3& nearClip, const Vector3& farClip);
	void define(float fov, float aspectRatio, float zoom, float nearZ, float farZ);
	void defineOrtho(float orthoSize, float aspectRatio, float zoom, float nearZ, float farZ);
	
	void setTransform(const Matrix3x4& transform);

	Intersection intersect(const Vector3& point) const;
	Intersection intersect(const BoundingBox& boundingBox) const;

private:
	Vector3 nearClip_;
	Vector3 farClip_;

	Matrix3x4 transform_;

	void updateVerticesAndPlanes();
};