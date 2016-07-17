#include "ximath\ximath.h"
#include <iostream>


int main()
{

	ximath::vec3 lul(1, 0, 0);
	ximath::vec3 lul2(0, 1, 0);

	ximath::vec3 aa = ximath::cross(lul, lul2);

	std::cout << aa.x;

	system("pause");
	return 0;
}
