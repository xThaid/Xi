#include "utils.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace ximath
{
	float radiansToDegrees(float rad)
	{
		return (rad * 180.0f) /(float) M_PI;
	}

	float degreesToRadians(float deg)
	{
		return (deg * (float) M_PI) / 180.0f;
	}
}