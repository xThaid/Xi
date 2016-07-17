#include "coreEngine.h"

#include <iostream>
#include <chrono>

#include "program.h"
#include "engine\scene.h"

namespace xiengine
{
	CoreEngine::CoreEngine(Window* window, Program* program) : 
		mainWindow(window),
		rendering(RenderingEngine::getInstance()),
		program(program)
	{
		isRunning = false;
		mainWindow->init(false);
		program->init();
	}

	void CoreEngine::start()
	{
		if (!isRunning)
		{
			isRunning = true;
			loop();
		}
	}

	void CoreEngine::stop()
	{
		isRunning = false;
	}

	void CoreEngine::loop()
	{
		std::chrono::time_point<std::chrono::system_clock> lastTime = std::chrono::system_clock::now();
		double delta = 0.0;
		double ns = 1000000000.0 / 60.0;
		std::chrono::time_point<std::chrono::system_clock> timer = std::chrono::system_clock::now();

		int updates = 0;
		int frames = 0;

		while (isRunning) 
		{
			std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
			std::chrono::duration<unsigned long long, std::nano> deltaTime = now - lastTime;
			delta += deltaTime.count() / ns;
			lastTime = now;
			if (delta >= 1.0) 
			{
				update();
				updates++;
				delta--;
			}

			render();
			frames++;
			std::chrono::duration<double, std::milli> timerDelta = now - timer;
			if (timerDelta.count() > 1000)
			{
				timer = now;
				std::cout << updates << " ups, " << frames << " fps" << std::endl;
				updates = 0;
				frames = 0;
			}

			if (mainWindow->shouldClose())
				stop();
		}
	}

	void CoreEngine::update()
	{
		if(scene != nullptr)
			scene->update();

		glfwPollEvents();
	}

	void CoreEngine::render()
	{
		if(scene != nullptr)
			rendering->renderScene(scene);

		mainWindow->swapBuffers();
	}
}