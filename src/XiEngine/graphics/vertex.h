#pragma once

#include "../math/ximath.h"

class Vertex
{
public:
	xim::Vector3 position;
	xim::Vector3 normal;
	xim::Vector2 texCoords;

	Vertex();
	Vertex(xim::Vector3 position, xim::Vector3 normal, xim::Vector2 texCoords = xim::Vector2());
};
