#include "uiRenderer.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../graphics/geometry.h"
#include "../graphics/graphicsDefs.h"
#include "../graphics/shader.h"
#include "../graphics/vertexBuffer.h"
#include "../graphics/texture.h"
#include "../resource/resourceManager.h"
#include "../ui/label.h"
#include "../utils/file.h"

UIRenderer::UIRenderer(Graphics* graphics, const IntVector2& uiSize) :
	graphics_(graphics),
	textShader_(ResourceManager::getInstance()->getResource<Shader>("text shader")),
	uiSize_(uiSize)
{
	projectionMatrix_ = Matrix4::orthoMatrix(0.0f, (float) uiSize.x_, 0.0f, (float) uiSize.y_);
	graphics_->setShader(textShader_);
	textShader_->setMatrix4("projection", projectionMatrix_);

	prepareGeometry();

	loadedFont_ = loadFont(File("D:/Dev/Repos/Xi/res/fonts/arial.ttf"));
}

UIRenderer::~UIRenderer()
{
	for (unsigned int c = 0; c < 128; c++)
	{
		if (characters_[c].texture_ != nullptr)
			delete characters_[c].texture_;
	}

	delete glyphGeometry_;
}

void UIRenderer::renderLabels(const std::vector<Label*>& labels)
{
	for (Label* label : labels)
	{
		renderLabel(label);
	}
}

void UIRenderer::renderLabel(Label* label)
{
	if (!loadedFont_)
		return;

	graphics_->setBlendMode(true);

	graphics_->setShader(textShader_);

	float x = label->getPosition().x_;
	float y = (float) uiSize_.y_ - label->getPosition().y_;

	const std::string& text = label->getText();
	for (unsigned int i = 0; i < text.size(); i++)
	{
		unsigned int c = text[i];

		float xpos = x + characters_[c].bearing_.x_ * label->getScale();
		float ypos = y - (characters_[c].size_.y_ - characters_[c].bearing_.y_) * label->getScale();

		Vector3 dimension = Vector3((float) characters_[c].size_.x_, (float) characters_[c].size_.y_, 1.0f);

		Matrix3x4 model = Matrix3x4::translationMatrix(Vector3(xpos, ypos, 0.0f));
		model.scale(dimension * label->getScale());
		
		graphics_->setTexture(0, characters_[c].texture_);

		textShader_->setMatrix3x4("model", model);
		textShader_->setColor("textColor", label->getColor());

		glyphGeometry_->draw(graphics_);

		x += (characters_[c].advance_ >> 6) * label->getScale();
	}
}

void UIRenderer::prepareGeometry()
{
	VertexBuffer* vertexBuffer = new VertexBuffer(MASK_POSITION | MASK_TEXCOORD);
	vertexBuffer->create(6);

	float data[] = 
	{
		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,

		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		1.0f, 1.0f, 0.0f,	1.0f, 0.0f
	};
	vertexBuffer->setData((void*) &data);

	glyphGeometry_ = new Geometry(PrimitiveTopology::TRIANGLES, vertexBuffer);
}

bool UIRenderer::loadFont(File& file)
{
	if (!file.exist())
		return false;

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		return false;

	FT_Face face;
	if (FT_New_Face(ft, file.getPath().c_str(), 0, &face))
		return false;

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	GLTextureOptions options;
	options.internalFormat = GL_RED;
	options.format = GL_RED;
	options.type = GL_UNSIGNED_BYTE;
	options.filterMin = GL_LINEAR;
	options.filterMax = GL_LINEAR_MIPMAP_LINEAR;
	options.wrapMethod = GL_CLAMP_TO_EDGE;
	options.mipMapping = true;

	for (unsigned int c = 0; c < 128; c++)
		characters_[c].texture_ = nullptr;

	for (unsigned int c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			return false;

		GLTexture2D* texture = new GLTexture2D(face->glyph->bitmap.width, face->glyph->bitmap.rows, options, face->glyph->bitmap.buffer);

		characters_[c].texture_ = texture;
		characters_[c].size_ = IntVector2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
		characters_[c].bearing_ = IntVector2(face->glyph->bitmap_left, face->glyph->bitmap_top);
		characters_[c].advance_ = face->glyph->advance.x;
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	return true;
}