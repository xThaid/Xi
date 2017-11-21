#include "testing.h"

#include "math\ximath.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <assert.h>

using namespace std;

void mathTest()
{
	xim::Matrix4 my;
	glm::mat4 mat = glm::mat4(1.0f);

	my.scale(2.0f, 4.0f, -2.0f);
	my.translate(1.0f, 2.0f, 3.0f);
	my.rotate(30.0f, 1.0f, 0.0f, 0.5f);
	my.translate(-3.0f, 10.0f, 2.0f);
	my.scale(xim::Vector3(0.5f));
	my.rotateZ(glm::radians(-83.0f));

	mat = glm::scale(mat, glm::vec3(2.0f, 4.0f, -2.0f));
	mat = glm::translate(mat, glm::vec3(1.0f, 2.0f, 3.0f));
	mat = glm::rotate(mat, 30.0f, glm::vec3(1.0f, 0.0f, 0.5f));
	mat = glm::translate(mat, glm::vec3(-3.0f, 10.0f, 2.0f));
	mat = glm::scale(mat, glm::vec3(0.5f));
	mat = glm::rotate(mat, glm::radians(-83.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	xim::Matrix4 per = xim::lookAt(xim::Vector3(4.0f, -2.0f, 1.5f), xim::Vector3(0.1f, 3.0f, -0.8f), xim::Vector3(9.0f, -2.0f, 0.0f));
	glm::mat4 per2 = glm::lookAt(glm::vec3(4.0f, -2.0f, 1.5f), glm::vec3(0.1f, 3.0f, -0.8f), glm::vec3(9.0f, -2.0f, 0.0f));

	xim::Matrix4 res1 = my * per;
	glm::mat4 res2 = mat * per2;

	for (int i = 0; i < 16; i++)
	{
		cout << *(res1.getPointer() + i) << " " << *(&res2[0][0] + i) << endl;
	}
}