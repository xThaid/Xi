#pragma once

#include <vector>
#include "entity/entity.h"

namespace xiengine
{
	class Entity;

	class Scene
	{
	public:
		Scene();

		void update();

		void destroy();
	private:
		std::vector<Entity> entities;


		friend class GraphicsEngine;
	};
}