#pragma once

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