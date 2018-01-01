#pragma once

#include "../terrain/terrain.h"

class SphericalTerrain : public Terrain
{
public:
	SphericalTerrain(float radius);
	~SphericalTerrain();

	virtual float getTerrainHeight(const Vector3& point) const override;
	virtual Vector3 projectOnSurface(const Vector3& point) const override;

protected:

private:
	float radius_;

	Vector3 cubeToSphere(const Vector3& point) const;
};