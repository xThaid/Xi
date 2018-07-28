#include "sphericalTerrain.h"

#include <FastNoise.h>

#include "../terrain/quadTreeFace.h"
#include "../terrain/terrainGenerator.h"

SphericalTerrain::SphericalTerrain(float radius) :
	Terrain(),
	radius_(radius)
{
	faces_.push_back(new QuadTreeFace(this, FACE_TOP, 1.0f));
	faces_.push_back(new QuadTreeFace(this, FACE_BOTTOM, 1.0f));
	faces_.push_back(new QuadTreeFace(this, FACE_NEAR, 1.0f));
	faces_.push_back(new QuadTreeFace(this, FACE_LEFT, 1.0f));
	faces_.push_back(new QuadTreeFace(this, FACE_FAR, 1.0f));
	faces_.push_back(new QuadTreeFace(this, FACE_RIGHT, 1.0f));

	connectFaces();
}

SphericalTerrain::~SphericalTerrain()
{
	delete generator_;
	generator_ = nullptr;
}

float SphericalTerrain::getTerrainHeight(const Vector3& point) const
{	
	FastNoise noise;
	noise.SetFractalOctaves(8);

	noise.SetFrequency(1.0f);
	float height = noise.GetSimplexFractal(point.x_, point.y_, point.z_);

	return radius_ + height * 5.0f;
}

Vector3 SphericalTerrain::projectOnSurface(const Vector3& point) const
{
	return cubeToSphere(point) * getTerrainHeight(point);
}

void SphericalTerrain::connectFaces()
{
	faces_[FACE_NEAR]->connect(NORTH, faces_[FACE_TOP]);
	faces_[FACE_NEAR]->connect(SOUTH, faces_[FACE_BOTTOM]);
	faces_[FACE_NEAR]->connect(WEST, faces_[FACE_LEFT]);

	faces_[FACE_LEFT]->connect(EAST, faces_[FACE_TOP]);
	faces_[FACE_LEFT]->connect(WEST, faces_[FACE_BOTTOM]);
	faces_[FACE_LEFT]->connect(NORTH, faces_[FACE_FAR]);

	faces_[FACE_FAR]->connect(SOUTH, faces_[FACE_TOP]);
	faces_[FACE_FAR]->connect(NORTH, faces_[FACE_BOTTOM]);
	faces_[FACE_FAR]->connect(EAST, faces_[FACE_RIGHT]);

	faces_[FACE_RIGHT]->connect(WEST, faces_[FACE_TOP]);
	faces_[FACE_RIGHT]->connect(EAST, faces_[FACE_BOTTOM]);
	faces_[FACE_RIGHT]->connect(SOUTH, faces_[FACE_NEAR]);
}

Vector3 SphericalTerrain::cubeToSphere(const Vector3& point) const
{
	const float x2 = point.x_ * point.x_;
	const float y2 = point.y_ * point.y_;
	const float z2 = point.z_ * point.z_;
	return Vector3(point.x_ * sqrt(1.0f - (y2 + z2) * 0.5f + y2 * z2 * 0.3333333333333f),
		point.y_ * sqrt(1.0f - (z2 + x2) * 0.5f + z2 * x2 * 0.333333333333f),
		point.z_ * sqrt(1.0f - (x2 + y2) * 0.5f + x2 * y2 * 0.333333333333f));
}
