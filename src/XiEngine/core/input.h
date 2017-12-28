#pragma once

#include "../precompiled.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window;

class Input
{
public:
	Input(Window* window);

	static void addPressedEvent(unsigned int key, std::function<void(void)> action);

	static bool getKey(int key);

	static float getMouseDeltaX();
	static float getMouseDeltaY();

	static void lockMouse();
	static void unlockMouse();

	void update();

private:
	Window* window_;

	float lastMouseX_, lastMouseY_;
	float mouseDeltaX_, mouseDeltaY_;
	bool isMouseLocked_ = true;

	bool pressed_[512];

	std::map<unsigned int, std::vector<std::function<void(void)> > >  onPressedEvents_;

	void _lockMouse();
	void _unlockMouse();
	void resetMousePos();

	void keyCallback(unsigned int key, unsigned int action);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};