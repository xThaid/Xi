#include "renderingEngine.h"

#include "../utils/logger.h"
#include "../core/scene.h"
#include "../camera.h"

RenderingEngine::RenderingEngine(Window * window)
{
	if (!glfwInit())
		Logger::error("Failed to initialize GLFW");
	else
		Logger::debug("GLFW version: " + std::string(glfwGetVersionString()));

	window->init();
	glfwMakeContextCurrent(window->getWindow());

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		Logger::error("Failed to initialize GLAD");

	Logger::info("OpenGL version: " + std::string((char*)glGetString(GL_VERSION)));

	changeViewport(window->getWidth(), window->getHeight());

	setUp();
}


RenderingEngine::~RenderingEngine()
{
	cleanUp();
	destroy();
}

void RenderingEngine::init()
{
	basicShader->compileShader();

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	xim::Matrix4 proj = xim::perspective(xim::radians(45.0f), 1.0f, 0.1f, 100.0f);
	basicShader->useShader();
	basicShader->loadMatrix4("projection", proj);
}

void RenderingEngine::changeViewport(int width, int height)
{
	glViewport(0, 0, width, height);
	viewportWidth = width;
	viewportHeight = height;
}

void RenderingEngine::render(Scene* scene)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	xim::Matrix4 viewMatrix = scene->getMainCamera()->getViewMatrix();

	xim::Vector3 cubePositions[] = {
		xim::Vector3(0.0f,  0.0f,  0.0f),
		xim::Vector3(2.0f,  5.0f, -15.0f),
		xim::Vector3(-1.5f, -2.2f, -2.5f),
		xim::Vector3(-3.8f, -2.0f, -12.3f),
		xim::Vector3(2.4f, -0.4f, -3.5f),
		xim::Vector3(-1.7f,  3.0f, -7.5f),
		xim::Vector3(1.3f, -2.0f, -2.5f),
		xim::Vector3(1.5f,  2.0f, -2.5f),
		xim::Vector3(1.5f,  0.2f, -1.5f),
		xim::Vector3(-1.3f,  1.0f, -1.5f)
	};

	basicShader->useShader();
	basicShader->loadMatrix4("view", viewMatrix);

	for (int i = 0; i < 10; i++)
	{
		xim::Matrix4 model;
		model.translate(cubePositions[i] + xim::Vector3(0.0f, 0.0f, -5.0f));

		model.rotate(glfwGetTime(), 1.0f, 0.5f, 0.5f);

		basicShader->loadMatrix4("model", model);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void RenderingEngine::setUp()
{
	basicShader = new Shader("D:/Dev/Repos/Xi/res/shaders/basicShader.vs", "D:/Dev/Repos/Xi/res/shaders/basicShader.fs");
}

void RenderingEngine::cleanUp()
{
	delete basicShader;
}

void RenderingEngine::destroy()
{
	glfwTerminate();
}