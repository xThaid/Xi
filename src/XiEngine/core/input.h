#pragma once

#include <glad/glad.h> 
#include <GLFW\glfw3.h>

class Window;

class Input
{
public:
	Input(Window* window);

	static bool getKey(int key);

	static float getMouseDeltaX();
	static float getMouseDeltaY();

	static void lockMouse();
	static void unlockMouse();

	void update();

private:
	Window* window;

	float lastMouseX, lastMouseY;
	float mouseDeltaX, mouseDeltaY;
	bool isMouseLocked = true;

	void _lockMouse();
	void _unlockMouse();
	void resetMousePos();

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};