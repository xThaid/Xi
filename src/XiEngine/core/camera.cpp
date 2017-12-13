#include "camera.h"

#include "../utils/logger.h"

Camera::Camera() : 
	Camera(Vector3(), -90.0f, 0.0f)
{
}

Camera::Camera(Vector3 position, float yaw, float pitch)
{
	this->position = position;
	this->yaw = yaw;
	this->pitch = pitch;

	cameraSpeed = SPEED;
	mouseSensitivity = SENSITIVITY;

	up = Vector3(0.0f, 1.0f, 0.0f);

	updateVectors();
}

Matrix4 Camera::getViewMatrix()
{
	return Matrix4::lookAt(position, position + front, up);
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

void Camera::setPosition(Vector3 position)
{
	this->position = position;
}

void Camera::setAngles(float yaw, float pitch)
{
	this->yaw = yaw;
	this->pitch = pitch;
	updateVectors();
}

void Camera::setYaw(float yaw)
{
	this->yaw = yaw;
	updateVectors();
}

void Camera::setPitch(float pitch)
{
	this->pitch = pitch;
	updateVectors();
}

void Camera::setCameraSpeed(float speed)
{
	cameraSpeed = speed;
}

void Camera::setMouseSensitivity(float sensitivity)
{
	mouseSensitivity = sensitivity;
}

void Camera::updateVectors()
{
	front.data[0] = cosf(degToRad(yaw)) * cosf(degToRad(pitch));
	front.data[1] = sinf(degToRad(pitch));
	front.data[2] = sinf(degToRad(yaw)) * cosf(degToRad(pitch));
	front.normalize();

	right = front.crossProduct(up).normalized();
}
