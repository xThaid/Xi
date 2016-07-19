#include "renderingEngine.h"

#include <iostream>

#include "../utils/logger.h"

namespace xiengine
{
	RenderingEngine::RenderingEngine()
	{
		if (!glfwInit())
			Logger::error("Failed to initialize GLFW");
		else
			Logger::debug("GLFW version: " + std::string(glfwGetVersionString()));
	}

	void RenderingEngine::init()
	{
		glewExperimental = GL_TRUE;
		GLenum status = glewInit();
		if (status != GLEW_OK)
			Logger::error("Failed to initialize GLEW: " + std::string((char*) glewGetErrorString(status)));
		else
			Logger::debug("GLEW version: " + std::string((char*) glewGetString(GLEW_VERSION)));
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