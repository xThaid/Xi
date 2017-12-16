#include <iostream>
#include <typeinfo>

#include "graphics\window.h"
#include "graphics\renderingEngine.h"
#include "core\core.h"
#include "core\program.h"

#include "utils\logger.h"

int main(int argc, char* argv[])
{
	const char* launchPath = argv[0];

	Logger::setLevel(Logger::LEVEL_DEBUG);

	Core core;
	core.start();

	return 0;
}