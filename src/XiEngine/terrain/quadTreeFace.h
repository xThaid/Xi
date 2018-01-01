#pragma once

#include "../precompiled.h"

#include "../math/ximath.h"

struct Batch;

class Camera;
class DebugRenderer;
class QuadTreeNode;
class Terrain;

enum FaceType
{
	FACE_TOP = 0,
	FACE_BOTTOM,
	FACE_NEAR,
	FACE_LEFT,
	FACE_FAR,
	FACE_RIGHT,
};

class QuadTreeFace
{
public:
	QuadTreeFace(Terrain* terrain, FaceType faceType = FACE_TOP, float positionY = 0.0f);
	~QuadTreeFace();

	void update();

	virtual void getBatches(Camera* cullCamera, std::vector<Batch>& batches);

	void drawDebugGeometry(DebugRenderer* debug);

	Vector3 getWorldPosition(const Vector2& localPoint);

	inline Terrain* getTerrain() { return terrain_; }

private:
	Terrain* terrain_;

	FaceType faceType_;

	float positionY_;
	Matrix3 orientation_;

	QuadTreeNode* rootNode_;
};