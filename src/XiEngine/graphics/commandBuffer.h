#pragma once

#include "../graphics/material.h"
#include "../graphics/mesh.h"
#include "../math/ximath.h"

struct RenderCommand
{
	Mesh* mesh;
	Material* material;
	xim::Matrix4 transform;
};

class CommandBuffer
{
public:
	CommandBuffer();
	~CommandBuffer();

	void push(Mesh* mesh, Material* material, xim::Matrix4 transform = xim::Matrix4());

	void clear();

	inline std::vector<RenderCommand>& getDefaultRenderCommands() { return defaultRenderCommands_; }

private:
	std::vector<RenderCommand> defaultRenderCommands_;
};