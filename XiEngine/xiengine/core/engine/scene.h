#pragma once

#include <vector>

namespace xiengine
{
	class Entity;

	class Scene
	{
	public:
		Scene();

	private:
		std::vector<Entity> entities;


		friend class GraphicsEngine;
	};
}