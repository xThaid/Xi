#include "vertex.h"

Vertex::Vertex()
{
}

Vertex::Vertex(xim::Vector3 position, xim::Vector3 normal, xim::Vector2 texCoords) :
	position(position),
	normal(normal),
	texCoords(texCoords)
{
}