#include "textureResource.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>

#include "resourceManager.h"

#include "../utils/file.h"

TextureResource::TextureResource(File file) :
	Resource(file)
{
}

TextureResource::~TextureResource()
{

}

void TextureResource::loadToRAM()
{
	data = stbi_load(file.getPath().c_str(), &width, &height, &nrChannels, 0);
}

void TextureResource::unloadFromRAM()
{
	stbi_image_free(data);
}

void TextureResource::loadToGPU()
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLuint pixelFormat = GL_RED;
	if (nrChannels == 3)
		pixelFormat = GL_RGB;
	else if (nrChannels == 4)
		pixelFormat = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void TextureResource::unloadFromGPU()
{
	glDeleteTextures(1, &textureID);
}
