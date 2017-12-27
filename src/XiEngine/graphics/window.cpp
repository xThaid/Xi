#include "window.h"

#include "../utils/logger.h"

Window::Window(int width, int height) :
	width_(width),
	height_(height),
	renderSize_(IntVector2(0, 0))
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


	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	
	GLFWWindow_= glfwCreateWindow(mode->width, mode->height, "Xi", glfwGetPrimaryMonitor(), nullptr);

	if (GLFWWindow_ == nullptr)
	{
		Logger::error("Failed to create GLFW window");
		return false;
	}

	int renderWidth, renderHeight;

	glfwGetFramebufferSize(GLFWWindow_, &renderWidth, &renderHeight);

	renderSize_ = IntVector2(renderWidth, renderHeight);

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