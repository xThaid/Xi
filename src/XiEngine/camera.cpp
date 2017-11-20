#include "camera.h"

Camera::Camera(ximath::Vector3 position = ximath::Vector3(0.0f, 0.0f, 0.0f), float yaw = 0.0f, float pitch = 0.0f)
{
	this->position = position;
	this->yaw = yaw;
	this->pitch = pitch;

	cameraSpeed = SPEED;
	mouseSensitivity = SENSITIVITY;

	up = ximath::Vector3(0.0f, 1.0f, 0.0f);

	updateVectors();
}

ximath::Matrix4 Camera::getViewMatrix()
{
	return ximath::lookAt(position, position + front, up);
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

void Camera::setPosition(ximath::Vector3 position)
{
	this->position = position;
}

void Camera::setAngles(float yaw, float pitch)
{
	this->yaw = yaw;
	this->pitch = pitch;
}

void Camera::setYaw(float yaw)
{
	this->yaw = yaw;
}

void Camera::setPitch(float pitch)
{
	this->pitch = pitch;
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
	front.x = (float) (cos(ximath::radians(yaw)) * cos(ximath::radians(pitch)));
	front.y = (float) sin(ximath::radians(pitch));
	front.z = (float) (sin(ximath::radians(yaw)) * cos(ximath::radians(pitch)));
	front.normalize();

	right = ximath::cross(front, up).normalized();
}
