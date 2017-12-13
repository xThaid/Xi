#pragma once

#include "../math/ximath.h"

class Vertex
{
public:
	Vector3 position;
	Vector3 normal;
	Vector2 texCoords;

	Vertex();
	Vertex(Vector3 position, Vector3 normal, Vector2 texCoords = Vector2());
};
