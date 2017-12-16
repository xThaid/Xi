#include "window.h"

#include "../utils/logger.h"

Window::Window(int width, int height) :
	width_(width),
	height_(height),
	renderWidth_(0),
	renderHeight_(0)
{
}

Window::~Window()
{
	destroy();
}

bool Window::create()
{
	if (GLFWWindow_ != nullptr)
		return true;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	GLFWWindow_ = glfwCreateWindow(width_, height_, "Xi", nullptr, nullptr);

	if (GLFWWindow_ == nullptr)
	{
		Logger::error("Failed to create GLFW window");
		return false;
	}

	glfwGetFramebufferSize(GLFWWindow_, &renderWidth_, &renderHeight_);

	return true;
}

void Window::destroy()
{
	if (GLFWWindow_ != nullptr)
	{
		glfwDestroyWindow(GLFWWindow_);
		GLFWWindow_ = nullptr;
	}
}

void Window::swapBuffers() const
{
	if(GLFWWindow_ != nullptr)
		glfwSwapBuffers(GLFWWindow_);
}

bool Window::shouldClose()
{
	if (GLFWWindow_ == nullptr)
		return false;

	return glfwWindowShouldClose(GLFWWindow_) == 1;
}