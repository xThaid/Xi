#include "core.h"

#include <iostream>
#include <chrono>
#include <iomanip>

#include "program.h"
#include "time.h"
#include "input.h"
#include "../scene/scene.h"

#include "../resource/resourceManager.h"
#include "../graphics/window.h"
#include "../utils/logger.h"

Core* Core::currentCore = nullptr;

Core::Core()
{
	running = false;

	upsLimit = 0;
	fpsLimit = 60;

	mainWindow = new Window(800, 800);
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
		exit(0);
	}
}

void Core::init()
{
	currentCore = this;

	resourceManager = new ResourceManager();

	graphics = new Graphics(mainWindow);
	rendering = new RenderingEngine();

	program = new Program();

	time = new Time();
	input = new Input(mainWindow);

	scene = nullptr;

	program->init();

	Logger::info("Initialization completed");
}

void Core::destroy()
{
	delete program;

	if (scene != nullptr)
		delete scene;

	delete resourceManager;

	delete rendering;
	delete graphics;

	delete mainWindow;

	delete time;
	delete input;

	currentCore = nullptr;
}
	
void Core::loop()
{
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
				upsDelta += delta.count() * upsLimit / 1000;
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
				fpsDelta += delta.count() * fpsLimit / 1000;
				if (fpsDelta >= 1.0)
				{
					render();
					frames++;
					fpsDelta -= 1.0;
				}
			}
		}

		if (mainWindow->shouldClose())
			stop();
	}
}

void Core::update()
{
	time->updateDelta();
	input->update();

	program->update();

	if(scene != nullptr)
		scene->update();

	glfwPollEvents();
}

void Core::render()
{
	if(scene != nullptr)
		rendering->render(scene);
}

void Core::setCurrentScene(Scene* scene)
{
	if (currentCore->scene != nullptr)
		delete scene;

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