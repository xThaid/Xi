#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "../utils/file.h"
#include "../utils/logger.h"

Texture::Texture(const std::string& path)
{
	file = new File(path);
	load();
}

Texture::~Texture()
{
	unload();

	delete file;
}

void Texture::bindTexture(GLuint textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbindTexture(GLuint textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::load()
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	unsigned char* data = stbi_load(file->getPath().c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		GLuint pixelFormat = GL_RED;
		if (nrChannels == 3)
			pixelFormat = GL_RGB;
		else if (nrChannels == 4)
			pixelFormat = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		Logger::warn("Couldn't load texture:" + file->getPath());

	stbi_image_free(data);
}

void Texture::unload()
{
	glDeleteTextures(1, &textureID);
}