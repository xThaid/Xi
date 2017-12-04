#pragma once

#include "../precompiled.h"

#include <glad/glad.h>

#include "../resource/resource.h"
#include "../utils/file.h"

struct GLTextureOptions
{
	GLenum internalFormat = GL_RGBA;
	GLenum format         = GL_RGBA;
	GLenum type           = GL_UNSIGNED_BYTE;
	GLenum filterMin      = GL_LINEAR_MIPMAP_LINEAR;
	GLenum filterMax      = GL_LINEAR;
	GLenum wrapMethod     = GL_REPEAT;
	
	bool mipMapping       = false;
};

class GLTexture2D
{
public:
	GLTexture2D(unsigned int width, unsigned int height, GLTextureOptions options);
	GLTexture2D(unsigned int width, unsigned int height, GLTextureOptions options, void* data);
	~GLTexture2D();

	void bind(unsigned int textureUnit = 0);
	void unbind();

private:
	GLuint textureID_;
};

class Texture2D : public Resource
{
	XI_RESOURCE(Texture2D)

public:
	Texture2D(const std::string& name, const std::string& path);
	~Texture2D();

	virtual bool beginLoad() override;
	virtual bool endLoad() override;

	virtual void release() override;

	virtual const std::string getTypeName() const override { return "Texture2D"; }

	inline GLTexture2D* getGLTexture() { return glTexture_; }

private:
	File file_;

	GLTexture2D* glTexture_;

	unsigned char* data_;

	int width_;
	int height_;
	int numComponents_;	
};