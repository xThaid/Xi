#pragma once

#include <cinttypes>

namespace TDEngine
{
	class File;

	class TextureAsset
	{
	public:
		TextureAsset(File file);
		~TextureAsset();

	private:
		uint32_t textureID;
	};
}
