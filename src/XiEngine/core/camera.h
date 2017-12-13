#pragma once

#include "../math/ximath.h"

const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	Camera();
	Camera(Vector3 position, float yaw, float pitch);

	Matrix4 getViewMatrix();

	void processKeyboard(CameraMovement direction, float deltaTime);
	void processMouse(float xDelta, float yDelta);

	void setPosition(Vector3 position);
	void setAngles(float yaw, float pitch);
	void setYaw(float yaw);
	void setPitch(float pitch);

	void setCameraSpeed(float speed);
	void setMouseSensitivity(float sensitivity);

	inline Vector3 getPosition() { return position; }

private:
	float yaw;
	float pitch;

	float cameraSpeed;
	float mouseSensitivity;

	Vector3 position;

	Vector3 front;
	Vector3 right;
	Vector3 up;

	void updateVectors();
};