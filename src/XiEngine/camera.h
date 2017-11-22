#pragma once

#include "math\ximath.h"

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
	Camera(xim::Vector3 position, float yaw, float pitch);

	xim::Matrix4 getViewMatrix();

	void processKeyboard(CameraMovement direction, float deltaTime);
	void processMouse(float xDelta, float yDelta);

	void setPosition(xim::Vector3 position);
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

	xim::Vector3 position;

	xim::Vector3 front;
	xim::Vector3 right;
	xim::Vector3 up;

	void updateVectors();
};