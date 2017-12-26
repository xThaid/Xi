#pragma once

#include "../precompiled.h"

#include "../graphics/shader.h"
#include "../resource/resource.h"

class MaterialLibrary;

class Material
{
public:
	Material(Shader* shader);
	~Material();

	Material(const Material&) = delete;
	void operator=(const Material&) = delete;

	Material* clone(const std::string& newName = "") const;

	void registerInLibrary(const std::string& name);

	void setShader(Shader* shader);
	void setWireframe(bool wireframe);

	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setVector2(const std::string& name, Vector2& value);
	void setVector3(const std::string& name, Vector3& value);
	void setVector4(const std::string& name, Vector4& value);
	void setMatrix4(const std::string& name, Matrix4& value);

	void sendUniformsValuesToShader();

	inline Shader* getShader() { return shader_; }
	inline bool isWireframe() { return wireframe_; }

private:
	Shader* shader_;

	std::map<std::string, ShaderUniformValue> shaderUniformValues_;

	bool wireframe_;

	friend class MaterialLibrary;
};

class MaterialLibrary
{
public:
	inline static MaterialLibrary* getInstance() { return instance_; }

	MaterialLibrary();
	~MaterialLibrary();
	
	Material* getMaterial(const std::string& name);

	inline Material* getDefaultMaterial() { return defaultMaterial_; }

private:
	static MaterialLibrary* instance_;

	std::map<std::string, Material*> materials_;

	Material* defaultMaterial_;

	void registerMaterial(const std::string& name, Material* material);

	void setupDefaultMaterials();

	friend class Material;
};