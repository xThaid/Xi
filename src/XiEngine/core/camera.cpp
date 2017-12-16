#include "camera.h"

#include "../graphics/debugRenderer.h"

Matrix4 lookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	Vector3 zAxis = (eye - target).normalized();
	Vector3 xAxis = up.crossProduct(zAxis).normalized();
	Vector3 yAxis = zAxis.crossProduct(xAxis);

	Matrix4 res;
	res.data[0] = xAxis.x_;
	res.data[4] = xAxis.y_;
	res.data[8] = xAxis.z_;

	res.data[1] = yAxis.x_;
	res.data[5] = yAxis.y_;
	res.data[9] = yAxis.z_;

	res.data[2] = zAxis.x_;
	res.data[6] = zAxis.y_;
	res.data[10] = zAxis.z_;

	res.data[12] = -eye.dotProduct(xAxis);
	res.data[13] = -eye.dotProduct(yAxis);
	res.data[14] = -eye.dotProduct(zAxis);
	res.data[15] = 1.0f;

	return res;
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
	float velocity = cameraSpeed * deltaTime;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
}

void Camera::processMouse(float xDelta, float yDelta)
{
	xDelta *= mouseSensitivity;
	yDelta *= mouseSensitivity;

	yaw += xDelta;
	pitch += yDelta;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	updateVectors();
}

void Camera::updateVectors()
{
	front.x_ = cosf(degToRad(yaw)) * cosf(degToRad(pitch));
	front.y_ = sinf(degToRad(pitch));
	front.z_ = sinf(degToRad(yaw)) * cosf(degToRad(pitch));
	front.normalize();

	right = front.crossProduct(up).normalized();
}

Camera::Camera() :
	viewDirty_(true),
	projectionDirty_(true),
	orthographic_(false),
	nearClip_(DEFAULT_NEARCLIP),
	farClip_(DEFAULT_FARCLIP),
	fov_(DEFAULT_CAMERA_FOV),
	orthoSize_(DEFAULT_ORTHOSIZE),
	aspectRatio_(1.0f),
	zoom_(1.0f),
	fillMode_(FILL_SOLID)
{
}

Camera::~Camera()
{
}

void Camera::drawDebugGeometry(DebugRenderer* debug)
{
}

void Camera::setNearClip(float nearClip)
{
	nearClip_ = std::max(nearClip, MIN_NEARCLIP);
	projectionDirty_ = true;
}

void Camera::setFarClip(float farClip)
{
	farClip_ = std::max(farClip, MIN_NEARCLIP);
	projectionDirty_ = true;
}

void Camera::setFov(float fov)
{
	fov_ = clamp(fov, 0.0f, MAX_FOV);
	projectionDirty_ = true;
}

void Camera::setOrthoSize(float orthoSize)
{
	orthoSize_ = orthoSize;
	aspectRatio_ = 1.0f;
	projectionDirty_ = true;
}

void Camera::setOrthoSize(const Vector2& orthoSize)
{
	orthoSize_ = orthoSize.y_;
	aspectRatio_ = orthoSize.x_ / orthoSize.y_;
	projectionDirty_ = true;
}

void Camera::setAspectRatio(float aspectRatio)
{
	aspectRatio_ = aspectRatio;
	projectionDirty_ = true;
}

void Camera::setZoom(float zoom)
{
	zoom_ = zoom;
	projectionDirty_ = true;
}

void Camera::setFillMod(FillMode mode)
{
	fillMode_ = mode;
}

void Camera::setOrthographic(bool enable)
{
	orthographic_ = enable;
	projectionDirty_ = true;
}

Matrix4 Camera::getProjection()
{
	if (projectionDirty_)
		updateProjection();

	return projection_;
}

Matrix4 Camera::getView()
{
	if (viewDirty_)
	{
		view_ = lookAt(position, position + front, up);
	}

	return view_;
}

void Camera::updateProjection()
{
	projection_ = Matrix4();

	if (!orthographic_)
	{
		float h = 1.0f / tanf(degToRad(fov_) * 0.5f) * zoom_;
		float w = h / aspectRatio_;
		float d = farClip_ - nearClip_;

		projection_.data[0] = w;
		projection_.data[5] = h;
		projection_.data[10] = -(farClip_ + nearClip_) / d;
		projection_.data[11] = -1.0f;
		projection_.data[14] = -2.0f * farClip_ * nearClip_ / d;
		projection_.data[15] = 0.0f;
	}
	else
	{
		//TODO
		/*
		m.data[0] = 2.0f / (right - left);
		m.data[5] = 2.0f / (top - bottom);
		m.data[10] = -2.0f / (zfar - znear);
		m.data[12] = -((right + left) / (right - left));
		m.data[13] = -((top + bottom) / (top - bottom));
		m.data[14] = -((zfar + znear) / (zfar - znear));
		m.data[15] = 1.0f;
		*/
	}

	projectionDirty_ = false;
}
