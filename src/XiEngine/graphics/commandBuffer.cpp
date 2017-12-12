#include "commandBuffer.h"

CommandBuffer::CommandBuffer()
{
}

CommandBuffer::~CommandBuffer()
{
}

void CommandBuffer::push(Mesh* mesh, Material* material, xim::Matrix4 transform)
{
	RenderCommand command;
	command.mesh = mesh;
	command.material = material;
	command.transform = transform;
	defaultRenderCommands_.push_back(command);
}

void CommandBuffer::clear()
{
	defaultRenderCommands_.clear();
}
