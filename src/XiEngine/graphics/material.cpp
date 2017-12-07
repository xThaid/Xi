#include "material.h"

Material::Material(const std::string& name, Shader* shader) :
	Resource(name),
	shader_(shader)
{
}

Material::~Material()
{
}

bool Material::beginLoad()
{
	return true;
}

bool Material::endLoad()
{
	return true;
}

void Material::release()
{
}

void Material::setShader(Shader* shader)
{
	shader_ = shader;
}

void Material::setBool(const std::string& name, bool value)
{
	shaderUniformValues_[name].type = UniformType::UNIFORM_TYPE_BOOL;
	shaderUniformValues_[name].bool_ = value;
}

void Material::setInt(const std::string& name, int value)
{
	shaderUniformValues_[name].type = UniformType::UNIFORM_TYPE_INT;
	shaderUniformValues_[name].int_ = value;
}

void Material::setFloat(const std::string& name, float value)
{
	shaderUniformValues_[name].type = UniformType::UNIFORM_TYPE_FLOAT;
	shaderUniformValues_[name].float_ = value;
}

void Material::setVector2(const std::string& name, xim::Vector2& value)
{
	shaderUniformValues_[name].type = UniformType::UNIFORM_TYPE_VEC2;
	shaderUniformValues_[name].vec2_ = value;
}

void Material::setVector3(const std::string& name, xim::Vector3& value)
{
	shaderUniformValues_[name].type = UniformType::UNIFORM_TYPE_VEC3;
	shaderUniformValues_[name].vec3_ = value;
}

void Material::setVector4(const std::string& name, xim::Vector4& value)
{
	shaderUniformValues_[name].type = UniformType::UNIFORM_TYPE_VEC4;
	shaderUniformValues_[name].vec4_ = value;
}

void Material::setMatrix4(const std::string& name, xim::Matrix4& value)
{
	shaderUniformValues_[name].type = UniformType::UNIFORM_TYPE_MAT4;
	shaderUniformValues_[name].mat4_ = value;
}

void Material::sendUniformsValuesToShader()
{
	shader_->useShader();
	for (auto it = shaderUniformValues_.begin(); it != shaderUniformValues_.end(); it++)
	{
		switch(it->second.type)
		{
		case UNIFORM_TYPE_BOOL:
			shader_->setBool(it->first, it->second.bool_);
			break;
		case UNIFORM_TYPE_INT:
			shader_->setInt(it->first, it->second.int_);
			break;
		case UNIFORM_TYPE_FLOAT:
			shader_->setFloat(it->first, it->second.float_);
			break;
		case UNIFORM_TYPE_VEC2:
			shader_->setVector2(it->first, it->second.vec2_);
			break;
		case UNIFORM_TYPE_VEC3:
			shader_->setVector3(it->first, it->second.vec3_);
			break;
		case UNIFORM_TYPE_VEC4:
			shader_->setVector4(it->first, it->second.vec4_);
			break;
		case UNIFORM_TYPE_MAT4:
			shader_->setMatrix4(it->first, it->second.mat4_);
			break;
		default:
			break;
		}
	}
}
