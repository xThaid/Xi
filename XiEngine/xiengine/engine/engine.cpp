#include "tdengine.h"

#include <iostream>
#include <chrono>

namespace TDEngine
{
	TDEngine::TDEngine()
	{
	}


	void TDEngine::start()
	{
		if (!init())
			return;

		loop();
	}

	bool TDEngine::init() 
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		windowID = glfwCreateWindow(WIDTH, HEIGHT, "TD Engine", nullptr, nullptr);
		if (windowID == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(windowID);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW" << std::endl;
			return false;
		}

		glViewport(0, 0, WIDTH, HEIGHT);

		return true;
	}

	void TDEngine::loop()
	{
		std::chrono::time_point<std::chrono::system_clock> lastTime = std::chrono::system_clock::now();
		double delta = 0.0;
		double ns = 1000000000.0 / 60.0;
		std::chrono::time_point<std::chrono::system_clock> timer = std::chrono::system_clock::now();

		int updates = 0;
		int frames = 0;
		running = true;
		while (running) {
			std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
			std::chrono::duration<unsigned long long, std::nano> deltaTime = now - lastTime;
			delta += deltaTime.count() / ns;
			lastTime = now;
			if (delta >= 1.0) {
				update((float) delta);
				updates++;
				delta--;
			}

			render();
			frames++;
			std::chrono::duration<double, std::milli> timerDelta = now - timer;
			if (timerDelta.count() > 1000) {
				timer = now;
				std::cout << updates << " ups, " << frames << " fps" << std::endl;
				updates = 0;
				frames = 0;
			}

			if (glfwWindowShouldClose(windowID) == GL_TRUE)
				running = false;
		}
	}

	void TDEngine::update(float delta)
	{

		glfwPollEvents();
	}

	void TDEngine::render()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glfwSwapBuffers(windowID);
	}
}