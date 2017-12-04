#pragma once

#include "../precompiled.h"

#include "../math/ximath.h"
#include "../resource/resource.h"

class Mesh : public Resource
{
	XI_RESOURCE(Mesh)

public:
	Mesh(const std::string& name, 
		std::vector<unsigned int>* indices, 
		std::vector<xim::Vector3>* positions, 
		std::vector<xim::Vector2>* UV, 
		std::vector<xim::Vector3>* normals);
	~Mesh();

	virtual bool beginLoad() override;
	virtual bool endLoad() override;

	virtual void release() override;

	virtual const std::string getTypeName() const override { return "Mesh"; }

	inline unsigned int getNumIndices() { return indices_->size(); }

	inline unsigned int getVAO() { return VAO_; }

	bool hasPositions();
	bool hasUV();
	bool hasNormals();
	bool hasIndices();

private:
	std::vector<xim::Vector3>* positions_;
	std::vector<xim::Vector2>* UV_;
	std::vector<xim::Vector3>* normals_;

	std::vector<unsigned int>* indices_;

	unsigned int VAO_;
	unsigned int VBO_;
	unsigned int EBO_;

	bool uploadToGPU(bool interleaved);

	void prepareData(std::vector<float>& data, bool interleaved);
};