#pragma once

#include <glad/glad.h> 
#include <GLFW\glfw3.h>

#include "window.h"
#include "shader\shader.h"

class Scene;

class RenderingEngine
{
public:
	RenderingEngine(Window* window);
	~RenderingEngine();

	void init();
	void changeViewport(int width, int height);

	void render(Scene* scene);
private:
	int viewportWidth, viewportHeight;

	Shader* basicShader;

	unsigned int VBO, VAO,EBO;

	void setUp();
	void cleanUp();
	void destroy();
};
