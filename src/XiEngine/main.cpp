#include <iostream>

#include "rendering\window.h"
#include "rendering\renderingEngine.h"
#include "core\core.h"
#include "core\program.h"

using namespace xiengine;

int main()
{
	Window win(800, 600, "Test");

	Core core(&win);
	core.start();

	system("pause");
	return 0;
}