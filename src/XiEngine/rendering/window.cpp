#include "window.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include "../utils/logger.h"

Window::Window(int width, int height, const std::string& title) :
	width(width), height(height), title(title)
{
}

Window::~Window()
{
	glfwDestroyWindow(window);
}

bool Window::init()
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
		Logger::error("Failed to create GLFW window");
		return false;
	}


	glfwSwapInterval(1);

	return true;
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
		fullscreen = enabled;
		GLFWmonitor* currMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(currMonitor);

		glfwDestroyWindow(window);

		init();
	}
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(window) == GL_TRUE;
}