#include "frustum.h"

Frustum::Frustum() :
	transform_(Matrix4())
{
}

Frustum& Frustum::operator=(const Frustum& rhs)
{
	nearClip_ = rhs.nearClip_;
	farClip_ = rhs.farClip_;
	transform_ = rhs.transform_;

	updateVerticesAndPlanes();

	return *this;
}

void Frustum::define(const Vector3& nearClip, const Vector3& farClip)
{
	nearClip_ = nearClip;
	farClip_ = farClip;

	updateVerticesAndPlanes();
}

void Frustum::define(float fov, float aspectRatio, float zoom, float nearZ, float farZ)
{
	nearZ = std::max(nearZ, 0.0f);
	farZ = std::max(farZ, nearZ);
	float halfViewSize = tanf(degToRad(fov) / 2.0f) / zoom;
	
	nearClip_ = Vector3();
	farClip_ = Vector3();

	nearClip_.z_ = nearZ;
	nearClip_.y_ = nearClip_.z_ * halfViewSize;
	nearClip_.x_ = nearClip_.y_ * aspectRatio;
	farClip_.z_ = farZ;
	farClip_.y_ = farClip_.z_ * halfViewSize;
	farClip_.x_ = farClip_.y_ * aspectRatio;

	updateVerticesAndPlanes();
}

void Frustum::defineOrtho(float orthoSize, float aspectRatio, float zoom, float nearZ, float farZ)
{
	nearZ = std::max(nearZ, 0.0f);
	farZ = std::max(farZ, nearZ);
	float halfViewSize = orthoSize * 0.5f / zoom;

	nearClip_ = Vector3();
	farClip_ = Vector3();

	nearClip_.z_ = nearZ;
	farClip_.z_ = farZ;
	farClip_.y_ = nearClip_.y_ = halfViewSize;
	farClip_.x_ = nearClip_.x_ = nearClip_.y_ * aspectRatio;
	
	updateVerticesAndPlanes();
}

void Frustum::setTransform(const Matrix4& transform)
{
	transform_ = transform;

	updateVerticesAndPlanes();
}

Intersection Frustum::intersect(const Vector3& point) const
{
	for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; i++)
	{
		if (planes_[i].distance(point) < 0.0f)
			return OUTSIDE;
	}

	return INSIDE;
}

Intersection Frustum::intersect(const BoundingBox& boundingBox) const
{
	Vector3 center = boundingBox.center();
	Vector3 edge = center - boundingBox.min_;

	for (unsigned i = 0; i < NUM_FRUSTUM_PLANES; ++i)
	{
		const Plane& plane = planes_[i];
		float dist = plane.normal_.dotProduct(center) + plane.d_;
		float absDist = plane.normal_.abs().dotProduct(edge);

		if (dist < -absDist)
			return OUTSIDE;
	}

	return INSIDE;
}

void Frustum::updateVerticesAndPlanes()
{
	vertices_[0] = transform_ * nearClip_;
	vertices_[1] = transform_ * Vector3(nearClip_.x_, -nearClip_.y_, nearClip_.z_);
	vertices_[2] = transform_ * Vector3(-nearClip_.x_, -nearClip_.y_, nearClip_.z_);
	vertices_[3] = transform_ * Vector3(-nearClip_.x_, nearClip_.y_, nearClip_.z_);
	vertices_[4] = transform_ * farClip_;
	vertices_[5] = transform_ * Vector3(farClip_.x_, -farClip_.y_, farClip_.z_);
	vertices_[6] = transform_ * Vector3(-farClip_.x_, -farClip_.y_, farClip_.z_);
	vertices_[7] = transform_ * Vector3(-farClip_.x_, farClip_.y_, farClip_.z_);

	planes_[PLANE_NEAR].define(vertices_[2], vertices_[1], vertices_[0]);
	planes_[PLANE_LEFT].define(vertices_[3], vertices_[7], vertices_[6]);
	planes_[PLANE_RIGHT].define(vertices_[1], vertices_[5], vertices_[4]);
	planes_[PLANE_UP].define(vertices_[0], vertices_[4], vertices_[7]);
	planes_[PLANE_DOWN].define(vertices_[6], vertices_[5], vertices_[1]);
	planes_[PLANE_FAR].define(vertices_[5], vertices_[6], vertices_[7]);
}
