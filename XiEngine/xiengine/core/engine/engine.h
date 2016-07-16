#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW\glfw3.h>

namespace xiengine
{
	class XiEngine
	{
	public:
		XiEngine();

		void start();

	private:
		const GLint WIDTH = 800, HEIGHT = 800;

		GLFWwindow* windowID;
		bool running = false;

		bool init();
		void loop();
		void render();
		void update(float delta);
	};
}