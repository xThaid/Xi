#include "program.h"

#include "core.h"
#include "scene.h"

namespace xiengine
{
	void Program::init()
	{
		Core::getCurrentCore()->setCurrentScene(new Scene());
	}

	void Program::update()
	{

	}
}