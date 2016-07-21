#include "core.h"

#include <iostream>
#include <chrono>
#include <iomanip>

#include "program.h"
#include "time\time.h"
#include "time\timer.h"
#include "scene.h"

#include "../utils/logger.h"

namespace xiengine
{
	Core* Core::currentCore = nullptr;

	Core::Core(Window* window) : 
		mainWindow(window)
	{
		running = false;

		upsLimit = 0;
		fpsLimit = 60;
	}

	void Core::start()
	{
		Logger::info("Starting Xi...!");
		if (!running)
		{
			init();
			running = true;
			loop();
		}
	}

	void Core::stop()
	{
		Logger::info("Shutting down Xi...!");
		if (running)
		{
			destroy();
			running = false;
		}
	}

	void Core::init()
	{
		rendering = new RenderingEngine();
		time = new Time();

		scene = nullptr;
		currentCore = this;

		mainWindow->init(false);
		rendering->makeContextCurrent(mainWindow);

		rendering->init();

		program->init();

		Logger::info("Initialization completed");
	}

	void Core::destroy()
	{
		delete rendering;
		delete time;

		if (scene != nullptr)
			delete scene;

		currentCore = nullptr;
	}
	
	void Core::loop()
	{
		const int milliSeconds = 1000;

		double upsDelta = 0.0;
		double fpsDelta = 0.0;

		int updates = 0;
		int frames = 0;

		Timer fpsTimer([&updates, &frames]() -> void
		{
			Logger::trace(std::to_string(updates) + "ups, " + std::to_string(frames) + "fps");
			updates = 0;
			frames = 0;

		}, 1000);
		fpsTimer.start();

		std::chrono::time_point<std::chrono::high_resolution_clock> lastTime = std::chrono::high_resolution_clock::now();

		while (running)
		{
			time->update();
			if (scene != nullptr)
			{
				std::chrono::time_point<std::chrono::high_resolution_clock> currentTime = std::chrono::high_resolution_clock::now();
				std::chrono::duration<float, std::milli> delta = currentTime - lastTime;
				lastTime = currentTime;

				if (upsLimit == 0)
				{
					update();
					updates++;
				}
				else
				{
					upsDelta += delta.count() * upsLimit / milliSeconds;
					if (upsDelta >= 1.0)
					{
						update();
						updates++;
						upsDelta -= 1.0;
					}
				}

				if (fpsLimit == 0)
				{
					render();
					frames++;
				}
				else
				{
					fpsDelta += delta.count() * fpsLimit / milliSeconds;
					if (fpsDelta >= 1.0)
					{
						render();
						frames++;
						fpsDelta -= 1.0;
					}
				}
			}

			glfwPollEvents();

			if (mainWindow->shouldClose())
				stop();
		}
	}

	void Core::update()
	{
		time->updateDelta();
		if(scene != nullptr)
			scene->update();
	}

	void Core::render()
	{
		if(scene != nullptr)
			rendering->render(scene);

		mainWindow->swapBuffers();
	}

	void Core::setCurrentScene(Scene* scene)
	{
		if (currentCore->scene != nullptr)
		{
			currentCore->scene->destroy();
			delete scene;
		}

		currentCore->scene = scene;
	}

	Core* Core::getCurrentCore()
	{
		return currentCore;
	}

	Scene* Core::getCurrentScene()
	{
		return currentCore->scene;
	}

}