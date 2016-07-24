#pragma once

#include <string>

namespace xiengine
{
	enum ComponentType
	{
		Transform,
		ModelRenderer,
		Camera
	};


	class ComponentBase
	{
	public:
		virtual ComponentType getType() = 0;
	};
}