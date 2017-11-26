#pragma once

#include <glad/glad.h> 
#include <GLFW\glfw3.h>

#include <string>

class File;

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	void bindTexture(GLuint textureUnit);
	void unbindTexture(GLuint textureUnit);

private:
	File* file;
	GLuint textureID;

	void load();
	void unload();
};