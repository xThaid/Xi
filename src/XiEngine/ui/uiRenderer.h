#pragma once

#include "../math/ximath.h"

class Camera;
class File;
class Geometry;
class GLTexture2D;
class Graphics;
class Label;
class Shader;

struct FontGlyph
{
	GLTexture2D* texture_;
	IntVector2 size_;
	IntVector2 bearing_;
	unsigned int advance_;
};

class UIRenderer
{
public:
	UIRenderer(Graphics* graphics, const IntVector2& uiSize);
	~UIRenderer();

	void renderLabel(Label* label);

private:
	Graphics* graphics_;

	bool loadedFont_;
	Shader* textShader_;
	Geometry* glyphGeometry_;
	FontGlyph characters_[128];

	Matrix4 projectionMatrix_;

	void prepareGeometry();

	bool loadFont(File& file);
};