#pragma once

#include "../graphics/mesh.h"

namespace Primitives
{
	MeshGeometry* quad();
	MeshGeometry* quad(float width, float height);

	MeshGeometry* cube();

	MeshGeometry* plane(unsigned int xSegments, unsigned int ySegments);

	MeshGeometry* circle(unsigned int edgeSegments, unsigned int ringSegments);

	MeshGeometry* sphere(unsigned int xSegments, unsigned int ySegments);

	MeshGeometry* torus(float r1, float r2, unsigned int numSteps1, unsigned int numSteps2);
}