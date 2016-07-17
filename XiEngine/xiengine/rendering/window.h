#pragma once

#include <string>

namespace xiengine
{
	class Window
	{
	public:
		Window(int width, int height, const std::string& title);
		~Window();

		bool init(bool fullscreen);
		void swapBuffers() const;

		void setFullscreen(bool enabled);

		bool shouldClose();

		inline GLFWwindow* getWindow() const { return window; }

		inline int getWidth() const { return width; }
		inline int getHeight() const { return height; }

	private:
		GLFWwindow* window;

		const int width;
		const int height;
		
		const std::string title;

		bool fullscreen;
	};
}