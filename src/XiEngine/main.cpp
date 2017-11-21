#include <iostream>
#include <typeinfo>

#include "rendering\window.h"
#include "rendering\renderingEngine.h"
#include "core\core.h"
#include "core\program.h"

#include "utils\logger.h"

#include "testing.h"

int main(int argc, char* argv[])
{
	Logger::setLevel(Logger::LEVEL_TRACE);

	Window win(800, 600, "Xi");

	Core core(&win);
	core.start();

	system("pause");
	return 0;
}