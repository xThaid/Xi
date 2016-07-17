#include "program.h"

#include "coreEngine.h"

namespace xiengine
{
	void Program::init()
	{

	}

	void Program::update()
	{

	}

	int main()
	{
		Window win(800, 600, "Test");
		Program program;

		CoreEngine eng(&win, &program);
		eng.start();

		return 0;
	}
}