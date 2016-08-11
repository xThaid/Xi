#pragma once

namespace xiengine
{
	class Window;
	class RenderingEngine;
	class ResourceManager;
	class Program;

	class Scene;
	
	class Time;

	class Core
	{
		friend class Time;

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
		static ResourceManager* getCurrentResourceManager();

	private:
		static Core* currentCore;

		Window* mainWindow;
		RenderingEngine* renderingEngine;
		ResourceManager* resourceManager;
		Program* program;
		Time* time;

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
}