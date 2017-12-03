#pragma once

#include "resource.h"

#include "../utils/file.h"

class TextureResource : public Resource
{
public:
	TextureResource(File file);
	~TextureResource();

private:
	unsigned char* data;

	int width, height, nrChannels;

	unsigned int textureID;

	void loadToRAM();
	void unloadFromRAM();

	void loadToGPU();
	void unloadFromGPU();
};