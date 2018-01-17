#pragma once

#include "../precompiled.h"

#include "../terrain/quadTreeNode.h"
#include "../math/ximath.h"

struct Batch;

class Camera;
class DebugRenderer;
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

	void cullNodesToRender(Camera* cullCamera, std::vector<QuadTreeNode*>& nodes);

	void drawDebugGeometry(DebugRenderer* debug);

	void connect(Side side, QuadTreeFace* face);

	Vector3 getWorldPosition(const Vector2& localPoint);

	inline FaceType getFaceType() { return faceType_; }

	inline Terrain* getTerrain() { return terrain_; }

private:
	Terrain* terrain_;

	FaceType faceType_;

	float positionY_;
	Matrix3 orientation_;

	QuadTreeNode* rootNode_;
};