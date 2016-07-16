#pragma once

namespace xiengine
{
	class BaseAsset
	{
	public:
		virtual bool load() = 0;
		virtual bool free() = 0;
	};
}