#pragma once

#include "../precompiled.h"

#include <limits>

#undef M_PI
static const float M_PI = 3.14159265358979323846264338327950288f;
static const float M_HALF_PI = M_PI * 0.5f;
static const float M_TWO_PI = M_PI * 2.0f;

static const float M_EPSILON = 0.000001f;
static const float M_INFINITY = (float)HUGE_VAL;

static const float M_DEGTORAD = M_PI / 180.0f;
static const float M_RADTODEG = 1.0f / M_DEGTORAD;

enum Intersection
{
	OUTSIDE,
	INTERSECTS,
	INSIDE
};

inline float radToDeg(float rad) { return rad * M_RADTODEG; }
inline float degToRad(float deg) { return deg * M_DEGTORAD; }

