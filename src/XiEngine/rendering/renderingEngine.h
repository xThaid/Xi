#pragma once

#include <GL/glew.h>
#include <GLFW\glfw3.h>

#include "window.h"

#include "shader\entityShader.h"

namespace xiengine
{
	class Scene;
	class Entity;

	class RenderingEngine
	{
	public:
		RenderingEngine();
		~RenderingEngine();

		void init();

		void makeContextCurrent(Window* window);

		void render(Scene* scene);
		void renderEntity(Entity* entity);
	private:
		EntityShader entityShader;

		void destroy();
	};
}