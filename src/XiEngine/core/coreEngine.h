#pragma once

#include "../rendering/renderingEngine.h"

namespace xiengine
{
	class Scene;
	class Program;

	class CoreEngine
	{
	public:
		CoreEngine(Window* window, Program* program);

		void start();
		void stop();

		inline void setScene(Scene* scene) { this->scene = scene; }
		inline Scene* getScene() { return scene; }

	private:
		Window* mainWindow;
		RenderingEngine* rendering;
		Program* program;

		Scene* scene;

		bool isRunning;

		void loop();
		
		void update();
		void render();
	};
}