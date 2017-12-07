#pragma once

#include "../precompiled.h"

#include "../graphics/shader.h"
#include "../resource/resource.h"

class Material : public Resource
{
	XI_RESOURCE(Material)

public:
	Material(const std::string& name, Shader* shader);
	~Material();

	virtual bool beginLoad() override;
	virtual bool endLoad() override;

	virtual void release() override;

	virtual const std::string getTypeName() const override { return "Material"; }

	void setShader(Shader* shader);

	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setVector2(const std::string& name, xim::Vector2& value);
	void setVector3(const std::string& name, xim::Vector3& value);
	void setVector4(const std::string& name, xim::Vector4& value);
	void setMatrix4(const std::string& name, xim::Matrix4& value);

	void sendUniformsValuesToShader();

	inline Shader* getShader() { return shader_; }

private:
	Shader* shader_;

	std::map<std::string, ShaderUniformValue> shaderUniformValues_;
};