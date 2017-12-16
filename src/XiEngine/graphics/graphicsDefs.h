#pragma once

#include "../precompiled.h"

enum class PrimitiveTopology
{
	POINTS = 0,
	LINES,
	LINE_STRIP,
	TRIANGLES,
	TRIANGLE_STRIP,
	TRIANGLE_FAN,
};

enum FillMode
{
	FILL_SOLID = 0,
	FILL_WIREFRAME,
	FILL_POINT
};

enum VertexElementType
{
	TYPE_INT = 0,
	TYPE_FLOAT,
	TYPE_VECTOR2,
	TYPE_VECTOR3,
	TYPE_VECTOR4,
	MAX_VERTEX_ELEMENT_TYPES
};

extern const unsigned ELEMENT_TYPESIZES[];

enum VertexElement
{
	VE_POSITION = 0,
	VE_NORMAL,
	VE_COLOR,
	VE_TEXCOORD,
	VE_TANGENT,
	MAX_VERTEX_ELEMENT
};

struct VertexElementDescription
{
	std::string name_;
	VertexElementType type_;
	
	VertexElementDescription(std::string name, VertexElementType type) :
		name_(name),
		type_(type)
	{
	}
};

extern const VertexElementDescription VERTEXELEMENTS[];

static const unsigned MASK_POSITION = 0x1;
static const unsigned MASK_NORMAL = 0x2;
static const unsigned MASK_COLOR = 0x4;
static const unsigned MASK_TEXCOORD = 0x8;
static const unsigned MASK_TANGENT = 0x10;