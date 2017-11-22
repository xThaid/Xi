#include "test.h"

#include "../math\ximath.h"

#include <iostream>
#include <assert.h>

using namespace std;

void mathTest()
{
	xim::Matrix4 lok1 = xim::lookAt(xim::Vector3(), xim::Vector3(0.0f, 0.0f, -1.0f), xim::Vector3(0.0f, 1.0f, 0.0f));

	for (int i = 0; i < 16; i++)
	{
		cout << *(lok1.getPointer() + i) << " " << endl;
	}
}