#pragma once

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

		void init();

		void makeContextCurrent(Window* window);

		void render(Scene* scene);
		void renderEntity(Entity* entity);
	private:

	};
}