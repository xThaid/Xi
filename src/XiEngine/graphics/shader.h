#pragma once

#include "../precompiled.h"

#include "../graphics/graphicsDefs.h"
#include "../math/ximath.h"
#include "../resource/resource.h"
#include "../utils/file.h"

enum UniformType
{
	UNIFORM_TYPE_BOOL,
	UNIFORM_TYPE_INT,
	UNIFORM_TYPE_FLOAT,
	UNIFORM_TYPE_SAMPLER2D,
	UNIFORM_TYPE_SAMPLERCUBE,
	UNIFORM_TYPE_VEC2,
	UNIFORM_TYPE_VEC3,
	UNIFORM_TYPE_VEC4,
	UNIFORM_TYPE_MAT3,
	UNIFORM_TYPE_MAT4
};

struct ShaderUniform
{
	std::string name;
	UniformType type;
	unsigned int location;
};

class ShaderVariation
{
public:
	ShaderVariation(const std::string& path, unsigned int type);
	~ShaderVariation();

	bool beginLoad();
	bool endLoad();

	void release();

	bool compileShader();
	void destroyShader();

	inline unsigned int getID() { return shaderVariationID_; }
	inline unsigned int getMemoryUse() { return memoryUse_; }

private:
	File sourceFile_;
	std::string sourceCode_;
	unsigned int memoryUse_;

	int shaderType_;
	unsigned int shaderVariationID_;
};

class Shader : public Resource
{
	XI_RESOURCE(Shader)

public:
	Shader(const std::string& shaderName, const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	~Shader();

	virtual bool beginLoad() override;
	virtual bool endLoad() override;

	virtual void release() override;

	virtual const std::string getTypeName() const override { return "Shader"; }

	bool linkShaders();
	void destroyShader();

	void useShader();

	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setVector2(const std::string& name, Vector2& value);
	void setVector3(const std::string& name, Vector3& value);
	void setVector4(const std::string& name, Vector4& value);
	void setMatrix3(const std::string& name, Matrix3& value);
	void setMatrix3x4(const std::string& name, Matrix3x4& value);
	void setMatrix4(const std::string& name, Matrix4& value);
	void setColor(const std::string& name, const Color& color);
	
	int getVertexAttributeLocation(VertexElement element);
	inline unsigned int getUsedVertexAttributes_() { return usedVertexAttributes_; }

private:
	unsigned int shaderProgramID_;

	ShaderVariation* vertexShader_;
	ShaderVariation* fragmentShader_;

	std::map<VertexElement, unsigned int> vertexAttributes_;
	unsigned int usedVertexAttributes_;

	std::map<std::string, ShaderUniform> shaderUniforms_;
	std::set<std::string> unknownUniformsCache_;

	void loadVertexAttributes();
	void loadUniforms();

	int getUniformLocation(const std::string& name);
};