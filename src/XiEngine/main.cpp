#include <iostream>
#include <typeinfo>

#include "rendering\window.h"
#include "rendering\renderingEngine.h"
#include "core\core.h"
#include "core\program.h"

#include "core\entity\component\modelComponent.h"

#include "utils\logger.h"

using namespace xiengine;

int main(int argc, char* argv[])
{
	Logger::setLevel(Logger::LEVEL_TRACE);

	Window win(800, 600, "Xi");

	Core core(&win);
	core.start();

	system("pause");
	return 0;
}