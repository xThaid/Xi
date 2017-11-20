#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace ximath
{
	inline float degrees(float rad)
	{
		return (rad * 180.0f) / (float)M_PI;
	}

	inline float radians(float deg)
	{
		return (deg * (float)M_PI) / 180.0f;
	}
}