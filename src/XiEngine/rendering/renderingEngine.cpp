#include "renderingEngine.h"

#include <iostream>

namespace xiengine
{
	RenderingEngine::RenderingEngine()
	{
		glfwInit();

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			std::cout << "Failed to initialize GLEW" << std::endl;
	}
}