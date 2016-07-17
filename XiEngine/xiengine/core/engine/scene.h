#pragma once

#include <vector>

namespace xiengine
{
	class Entity;

	class Scene
	{
	public:
		Scene();

		void update();

	private:
		std::vector<Entity> entities;


		friend class GraphicsEngine;
	};
}