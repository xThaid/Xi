#pragma once

#include "ximath\ximath.h"

#include "componentBase.h"

namespace xiengine
{
	class transformComponent : ComponentBase
	{
	public:
		ximath::Vector3 position;
		ximath::Quaternion rotation;
		ximath::Vector3 rotation;
	};
}