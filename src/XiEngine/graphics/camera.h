#pragma once

#include "../graphics/graphicsDefs.h"
#include "../math/ximath.h"

static const float DEFAULT_NEARCLIP = 0.1f;
static const float DEFAULT_FARCLIP = 1000.0f;
static const float DEFAULT_CAMERA_FOV = 45.0f;
static const float DEFAULT_ORTHOSIZE = 20.0f;

static const float MIN_NEARCLIP = 0.01f;
static const float MAX_FOV = 160.0f;

class DebugRenderer;

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	void processKeyboard(CameraMovement direction, float deltaTime);
	void processMouse(float xDelta, float yDelta);

	float yaw = 0.0f;
	float pitch = 0.0f;

	float cameraSpeed = 2.5f;
	float mouseSensitivity = 0.1f;

	Vector3 position;

	Vector3 front;
	Vector3 right;
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	void updateVectors();

public:
	Camera();
	~Camera();

	void drawDebugGeometry(DebugRenderer* debug);

	void setNearClip(float nearClip);
	void setFarClip(float farClip);
	void setFov(float fov);
	void setOrthoSize(float orthoSize);
	void setOrthoSize(const Vector2& orthoSize);
	void setAspectRatio(float aspectRatio);
	void setZoom(float zoom);
	void setFillMod(FillMode mode);

	void setOrthographic(bool enable);

	inline float getFarClip() const { return farClip_; }
	inline float getNearClip() const { return nearClip_; }
	inline float getFov() const { return fov_; }
	inline float getOrthoSize() const { return orthoSize_; }
	inline float getAspectRatio() const { return aspectRatio_; }
	inline float getZoom() const { return zoom_; }
	inline FillMode getFillMode() const { return fillMode_; }

	inline bool isOrthographic() const { return orthographic_; }

	const Frustum& getFrustum();

	Matrix4 getProjection();
	Matrix4 getView();

private:
	Frustum frustum_;

	Matrix4 view_;
	Matrix4 projection_;

	bool frustumDirty_;
	bool viewDirty_;
	bool projectionDirty_;

	bool orthographic_;

	float nearClip_;
	float farClip_;
	float fov_;
	float orthoSize_;
	float aspectRatio_;
	float zoom_;

	FillMode fillMode_;

	void updateFrustum();
	void updateProjection();
};