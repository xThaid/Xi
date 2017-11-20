#pragma once

#include <glad/glad.h> 
#include <GLFW\glfw3.h>

#include "window.h"
#include "shader\shader.h"

class Scene;
class Entity;

class RenderingEngine
{
public:
	RenderingEngine(Window* window);
	~RenderingEngine();

	void init();

	void render(Scene* scene);
private:
	Shader* basicShader;

	unsigned int VBO, VAO;

	void setUp();
	void destroy();
};
