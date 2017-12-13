#include "vertex.h"

Vertex::Vertex()
{
}

Vertex::Vertex(Vector3 position, Vector3 normal, Vector2 texCoords) :
	position(position),
	normal(normal),
	texCoords(texCoords)
{
}