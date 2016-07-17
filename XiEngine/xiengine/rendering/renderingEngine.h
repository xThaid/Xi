#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW\glfw3.h>

#include "window.h"

namespace xiengine
{
	class Scene;
	class Entity;

	class RenderingEngine
	{
	public:
		RenderingEngine();

		void makeContextCurrent(const Window& window);

		void renderScene(Scene* scene);
		void renderEntity(Entity* entity);

		static RenderingEngine* getInstance() { return &instance; }

	private:
		static RenderingEngine instance;
	};
}