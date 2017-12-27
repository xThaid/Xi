#include "texture.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "../utils/file.h"
#include "../utils/logger.h"

GLTexture2D::GLTexture2D(unsigned int width, unsigned int height, GLTextureOptions options) :
	GLTexture2D(width, height, options, 0)
{
}

GLTexture2D::GLTexture2D(unsigned int width, unsigned int height, GLTextureOptions options, void* data)
{
	glGenTextures(1, &textureID_);

	glBindTexture(GL_TEXTURE_2D, textureID_);
	
	glTexImage2D(GL_TEXTURE_2D, 0, options.internalFormat, width, height, 0, options.format, options.type, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, options.filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, options.filterMax);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, options.wrapMethod);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, options.wrapMethod);
	if (options.mipMapping)
		glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

GLTexture2D::~GLTexture2D()
{
	glDeleteTextures(1, &textureID_);
}

Texture2D::Texture2D(const std::string& name, const std::string& path) :
	Resource(name),
	file_(path)
{
}

Texture2D::~Texture2D()
{
	if (data_ != 0)
		stbi_image_free(data_);
}

bool Texture2D::beginLoad()
{
	if (!file_.exist())
		return false;

	stbi_set_flip_vertically_on_load(true);

	data_= stbi_load(file_.getPath().c_str(), &width_, &height_, &numComponents_, 0);

	return data_ != 0;
}

bool Texture2D::endLoad()
{
	GLTextureOptions options;
	
	switch (numComponents_)
	{
	case 1:
		options.format = GL_RED;
		break;
	case 3:
		options.format = GL_RGB;
		break;
	case 4:
		options.format = GL_RGBA;
		break;
	default:
		Logger::error("Unknown format of loaded image: " + getName());
		return false;
	}

	options.mipMapping = true;
	
	glTexture_ = new GLTexture2D(width_, height_, options, data_);

	return true;
}

void Texture2D::release()
{
	delete glTexture_;
}
