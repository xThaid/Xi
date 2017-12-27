#include "label.h"

Label::Label(const std::string& text, const Vector2& position, float scale, Color color) :
	text_(text),
	position_(position),
	scale_(scale),
	color_(color)
{
}

Label::~Label()
{
}

void Label::setText(const std::string& text)
{
	text_ = text;
}

void Label::setPosition(float x, float y)
{
	position_ = Vector2(x, y);
}

void Label::setPosition(const Vector2& position)
{
	position_ = position;
}

void Label::setScale(float scale)
{
	scale_ = scale;
}

void Label::setColor(const Color& color)
{
	color_ = color;
}