#include "program.h"

#include "core.h"
#include "scene.h"
#include "resource\resourceManager.h"

namespace xiengine
{
	void Program::init()
	{
		ResourceManager* resManager = Core::getCurrentResourceManager();

		resManager->addResource("D:\\Dev\\GameDev\\txt\\brick\\brickwall.jpg");

		Core::getCurrentCore()->setCurrentScene(new Scene());
	}

	void Program::update()
	{

	}
}