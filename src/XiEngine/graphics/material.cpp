#include "material.h"

#include "../resource/resourceManager.h"
#include "../utils/logger.h"

Material::Material(Shader* shader) :
	shader_(shader),
	wireframe_(false)
{
}

Material::~Material()
{
}

Material* Material::clone(const std::string& newName) const
{
	Material* myClone = new Material(shader_);
	myClone->wireframe_ = wireframe_;

	myClone->shaderUniformValues_ = shaderUniformValues_;

	if (!newName.empty())
		myClone->registerInLibrary(newName);

	return myClone;
}

void Material::registerInLibrary(const std::string& name)
{
	MaterialLibrary::getInstance()->registerMaterial(name, this);
}

void Material::setShader(Shader* shader)
{
	shader_ = shader;
}

void Material::setWireframe(bool wireframe)
{
	wireframe_ = wireframe;
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

MaterialLibrary* MaterialLibrary::instance_ = nullptr;

MaterialLibrary::MaterialLibrary()
{
	if (instance_ != nullptr)
	{
		Logger::error("Created second material library!");
		return;
	}

	instance_ = this;

	setupDefaultMaterials();
}

MaterialLibrary::~MaterialLibrary()
{
	for (auto& material : materials_)
	{
		delete material.second;
	}

	delete debugMaterial_;
	delete defaultMaterial_;
}

Material* MaterialLibrary::getMaterial(const std::string& name)
{
	auto result = materials_.find(name);
	if (result == materials_.end())
	{
		return debugMaterial_;
	}

	return result->second;
}

void MaterialLibrary::registerMaterial(const std::string& name, Material* material)
{
	auto result = materials_.find(name);
	if (result != materials_.end())
	{
		Logger::warn("There already exists material with name " + name);
		return;
	}

	materials_[name] = material;
}

void MaterialLibrary::setupDefaultMaterials()
{
	debugMaterial_ = new Material(ResourceManager::getInstance()->getResource<Shader>("debug shader"));
	debugMaterial_->setVector3("color", xim::Vector3(1.0f, 0.0f, 1.0f));

	defaultMaterial_ = new Material(ResourceManager::getInstance()->getResource<Shader>("tempShader"));

	defaultMaterial_->setVector3("light.ambient", xim::Vector3(0.1f, 0.1f, 0.1f));
	defaultMaterial_->setVector3("light.diffuse", xim::Vector3(0.5f, 0.5f, 0.5f));
	defaultMaterial_->setVector3("light.specular", xim::Vector3(1.0f, 1.0f, 1.0f));
	defaultMaterial_->setVector3("light.position", xim::Vector3(3.0f, 3.0f, 0.0f));

	defaultMaterial_->setInt("material.diffuse", 0);
	defaultMaterial_->setFloat("material.shininess", 32.0f);

	Material* redDebug = MaterialLibrary::getInstance()->getDebugMaterial()->clone("redDebug");
	redDebug->setVector3("color", xim::Vector3(1.0f, 0.0f, 0.0f));
	Material* greenDebug = MaterialLibrary::getInstance()->getDebugMaterial()->clone("greenDebug");
	greenDebug->setVector3("color", xim::Vector3(0.0f, 1.0f, 0.0f));
	Material* blueDebug = MaterialLibrary::getInstance()->getDebugMaterial()->clone("blueDebug");
	blueDebug->setVector3("color", xim::Vector3(0.0f, 0.0f, 1.0f));
}
