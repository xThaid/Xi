#include <iostream>
#include <typeinfo>

#include "graphics\window.h"
#include "graphics\renderingEngine.h"
#include "core\core.h"
#include "core\program.h"

#include "utils\logger.h"
#include "utils/stringHash.h"

int main(int argc, char* argv[])
{
	const char* launchPath = argv[0];

	Logger::setLevel(Logger::LEVEL_DEBUG);

	Window win(800, 600, "Xi");

	Core core(&win);
	core.start();

	system("pause");
	return 0;
}