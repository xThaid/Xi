#include "renderingEngine.h"

#include <iostream>

namespace xiengine
{
	RenderingEngine::RenderingEngine()
	{
		glfwInit();
	}

	void RenderingEngine::init()
	{
		glewExperimental = GL_TRUE;
		GLenum status = glewInit();
		if (status != GLEW_OK)
			std::cout << "Failed to initialize GLEW: " << glewGetErrorString(status) << std::endl;
	}

	void RenderingEngine::makeContextCurrent(Window* window)
	{
		glfwMakeContextCurrent(window->getWindow());
		glViewport(0, 0, window->getWidth(), window->getHeight());
	}

	void RenderingEngine::render(Scene* scene)
	{
		glClearColor(0.0f, 0.3f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderingEngine::renderEntity(Entity* entity)
	{

	}
}