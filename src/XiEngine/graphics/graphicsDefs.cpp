#include "graphicsDefs.h"

extern const unsigned ELEMENT_TYPESIZES[] =
{
	sizeof(int),
	sizeof(float),
	2 * sizeof(float),
	3 * sizeof(float),
	4 * sizeof(float),
	sizeof(unsigned int)
};

extern const VertexElementDescription VERTEXELEMENTS[] = 
{
	VertexElementDescription("iPos", TYPE_VECTOR3),
	VertexElementDescription("iNormal", TYPE_VECTOR3),
	VertexElementDescription("iColor", TYPE_UBYTE4_NORM),
	VertexElementDescription("iTexCoord", TYPE_VECTOR2),
	VertexElementDescription("iTangent", TYPE_VECTOR4),
};