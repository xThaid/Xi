#pragma once

#include "ximath.h"

#include "componentBase.h"

namespace xiengine
{
	class TransformComponent : public ComponentBase
	{
	public:
		ximath::Vector3 position;
		ximath::Quaternion rotation;
		ximath::Vector3 scale;

		ComponentType getType();
	};
}