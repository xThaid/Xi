#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>

namespace xiengine
{
	class File;
	
	enum ShaderType
	{
		VERTEX,
		FRAGMENT
	};

	class Shader
	{
	public:
		Shader(const std::string& shaderSource);
		Shader(File file);
		~Shader();

		GLuint compileShader(ShaderType type);
		void clean();

	private:
		GLuint shaderID;

		const char* shaderSource;

	};
}
			