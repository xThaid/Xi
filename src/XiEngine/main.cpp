#include <iostream>

#include "rendering\window.h"
#include "rendering\renderingEngine.h"
#include "core\coreEngine.h"
#include "core\program.h"

using namespace xiengine;

int main()
{
	Window win(800, 600, "Test");
	RenderingEngine rendering;
	Program program;

	CoreEngine eng(&win, &rendering, &program);
	eng.start();

	system("pause");
	return 0;
}