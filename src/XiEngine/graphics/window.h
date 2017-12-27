#pragma once

#include "../precompiled.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../math/ximath.h"

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

	inline IntVector2 getRenderSize() { return renderSize_; }

private:
	GLFWwindow* GLFWWindow_;

	const int width_;
	const int height_;

	IntVector2 renderSize_;
};