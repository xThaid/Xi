#pragma once

#include "../rendering/renderingEngine.h"

class Scene;
class Program;
class Time;

class Core
{
	friend class Time;
	friend class Input;

public:
	Core(Window* window);

	void start();
	void stop();

	inline void setUPSLimit(int upsLimit) { this->upsLimit = upsLimit; }
	inline void setFPSLimit(int fpsLimit) { this->fpsLimit = fpsLimit; }

	inline bool isRunning() { return running; }

	static void setCurrentScene(Scene* scene);

	static Core* getCurrentCore();
	static Scene* getCurrentScene();

private:
	static Core* currentCore;

	Window* mainWindow;
	RenderingEngine* rendering;
	Program* program;

	Time* time;
	Input* input;

	Scene* scene;

	bool running;
	int upsLimit;
	int fpsLimit;

	void init();
	void destroy();

	void loop();
		
	void update();
	void render();
};