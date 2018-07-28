#pragma once

#include "../graphics/graphics.h"
#include "../graphics/renderingEngine.h"

class ResourceManager;
class Scene;
class Program;
class Input;
class Time;

class Core
{
	friend class Time;
	friend class Input;
	friend class ResourceManager;

public:
	Core();

	void start();
	void stop();

	inline void setUPSLimit(int upsLimit) { this->upsLimit = upsLimit; }
	inline void setFPSLimit(int fpsLimit) { this->fpsLimit = fpsLimit; }

	inline bool isRunning() { return running; }

	inline RenderingEngine* getRenderer() { return rendering; }

	inline int getLastUPS() { return lastUPS; }
	inline int getLastFPS() { return lastFPS; }

	static void setCurrentScene(Scene* scene);

	static Core* getCurrentCore();
	static Scene* getCurrentScene();

private:
	static Core* currentCore;

	Window* mainWindow;
	Graphics* graphics;
	RenderingEngine* rendering;
	Program* program;

	Time* time;
	Input* input;

	ResourceManager* resourceManager;

	Scene* scene;

	bool running;
	int upsLimit;
	int fpsLimit;

	int lastUPS;
	int lastFPS;

	void init();
	void destroy();

	void loop();
		
	void update();
	void render();
};