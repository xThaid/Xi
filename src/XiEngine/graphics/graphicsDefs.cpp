#include "graphicsDefs.h"

extern const unsigned ELEMENT_TYPESIZES[] =
{
	sizeof(int),
	sizeof(float),
	2 * sizeof(float),
	3 * sizeof(float),
	4 * sizeof(float)
};

extern const VertexElementDescription VERTEXELEMENTS[] = 
{
	VertexElementDescription("iPos", TYPE_VECTOR3),
	VertexElementDescription("iNormal", TYPE_VECTOR3),
	VertexElementDescription("iColor", TYPE_VECTOR3),
	VertexElementDescription("iTexCoord", TYPE_VECTOR2),
	VertexElementDescription("iTangent", TYPE_VECTOR4),
};