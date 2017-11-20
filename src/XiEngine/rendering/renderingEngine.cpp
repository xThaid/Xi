#include "renderingEngine.h"

#include <iostream>

#include "../utils/logger.h"

RenderingEngine::RenderingEngine(Window * window)
{
	if (!glfwInit())
		Logger::error("Failed to initialize GLFW");
	else
		Logger::debug("GLFW version: " + std::string(glfwGetVersionString()));

	window->init();
	glfwMakeContextCurrent(window->getWindow());

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		Logger::error("Failed to initialize GLAD");

	Logger::info("OpenGL version: " + std::string((char*)glGetString(GL_VERSION)));
}


RenderingEngine::~RenderingEngine()
{
	destroy();
}

void RenderingEngine::init()
{
	glEnable(GL_DEPTH_TEST);
}

void RenderingEngine::destroy()
{
	glfwTerminate();
}

void RenderingEngine::render(Scene* scene)
{
	glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}