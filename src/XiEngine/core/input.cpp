#include "input.h"

#include "../rendering/window.h"
#include "core.h"

Input::Input(Window* window)
{
	this->window = window;

	glfwSetKeyCallback(window->getWindow(), key_callback);

	_lockMouse();
}

bool Input::getKey(int key)
{
	return glfwGetKey(Core::getCurrentCore()->input->window->getWindow(), key);
}

float Input::getMouseDeltaX()
{
	return Core::getCurrentCore()->input->mouseDeltaX;
}

float Input::getMouseDeltaY()
{
	return Core::getCurrentCore()->input->mouseDeltaY;
}

void Input::lockMouse()
{
	Core::getCurrentCore()->input->_lockMouse();
}

void Input::unlockMouse()
{
	Core::getCurrentCore()->input->_unlockMouse();
}

void Input::update()
{
	if (isMouseLocked)
	{
		double xpos, ypos;
		glfwGetCursorPos(window->getWindow(), &xpos, &ypos);
		mouseDeltaX = (float)xpos - lastMouseX;
		mouseDeltaY = (float)ypos - lastMouseY;

		lastMouseX = (float)xpos;
		lastMouseY = (float)ypos;
	}
}

void Input::_lockMouse()
{
	resetMousePos();
	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	isMouseLocked = true;
}

void Input::_unlockMouse()
{
	resetMousePos();
	glfwSetInputMode(Core::getCurrentCore()->input->window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	isMouseLocked = false;
}

void Input::resetMousePos()
{
	double xpos, ypos;
	glfwGetCursorPos(window->getWindow(), &xpos, &ypos);
	lastMouseX = (float)xpos;
	lastMouseY = (float)ypos;
	mouseDeltaX = 0.0f;
	mouseDeltaY = 0.0f;
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
}