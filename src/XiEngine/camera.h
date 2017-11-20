#pragma once

#include "math\ximath.h"

const int SPEED = 2.5f;
const int SENSITIVITY = 0.1;

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	Camera(ximath::Vector3 position, float yaw, float pitch);

	ximath::Matrix4 getViewMatrix();

	void processKeyboard(CameraMovement direction, float deltaTime);
	void processMouse(float xDelta, float yDelta);

	void setPosition(ximath::Vector3 position);
	void setAngles(float yaw, float pitch);
	void setYaw(float yaw);
	void setPitch(float pitch);

	void setCameraSpeed(float speed);
	void setMouseSensitivity(float sensitivity);

private:
	float yaw;
	float pitch;

	float cameraSpeed;
	float mouseSensitivity;

	ximath::Vector3 position;

	ximath::Vector3 front;
	ximath::Vector3 right;
	ximath::Vector3 up;

	void updateVectors();
};