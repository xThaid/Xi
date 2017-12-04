#pragma once

#include "../graphics/mesh.h"

namespace Primitives
{
	class Quad : public Mesh
	{
	public:
		Quad(const std::string& name);
		Quad(const std::string& name, float width, float height);
	};

	class Cube : public Mesh
	{
	public:
		Cube(const std::string& name);
	};

	class Plane : public Mesh
	{
	public:
		Plane(const std::string& name, unsigned int xSegments, unsigned int ySegments);
	};

	class Circle : public Mesh
	{
	public:
		Circle(const std::string& name, unsigned int edgeSegments, unsigned int ringSegments);
	};

	class Sphere : public Mesh
	{
	public:
		Sphere(const std::string& name, unsigned int xSegments, unsigned int ySegments);
	};
}