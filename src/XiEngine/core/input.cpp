#include "input.h"

#include "../core/core.h"
#include "../graphics/window.h"

Input::Input(Window* window) :
	window_(window)
{
	glfwSetKeyCallback(window->getGLFWWindow(), key_callback);

	for (unsigned int i = 0; i < 512; i++)
		pressed_[i] = false;

	_lockMouse();
}

void Input::addPressedEvent(unsigned int key, std::function<void(void)> action)
{
	Core::getCurrentCore()->input->onPressedEvents_[key].push_back(action);
}

bool Input::getKey(int key)
{
	return glfwGetKey(Core::getCurrentCore()->input->window_->getGLFWWindow(), key) != GLFW_RELEASE;
}

float Input::getMouseDeltaX()
{
	return Core::getCurrentCore()->input->mouseDeltaX_;
}

float Input::getMouseDeltaY()
{
	return Core::getCurrentCore()->input->mouseDeltaY_;
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
	if (isMouseLocked_)
	{
		double xpos, ypos;
		glfwGetCursorPos(window_->getGLFWWindow(), &xpos, &ypos);
		mouseDeltaX_ = (float)xpos - lastMouseX_;
		mouseDeltaY_ = (float)ypos - lastMouseY_;

		lastMouseX_ = (float)xpos;
		lastMouseY_ = (float)ypos;
	}
}

void Input::_lockMouse()
{
	resetMousePos();
	glfwSetInputMode(window_->getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	isMouseLocked_ = true;
}

void Input::_unlockMouse()
{
	resetMousePos();
	glfwSetInputMode(Core::getCurrentCore()->input->window_->getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	isMouseLocked_ = false;
}

void Input::resetMousePos()
{
	double xpos, ypos;
	glfwGetCursorPos(window_->getGLFWWindow(), &xpos, &ypos);
	lastMouseX_ = (float)xpos;
	lastMouseY_ = (float)ypos;
	mouseDeltaX_ = 0.0f;
	mouseDeltaY_ = 0.0f;
}

void Input::keyCallback(unsigned int key, unsigned int action)
{
	auto& res = onPressedEvents_.find(key);
	if(res != onPressedEvents_.end())
	{
		if (action == GLFW_PRESS && !pressed_[key])
		{
			for (unsigned int i = 0; i < res->second.size(); i++)
			{
				res->second[i]();
			}
			pressed_[key] = true;
		}
		else
		{
			pressed_[key] = false;
		}
	}
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Core::getCurrentCore()->input->keyCallback(key, action);
}