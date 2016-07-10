#pragma once

#include <vector>

namespace xiengine
{
	class Entity;

	class Scene
	{
		friend class GraphicsEngine;

	public:
		Scene();

	private:
		std::vector<Entity> entities;
	};
}