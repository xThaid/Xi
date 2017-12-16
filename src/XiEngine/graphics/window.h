#pragma once

#include "../precompiled.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int width, int height);
	~Window();

	bool create();
	void destroy();

	void swapBuffers() const;

	bool shouldClose();

	inline GLFWwindow* getGLFWWindow() const { return GLFWWindow_; }

	inline int getWidth() const { return width_; }
	inline int getHeight() const { return height_; }

	inline int getRenderWidth() const { return renderWidth_; }
	inline int getRenderHeight() const { return renderHeight_; }

private:
	GLFWwindow* GLFWWindow_;

	const int width_;
	const int height_;

	int renderWidth_;
	int renderHeight_;
};