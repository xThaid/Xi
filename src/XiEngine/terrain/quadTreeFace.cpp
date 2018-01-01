#include "quadTreeFace.h"

#include "../graphics/camera.h"
#include "../graphics/indexBuffer.h"
#include "../scene/scene.h"
#include "../scene/sceneNode.h"
#include "../terrain/quadTreeNode.h"
#include "../terrain/quadTreePatch.h"
#include "../terrain/terrain.h"

QuadTreeFace::QuadTreeFace(Terrain* terrain, FaceType faceType, float positionY) :
	terrain_(terrain),
	faceType_(faceType),
	positionY_(positionY)
{
	switch (faceType_)
	{
	case FACE_TOP:
		orientation_ = Matrix3::rotationZMatrix(degToRad(0.0f));
		break;
	case FACE_BOTTOM:
		orientation_ = Matrix3::rotationZMatrix(degToRad(180.0f));
		break;
	case FACE_NEAR:
		orientation_ = Matrix3::rotationXMatrix(degToRad(90.0f));
		break;
	case FACE_LEFT:
		orientation_ = Matrix3::rotationZMatrix(degToRad(90.0f));
		break;
	case FACE_FAR:
		orientation_ = Matrix3::rotationXMatrix(degToRad(-90.0f));
		break;
	case FACE_RIGHT:
		orientation_ = Matrix3::rotationZMatrix(degToRad(-90.0f));
		break;
	}

	rootNode_ = new QuadTreeNode(this, nullptr, NORTH_EAST, Vector2(0.0f, 0.0f), 2.0f);
}

QuadTreeFace::~QuadTreeFace()
{
	delete rootNode_;
}

void QuadTreeFace::update()
{
	rootNode_->update(terrain_->getCullCamera()->position);
}

void QuadTreeFace::getBatches(Camera* cullCamera, std::vector<Batch>& batches)
{
	rootNode_->getBatches(cullCamera, batches);
}

void QuadTreeFace::drawDebugGeometry(DebugRenderer* debug)
{
	rootNode_->drawDebugGeometry(debug);
}

Vector3 QuadTreeFace::getWorldPosition(const Vector2& localPoint)
{
	return orientation_ * Vector3(localPoint.x_, positionY_, localPoint.y_);
}
