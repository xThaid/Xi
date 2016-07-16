#include "window.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW\glfw3.h>

#include <iostream>

namespace xiengine
{
	Window::Window(int width, int height, const std::string& title) :
		width(width), height(height), title(title)
	{
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
	}

	bool Window::init(bool fullscreen)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		if(fullscreen)
			window = glfwCreateWindow(width, height, title.c_str(), glfwGetPrimaryMonitor(), nullptr);
		else
			window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		if (window == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			return false;
		}
	}

	void Window::swapBuffers() const
	{
		if(window != nullptr)
		glfwSwapBuffers(window);
	}

	void Window::setFullscreen(bool enabled) 
	{
		if (window != nullptr && enabled != fullscreen)
		{
			GLFWmonitor* currMonitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(currMonitor);

			glfwDestroyWindow(window);

			init(enabled);
		}
	}
}